//
// Created by Xingwei Lin on 14/1/18.
//

#include <jni.h>


#define LOG_TAG    "heap_summary"
#define LOGI(...)  __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)
#define LOGE(...)  __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)
#define LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__)

extern "C" {
JNIEXPORT jobject JNICALL
Java_org_arguslab_native_1heap_1summary_MainActivity_fieldAssignmentFromArg(JNIEnv *env,
                                                                            jobject thisObj,
                                                                            jobject summaryBasedUtil,
                                                                            jobject foo);
JNIEXPORT jobject JNICALL
Java_org_arguslab_native_1heap_1summary_MainActivity_fieldAssignmentFromNative(JNIEnv *env,
                                                                               jobject thisObj,
                                                                               jobject summaryBasedUtil);

JNIEXPORT jobject JNICALL
Java_org_arguslab_native_1heap_1summary_MainActivity_fieldAssignmentFromAnotherObject(JNIEnv *env,
                                                                                      jobject thisObj,
                                                                                      jobject summaryBasedUtil,
                                                                                      jobject summaryBasedUtilAnother);
JNIEXPORT jobject JNICALL
Java_org_arguslab_native_1heap_1summary_MainActivity_fieldAssignmentFromBranches(JNIEnv *env,
                                                                                 jobject thisObj,
                                                                                 jobject summaryBasedUtil,
                                                                                 jobject summaryBasedUtilAnother,
                                                                                 jobject foo,
                                                                                 jchar flag);
}


JNIEXPORT jobject JNICALL
Java_org_arguslab_native_1heap_1summary_MainActivity_fieldAssignmentFromArg(JNIEnv *env,
                                                                            jobject thisObj,
                                                                            jobject summaryBasedUtil,
                                                                            jobject foo) {
    jclass summaryBasedUtilClass = env->GetObjectClass(summaryBasedUtil);
    jfieldID fooFieldID = env->GetFieldID(summaryBasedUtilClass, "foo",
                                          "Lorg/arguslab/native_heap_summary/Foo;");
    env->SetObjectField(summaryBasedUtil, fooFieldID, foo);
    jobject returnFoo = env->GetObjectField(summaryBasedUtil, fooFieldID);
    return returnFoo;
}

JNIEXPORT jobject JNICALL
Java_org_arguslab_native_1heap_1summary_MainActivity_fieldAssignmentFromNative(JNIEnv *env,
                                                                               jobject thisObj,
                                                                               jobject summaryBasedUtil) {

    jclass fooClass = env->FindClass("org/arguslab/native_heap_summary/Foo");
    jmethodID constructionMethod = env->GetMethodID(fooClass, "<init>", "()V");
    jobject fooObject = env->NewObject(fooClass, constructionMethod);

    jfieldID fooStrFieldID = env->GetFieldID(fooClass, "fooStr",
                                             "Ljava/lang/String;");
    jstring fooStr = env->NewStringUTF("fieldAssignmentFromNative");
    env->SetObjectField(fooObject, fooStrFieldID, fooStr);
    jfieldID fooNumFieldID = env->GetFieldID(fooClass, "fooNum", "I");
    env->SetIntField(fooObject, fooNumFieldID, 2018);

    jclass summaryBasedUtilClass = env->GetObjectClass(summaryBasedUtil);
    jfieldID fooFieldID = env->GetFieldID(summaryBasedUtilClass, "foo",
                                          "Lorg/arguslab/native_heap_summary/Foo;");
    env->SetObjectField(summaryBasedUtil, fooFieldID, fooObject);
    jobject returnFoo = env->GetObjectField(summaryBasedUtil, fooFieldID);
    return returnFoo;
}

JNIEXPORT jobject JNICALL
Java_org_arguslab_native_1heap_1summary_MainActivity_fieldAssignmentFromAnotherObject(JNIEnv *env,
                                                                                      jobject thisObj,
                                                                                      jobject summaryBasedUtil,
                                                                                      jobject summaryBasedUtilAnother) {

    jclass summaryBasedUtilClass = env->GetObjectClass(summaryBasedUtil);
    jfieldID fooFieldID = env->GetFieldID(summaryBasedUtilClass, "foo",
                                          "Lorg/arguslab/native_heap_summary/Foo;");

    jobject fooAnother = env->GetObjectField(summaryBasedUtilAnother, fooFieldID);
    env->SetObjectField(summaryBasedUtil, fooFieldID, fooAnother);
    jobject returnFoo = env->GetObjectField(summaryBasedUtil, fooFieldID);
    return returnFoo;
}

JNIEXPORT jobject JNICALL
Java_org_arguslab_native_1heap_1summary_MainActivity_fieldAssignmentFromBranches(JNIEnv *env,
                                                                                 jobject thisObj,
                                                                                 jobject summaryBasedUtil,
                                                                                 jobject summaryBasedUtilAnother,
                                                                                 jobject foo,
                                                                                 jchar flag) {
    jclass summaryBasedUtilClass = env->GetObjectClass(summaryBasedUtil);
    jfieldID fooFieldID = env->GetFieldID(summaryBasedUtilClass, "foo",
                                          "Lorg/arguslab/native_heap_summary/Foo;");
    if (flag == 'A') {
        env->SetObjectField(summaryBasedUtil, fooFieldID, foo);
        jobject returnFromArg = env->GetObjectField(summaryBasedUtil, fooFieldID);
        return returnFromArg;
    } else if (flag == 'N') {
        jclass fooClass = env->FindClass("org/arguslab/native_heap_summary/Foo");
        jmethodID constructionMethod = env->GetMethodID(fooClass, "<init>", "()V");
        jobject fooObject = env->NewObject(fooClass, constructionMethod);
        jfieldID fooStrFieldID = env->GetFieldID(fooClass, "fooStr",
                                                 "Ljava/lang/String;");
        jstring fooStr = env->NewStringUTF("fieldAssignmentFromNative");
        env->SetObjectField(fooObject, fooStrFieldID, fooStr);
        jfieldID fooNumFieldID = env->GetFieldID(fooClass, "fooNum", "I");
        env->SetIntField(fooObject, fooNumFieldID, 2018);
        env->SetObjectField(summaryBasedUtil, fooFieldID, fooObject);
        jobject returnFromNative = env->GetObjectField(summaryBasedUtil, fooFieldID);
        return returnFromNative;
    } else if (flag == 'O') {
        jobject fooAnother = env->GetObjectField(summaryBasedUtilAnother, fooFieldID);
        env->SetObjectField(summaryBasedUtil, fooFieldID, fooAnother);
        jobject returnFromAnotherObject = env->GetObjectField(summaryBasedUtil, fooFieldID);
        return returnFromAnotherObject;
    } else {
        return foo;
    }


}