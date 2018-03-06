package org.arguslab.native_heap_summary;

import android.annotation.SuppressLint;
import android.app.Activity;
import android.os.Bundle;
import android.util.Log;


public class MainActivity extends Activity {

    static {
        System.loadLibrary("heap_summary"); // "heap_summary.dll" in Windows, "libheap_summary.so" in Unixes
    }

    public static native Foo fieldAssignmentFromArg(SummaryBasedUtil summaryBasedUtil, Foo foo);

    public static native Foo fieldAssignmentFromNative(SummaryBasedUtil summaryBasedUtil);

    public static native Foo fieldAssignmentFromAnotherObject(SummaryBasedUtil summaryBasedUtil, SummaryBasedUtil summaryBasedUtilAnother);

    public static native Foo fieldAssignmentFromBranches(SummaryBasedUtil summaryBasedUtil, SummaryBasedUtil summaryBasedUtilAnother, Foo foo, char flag);

    @SuppressLint("LongLogTag")
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        SummaryBasedUtil summaryBasedUtil = new SummaryBasedUtil();

        Foo foo = new Foo();
        foo.fooNum = 2017;
        foo.fooStr = "fieldAssignmentFromArg";
        Foo fooFromArg = fieldAssignmentFromArg(summaryBasedUtil, foo);
        Log.d("fieldAssignmentFromArg", String.valueOf(fooFromArg.fooNum));
        Log.d("fieldAssignmentFromArg", fooFromArg.fooStr);

        Foo fooFromNative = fieldAssignmentFromNative(summaryBasedUtil);
        Log.d("fieldAssignmentFromNative", String.valueOf(fooFromNative.fooNum));
        Log.d("fieldAssignmentFromNative", fooFromNative.fooStr);

        SummaryBasedUtil summaryBasedUtilAnother = new SummaryBasedUtil();
        Foo fooAnother = new Foo();
        fooAnother.fooNum = 2019;
        fooAnother.fooStr = "fieldAssignmentFromAnotherObject";
        summaryBasedUtilAnother.foo = fooAnother;
        Foo fooFromAnotherObject = fieldAssignmentFromAnotherObject(summaryBasedUtil, summaryBasedUtilAnother);
        Log.d("fieldAssignmentFromAnotherObject", String.valueOf(fooFromAnotherObject.fooNum));
        Log.d("fieldAssignmentFromAnotherObject", fooFromAnotherObject.fooStr);

        char flag = 'A';
        Foo fooFromBranches = fieldAssignmentFromBranches(summaryBasedUtil, summaryBasedUtilAnother, foo, flag);
        Log.d("fieldAssignmentFromBranches", String.valueOf(fooFromBranches.fooNum));
        Log.d("fieldAssignmentFromBranches", fooFromBranches.fooStr);

    }
}