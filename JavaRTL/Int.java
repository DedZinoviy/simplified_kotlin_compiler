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

    /** Операция сложения Int.
     * @param other Второе слагаемое.
     * @return  Результат сложения.
     */
    public Int plus(Int other) {
        return new Int(this._value + other._value);
    }

    /** Операция вычитания Int.
     * @param other Вычитаемое.
     * @return  Результат вычитания.
     */
    public Int minus(Int other) {
        return new Int(this._value - other._value);
    }

    /** Операция умножения Int.
     * @param other Второй множитель.
     * @return результат умножения.
     */
    public Int times(Int other) {
        return new Int(this._value * other._value);
    }

    /** Операция деления Int.
     * @param other делитель.
     * @return Частное от деления.
     */
    public Int div(Int other) {
        return new Int(this._value / other._value);
    }

    /** Операция получения остатка от деления
     * @param other делитель.
     * @return Остаток от деления.
     */
    public Int rem(Int other) {
        return new Int(this._value % other._value);
    }

    public Boolean equals(Int other) {
        return new Boolean(this._value == other._value);
    }

    public Boolean notEquals(Int other) {
        return new Boolean(this._value != other._value);
    }

    public Boolean greater(Int other) {
        return new Boolean(this._value > other._value);
    }

    public Boolean less(Int other) {
        return new Boolean(this._value < other._value);
    }

    public Boolean greaterEquals(Int other) {
        return new Boolean(this._value >= other._value);
    }

    public Boolean lessEquals(Int other) {
        return new Boolean(this._value <= other._value);
    }

    public Double toDouble() {
        return new Double((double) this._value);
    }

    public Char toChar() {
        return new Char(this._value);
    }
}
