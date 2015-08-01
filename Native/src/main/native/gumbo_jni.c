#include "include/gumbo_jni.h"
#include <jni.h>
#include <gumbo.h>

#ifdef __CYGWIN32__
#include <direct.h>
#elif defined __linux__
#include <sys/stat.h>
#endif

typedef struct _gumbo_desc{
    GumboOutput* output;
    char* text;
} gumbo_desc;

static void* malloc_wrapper(void* unused, size_t size){
    return malloc(size);
}

static void free_wrapper(void* unused, void* ptr){
    free(ptr);
}

static int java_gumbo_description = 0;
static gumbo_desc** java_gumbo_descriptions;
static GumboOptions options ={
    &malloc_wrapper,
    &free_wrapper,
    NULL,
    8,
    false,
    -1,
    GUMBO_TAG_LAST,
    GUMBO_NAMESPACE_HTML
};

static void
read_file(FILE* fp, char** output, int* len){
    struct stat filestats;
    int fd = fileno(fp);
    fstat(fd, &filestats);
    *len = filestats.st_size;
    *output = malloc(*len + 1);
    int start = 0;
    int read;
    while((read = fread(*output + start, 1, *len - start, fp))){
        start += read;
    }
    fclose(fp);
}

static const char*
find_title(const GumboNode* root){
    if(root->type != GUMBO_NODE_ELEMENT){
        return "<not html node>";
    } else if(root->v.element.children.length < 2){
        return "<html nodes are less than 2>";
    }

    const GumboVector* root_children = &root->v.element.children;
    GumboNode* head = NULL;
    for(int i = 0; i < root_children->length; ++i){
        GumboNode* child = root_children->data[i];
        if(child->type == GUMBO_NODE_ELEMENT && child->v.element.tag == GUMBO_TAG_HEAD){
            head = child;
            break;
        }
    }

    if(head == NULL){
        return "<head not found>";
    }

    GumboVector* head_children = &head->v.element.children;
    for(int i = 0; i < head_children->length; ++i){
        GumboNode* child = head_children->data[i];
        if(child->type == GUMBO_NODE_ELEMENT && child->v.element.tag == GUMBO_TAG_TITLE){
            if(child->v.element.children.length != 1){
                return "<empty title>";
            }

            GumboNode* title_text = child->v.element.children.data[0];
            return title_text->v.text.text;
        }
    }

    return "<no title found>";
}

static void
java_gumbo_free_description(gumbo_desc* desc){
    gumbo_destroy_output(&options, desc->output);
    free(desc->text);
}

JNIEXPORT jint JNICALL
Java_io_github_s0cks_gumbo_HTMLFile_open(JNIEnv* env, jobject obj, jstring file){
    if(!java_gumbo_descriptions){
        java_gumbo_descriptions = malloc(1024 * sizeof(gumbo_desc));
    }

    int desc = java_gumbo_description++;
    gumbo_desc* d = malloc(sizeof(gumbo_desc));

    FILE* f = fopen((*env)->GetStringUTFChars(env, file, 0), "r");
    char* input;
    int len;
    read_file(f, &input, &len);
    GumboOutput* g = gumbo_parse_with_options(&options, input, len);
    d->output = g;
    d->text = input;
    java_gumbo_descriptions[desc] = d;
    return desc;
}

JNIEXPORT jstring JNICALL
Java_io_github_s0cks_gumbo_HTMLFile_getTitle(JNIEnv* env, jobject obj, jint desc){
    gumbo_desc* d = java_gumbo_descriptions[desc];
    const char* title = find_title(d->output->root);
    return (*env)->NewStringUTF(env, title);
}

JNIEXPORT void JNICALL
Java_io_github_s0cks_gumbo_HTMLFile_close(JNIEnv* env, jobject obj, jint desc){
    java_gumbo_free_description(java_gumbo_descriptions[desc]);
}