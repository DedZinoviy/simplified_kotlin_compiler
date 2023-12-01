package JavaRTL;

/**
 * Класс, представляющий символьную константу.
 */
public class Char {

    public char _char;

    public Char(char chr) {
        this._char = chr;
    }

    Char(int charVal) {
        this._char = (char)charVal;
    }
}
