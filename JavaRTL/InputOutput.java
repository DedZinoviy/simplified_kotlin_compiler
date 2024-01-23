package JavaRTL;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class InputOutput {

    public static JavaRTL.Unit println(Int i) {
        System.out.println(i._value);
        return new Unit();
    }

    public static JavaRTL.Unit println(Char c) {
        System.out.println(c._value);
        return new Unit();
    }

    public static JavaRTL.Unit println(JavaRTL.String s) {
        System.out.println(s._value);
        return new Unit();
    }

    public static JavaRTL.Unit println(JavaRTL.Boolean b) {
        System.out.println(b._value);
        return new Unit();
    }

    public static JavaRTL.Unit print(Int i) {
        System.out.print(i._value);
        return new Unit();
    }

    public static JavaRTL.Unit print(Char c) {
        System.out.print(c._value);
        return new Unit();
    }

    public static JavaRTL.Unit print(JavaRTL.String s) {
        System.out.print(s._value);
        return new Unit();
    }

    public static JavaRTL.Unit print(JavaRTL.Boolean b) {
        System.out.print(b._value);
        return new Unit();
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
