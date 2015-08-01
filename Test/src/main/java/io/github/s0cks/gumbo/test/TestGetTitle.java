package io.github.s0cks.gumbo.test;

import io.github.s0cks.gumbo.HTMLFile;
import org.jsoup.Jsoup;
import org.jsoup.nodes.Document;
import org.openjdk.jmh.annotations.Benchmark;
import org.openjdk.jmh.profile.StackProfiler;
import org.openjdk.jmh.runner.Runner;
import org.openjdk.jmh.runner.options.Options;
import org.openjdk.jmh.runner.options.OptionsBuilder;

import java.io.IOException;
import java.nio.file.Path;
import java.nio.file.Paths;

public class TestGetTitle{
    private static final Path document = Paths.get(System.getProperty("user.dir"), "test.html");

    static{
        System.loadLibrary("gumbo-linux");
    }

    public static void main(String... args)
    throws Exception{
        Options opts = new OptionsBuilder()
            .addProfiler(StackProfiler.class)
            .forks(1)
            .include(TestGetTitle.class.getSimpleName())
            .build();
        new Runner(opts).run();
    }

    @Benchmark
    public void jsoup()
    throws IOException{
        Document d = Jsoup.parse(document.toFile(), "utf-8");
        d.title();
    }

    @Benchmark
    public void gumbo()
    throws IOException {
        try(HTMLFile file = new HTMLFile(document)){
            file.getTitle();
        } catch(Exception e){
            e.printStackTrace(System.err);
        }
    }
}