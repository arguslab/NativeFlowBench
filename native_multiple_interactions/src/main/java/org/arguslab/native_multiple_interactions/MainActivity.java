package org.arguslab.native_multiple_interactions;

import android.Manifest;
import android.app.Activity;
import android.content.Context;
import android.content.pm.PackageManager;
import android.os.Bundle;

public class MainActivity extends Activity {

    static {
        System.loadLibrary("multiple_interactions"); // "multiple_interactions.dll" in Windows, "libmultiple_interactions.so" in Unixes
    }

    public static native void propagateImei(Context myContext);

    public static native void leakImei(String imei);

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        if(checkSelfPermission(Manifest.permission.READ_PHONE_STATE) != PackageManager.PERMISSION_GRANTED) {
            requestPermissions(new String[]{Manifest.permission.READ_PHONE_STATE}, 1);
        }
    }

    private void toNative() {
        propagateImei(this.getApplicationContext()); // source

    }

    public void toNativeAgain(String data) {
        leakImei(data);
    }

    @Override
    public void onRequestPermissionsResult(int requestCode, String[] permissions, int[] grantResults) {
        switch (requestCode) {
            case 1: {
                toNative();
                return;
            }
        }
    }
}
