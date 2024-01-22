package JavaRTL;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class InputOutput {

    public static void println(Int i) {
        System.out.println(i._value);
    }

    public static void println(Char c) {
        System.out.println(c._value);
    }

    public static void println(JavaRTL.String s) {
        System.out.println(s._value);
    }

    public static void println(JavaRTL.Boolean b) {
        System.out.println(b._value);
    }

    public static void print(Int i) {
        System.out.print(i._value);
    }

    public static void print(Char c) {
        System.out.print(c._value);
    }

    public static void print(JavaRTL.String s) {
        System.out.print(s._value);
    }

    public static void print(JavaRTL.Boolean b) {
        System.out.print(b._value);
    }

    public static JavaRTL.String readLine(){
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        try {
            java.lang.String s = br.readLine();
            return new JavaRTL.String(s);
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
    }
}
