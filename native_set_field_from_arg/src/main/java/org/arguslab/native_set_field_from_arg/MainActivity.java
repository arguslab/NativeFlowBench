package org.arguslab.native_set_field_from_arg;

import android.app.Activity;
import android.os.Bundle;
import android.util.Log;


public class MainActivity extends Activity {

    static {
        System.loadLibrary("set_field_from_arg"); // "set_field_from_arg.dll" in Windows, "libset_field_from_arg.so" in Unixes
    }

    public static native Foo setField(ComplexData complexData, Foo foo);


    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        ComplexData complexData = new ComplexData();

        Foo foo = new Foo();
        foo.setIndex(2018);
        foo.setData("set_field_from_arg");
        Foo fooRet = setField(complexData, foo);
        Log.d("setField", String.valueOf(fooRet.getIndex()));
        Log.d("setField", fooRet.getData());

    }
}
