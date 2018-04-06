package org.arguslab.native_set_field_from_arg_field;

import android.annotation.SuppressLint;
import android.app.Activity;
import android.os.Bundle;
import android.util.Log;

public class MainActivity extends Activity {

    static {
        System.loadLibrary("set_field_from_arg_field"); // "set_field_from_arg_field.dll" in Windows, "libset_field_from_arg_field.so" in Unixes
    }

    public static native Foo setField(ComplexData complexData, ComplexData otherData);

    @SuppressLint("LongLogTag")
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        ComplexData complexData = new ComplexData();
        ComplexData otherData = new ComplexData();

        Foo foo = new Foo();
        foo.setIndex(2018);
        foo.setData("set_field_from_arg_field");
        otherData.setFoo(foo);
        Foo fooRet = setField(complexData, otherData);
        Log.d("set_field_from_arg_field", String.valueOf(fooRet.getIndex()));
        Log.d("set_field_from_arg_field", fooRet.getData());
    }
}
