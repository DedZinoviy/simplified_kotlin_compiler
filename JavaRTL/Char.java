package JavaRTL;

/**
 * Класс, представляющий символьную константу.
 */
public class Char extends Any{

    public char _value;

    public Char(char chr) {
        this._value = chr;
    }

    Char(int charVal) {
        this._value = (char)charVal;
    }

    public Char plus(Int other) {
        return new Char(this._value + other._value);
    }

    public Char minus(Int other) {
        return new Char(this._value - other._value);
    }
}
