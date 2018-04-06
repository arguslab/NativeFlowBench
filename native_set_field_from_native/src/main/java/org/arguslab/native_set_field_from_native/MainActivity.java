package org.arguslab.native_set_field_from_native;

import android.app.Activity;
import android.os.Bundle;
import android.util.Log;

public class MainActivity extends Activity {

    static {
        System.loadLibrary("set_field_from_native"); // "set_field_from_native.dll" in Windows, "libset_field_from_native.so" in Unixes
    }

    public static native Foo setField(ComplexData complexData);

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        ComplexData complexData = new ComplexData();
        Foo fooRet = setField(complexData);
        Log.d("set_field_from_native", String.valueOf(fooRet.getIndex()));
        Log.d("set_field_from_native", fooRet.getData());
    }
}
