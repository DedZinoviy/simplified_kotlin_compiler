package JavaRTL;

public class Boolean {
    
    public boolean _value;
    
    public Boolean(boolean val){
        this._value = val;
    }

    public Boolean equals(Boolean other) {
        return new Boolean(this._value == other._value);
    }

    public Boolean notEquals(Boolean other) {
        return new Boolean(this._value != other._value);
    }

    public Boolean not() {
        return new Boolean(!this._value);
    }

    public Boolean or(Boolean other) {
        return new Boolean(this._value || other._value);
    }

    public Boolean and(Boolean other) {
        return new Boolean(this._value && other._value);
    }

    public Boolean(int val) {
        if (val == 0)
            this._value = false;
        else 
            this._value = true;
    }
}
