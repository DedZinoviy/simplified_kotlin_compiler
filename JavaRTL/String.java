package JavaRTL;

public class String extends Any{

    public java.lang.String _value;
    public String(java.lang.String str){
        this._value = str;
    }

    public Int toInt() {
        try {
            int i = Integer.parseInt (this._value.trim ());
            return new Int(i);
        } catch (NumberFormatException nfe) {
            throw new NumberFormatException(nfe.getMessage());
        }
    }
}
