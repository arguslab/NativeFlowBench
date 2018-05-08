//
// Created by Xingwei Lin on 14/1/18.
//

#include <jni.h>


#define LOG_TAG    "set_field_from_branches"
#define LOGI(...)  __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)
#define LOGE(...)  __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)
#define LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__)

extern "C" {
JNIEXPORT jobject JNICALL
Java_org_arguslab_native_1set_1field_1from_1branches_MainActivity_setField(JNIEnv *env,
                                                                           jobject thisObj,
                                                                           jobject complexData,
                                                                           jobject otherData,
                                                                           jobject fooArg,
                                                                           jint index);

}


JNIEXPORT jobject JNICALL
Java_org_arguslab_native_1set_1field_1from_1branches_MainActivity_setField(JNIEnv *env,
                                                                           jobject thisObj,
                                                                           jobject complexData,
                                                                           jobject otherData,
                                                                           jobject fooArg,
                                                                           jint index) {
    jclass complexDataClass = env->GetObjectClass(complexData);
    jfieldID fooFieldID = env->GetFieldID(complexDataClass, "foo",
                                          "Lorg/arguslab/native_set_field_from_branches/Foo;");
    jobject fooRet = NULL;
    if (index == 1) {
        env->SetObjectField(complexData, fooFieldID, fooArg);
        fooRet = env->GetObjectField(complexData, fooFieldID);
    } else if (index == 2) {
        jclass fooClass = env->FindClass("org/arguslab/native_set_field_from_branches/Foo");
        jmethodID constructionMethod = env->GetMethodID(fooClass, "<init>", "()V");
        jobject foo = env->NewObject(fooClass, constructionMethod);
        jfieldID dataFieldID = env->GetFieldID(fooClass, "data",
                                               "Ljava/lang/String;");
        jstring data = env->NewStringUTF("set_field_from_native");
        env->SetObjectField(foo, dataFieldID, data);
        jfieldID indexFieldID = env->GetFieldID(fooClass, "index", "I");
        env->SetIntField(foo, indexFieldID, 2018);

        env->SetObjectField(complexData, fooFieldID, foo);
        fooRet = env->GetObjectField(complexData, fooFieldID);
    } else if (index == 3) {
        jobject foo = env->GetObjectField(otherData, fooFieldID);
        env->SetObjectField(complexData, fooFieldID, foo);
        fooRet = env->GetObjectField(complexData, fooFieldID);
    }
    return fooRet;
}

