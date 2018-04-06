//
// Created by Xingwei Lin on 14/1/18.
//

#include <jni.h>


#define LOG_TAG    "set_field_from_native"
#define LOGI(...)  __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)
#define LOGE(...)  __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)
#define LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__)

extern "C" {
JNIEXPORT jobject JNICALL
Java_org_arguslab_native_1set_1field_1from_1native_MainActivity_setField(JNIEnv *env,
                                                                             jobject thisObj,
                                                                             jobject comlexData);

}


JNIEXPORT jobject JNICALL
Java_org_arguslab_native_1set_1field_1from_1native_MainActivity_setField(JNIEnv *env,
                                                                             jobject thisObj,
                                                                             jobject comlexData) {
    jclass fooClass = env->FindClass("org/arguslab/native_set_field_from_native/Foo");
    jmethodID constructionMethod = env->GetMethodID(fooClass, "<init>", "()V");
    jobject foo = env->NewObject(fooClass, constructionMethod);

    jfieldID dataFieldID = env->GetFieldID(fooClass, "data",
                                             "Ljava/lang/String;");
    jstring data = env->NewStringUTF("set_field_from_native");
    env->SetObjectField(foo, dataFieldID, data);
    jfieldID indexFieldID = env->GetFieldID(fooClass, "index", "I");
    env->SetIntField(foo, indexFieldID, 2018);

    jclass complexDataClass = env->GetObjectClass(comlexData);
    jfieldID fooFieldID = env->GetFieldID(complexDataClass, "foo",
                                          "Lorg/arguslab/native_set_field_from_native/Foo;");
    env->SetObjectField(comlexData, fooFieldID, foo);
    jobject fooRet = env->GetObjectField(comlexData, fooFieldID);
    return fooRet;
}

