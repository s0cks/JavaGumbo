/* DO NOT EDIT THIS FILE - it is machine generated */
#include <jni.h>
/* Header for class io_github_s0cks_gumbo_HTMLFile */

#ifndef _Included_io_github_s0cks_gumbo_HTMLFile
#define _Included_io_github_s0cks_gumbo_HTMLFile
#ifdef __cplusplus
extern "C" {
#endif
/*
 * Class:     io_github_s0cks_gumbo_HTMLFile
 * Method:    open
 * Signature: (Ljava/lang/String;)I
 */
JNIEXPORT jint JNICALL Java_io_github_s0cks_gumbo_HTMLFile_open
  (JNIEnv *, jobject, jstring);

/*
 * Class:     io_github_s0cks_gumbo_HTMLFile
 * Method:    getTitle
 * Signature: (I)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_io_github_s0cks_gumbo_HTMLFile_getTitle
  (JNIEnv *, jobject, jint);

/*
 * Class:     io_github_s0cks_gumbo_HTMLFile
 * Method:    close
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_io_github_s0cks_gumbo_HTMLFile_close
  (JNIEnv *, jobject, jint);

#ifdef __cplusplus
}
#endif
#endif
