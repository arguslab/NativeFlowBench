package org.arguslab.native_set_field_from_branches;

import android.app.Activity;
import android.os.Bundle;
import android.util.Log;

import java.util.Random;

public class MainActivity extends Activity {

    static {
        System.loadLibrary("set_field_from_branches"); // "set_field_from_branches.dll" in Windows, "libset_field_from_branches.so" in Unixes
    }

    public static native Foo setField(ComplexData complexData, ComplexData otherData, Foo foo, int index);

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

        Foo fooArg = new Foo();
        fooArg.setIndex(2018);
        fooArg.setData("set_field_from_arg");

        Random random = new Random();
        int index = random.nextInt(4);
        Foo fooRet = setField(complexData, otherData, fooArg, index);
        Log.d("set_field_from_branches", String.valueOf(fooRet.getIndex()));
        Log.d("set_field_from_branches", fooRet.getData());
    }
}
