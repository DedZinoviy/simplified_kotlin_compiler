package JavaRTL;

public class Boolean {
    
    public boolean _value;
    
    public Boolean(boolean val){
        this._value = val;
    }

    public Boolean(int val) {
        if (val == 0)
            this._value = false;
        else 
            this._value = true;
    }
}
