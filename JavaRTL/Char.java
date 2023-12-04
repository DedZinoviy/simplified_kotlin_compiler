package JavaRTL;

/**
 * Класс, представляющий символьную константу.
 */
public class Char {

    public char _value;

    public Char(char chr) {
        this._value = chr;
    }

    Char(int charVal) {
        this._value = (char)charVal;
    }
}
