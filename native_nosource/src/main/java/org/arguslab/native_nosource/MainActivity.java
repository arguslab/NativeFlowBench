package org.arguslab.native_nosource;

import android.Manifest;
import android.app.Activity;
import android.content.Context;
import android.content.pm.PackageManager;
import android.os.Bundle;
import android.util.Log;

public class MainActivity extends Activity {

    static {
        System.loadLibrary("nosource"); // "nosource.dll" in Windows, "libnosource.so" in Unixes
    }

    public static native String getData();

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        String data = getData();
        Log.i("Data", data);
    }

}
