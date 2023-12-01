package JavaRTL;

public class Int extends Any{

    public static final int MIN_VALUE = -2147483648;

    public static final int MAX_VALUE = 2147483647;
    public int _value;
    
    public Int(int value) {
        this._value = value;
    }

    public Int toInt() {
        return this;
    }

    public Double toDouble() {
        return new Double((double) this._value);
    }

    public Char toChar() {
        return new Char(this._value);
    }
}
