package io.github.s0cks.gumbo;

import java.io.Closeable;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.util.HashMap;
import java.util.Map;

public final class HTMLFile
implements Closeable {
    private final int desc;

    private static final Map<Path, Integer> cache = new HashMap<>();

    public HTMLFile(Path p)
    throws FileNotFoundException {
        if(!Files.exists(p)){
            throw new FileNotFoundException("Cannot find file: " + p);
        }

        this.desc = this.open(p.toString());
    }

    public String getTitle(){
        return this.getTitle(this.desc);
    }

    private native int open(String file);
    private native String getTitle(int desc);
    private native void close(int desc);

    @Override
    public void close()
    throws IOException{
        this.close(this.desc);
    }
}