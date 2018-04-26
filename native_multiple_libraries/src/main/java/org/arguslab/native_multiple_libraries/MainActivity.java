package org.arguslab.native_multiple_libraries;

import android.app.Activity;
import android.os.Bundle;

import android.Manifest;
import android.content.pm.PackageManager;
import android.telephony.TelephonyManager;

/**
 * @author Xingwei Lin
 * @testcase_name Native_Multiple_Libraries
 * @author_mail xwlin.roy@gmail.com
 * @description The value v of a source is sent to native lib via jni.
 * native lib is not leaking the data.
 * @dataflow
 * @number_of_leaks 0
 * @challenges The analysis must be able to track data flow in both java and native to avoid the false positive.
 */
public class MainActivity extends Activity {

    static {
        System.loadLibrary("master"); // "master.dll" in Windows, "libmaster.so" in Unixes
        System.loadLibrary("foo"); // "foo.dll" in Windows, "libfoo.so" in Unixes
    }

    public static native void masterSend(String data);

    public static native void fooSend(String data);

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        if (checkSelfPermission(Manifest.permission.READ_PHONE_STATE) != PackageManager.PERMISSION_GRANTED) {
            requestPermissions(new String[]{Manifest.permission.READ_PHONE_STATE}, 1);
        }
    }

    private void leakImei() {
        TelephonyManager tel = (TelephonyManager) getSystemService(TELEPHONY_SERVICE);
        String imei = tel.getDeviceId(); // source
        masterSend(imei);
    }

    @Override
    public void onRequestPermissionsResult(int requestCode, String[] permissions, int[] grantResults) {
        switch (requestCode) {
            case 1: {
                leakImei();
                return;
            }
        }
    }
}
