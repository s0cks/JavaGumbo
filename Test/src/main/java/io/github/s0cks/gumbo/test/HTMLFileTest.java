package io.github.s0cks.gumbo.test;

import io.github.s0cks.gumbo.HTMLFile;
import org.jsoup.Jsoup;
import org.jsoup.nodes.Document;

import java.nio.file.Path;
import java.nio.file.Paths;

public final class HTMLFileTest{
    static{
        System.loadLibrary("gumbo-linux");
    }

    public static void main(String... args)
    throws Exception{
        Path file = Paths.get(System.getProperty("user.home"), "Desktop", "test.html");
        long start = System.nanoTime();
        try(HTMLFile html = new HTMLFile(file)){
            for(int i = 0; i < 10; i++){
                System.out.println(html.getTitle());
            }
        }
        System.out.println((System.nanoTime() - start) + " ns");

        start = System.nanoTime();
        Document d = Jsoup.parse(file.toFile(), "utf-8");
        for(int i = 0; i < 10; i++){
            System.out.println(d.title());
        }
        System.out.println((System.nanoTime() - start) + " ns");
    }
}