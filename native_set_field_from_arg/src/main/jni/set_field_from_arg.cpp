//
// Created by Xingwei Lin on 14/1/18.
//

#include <jni.h>


#define LOG_TAG    "set_field_from_arg"
#define LOGI(...)  __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)
#define LOGE(...)  __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)
#define LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__)

extern "C" {
JNIEXPORT jobject JNICALL
Java_org_arguslab_native_1set_1field_1from_1arg_MainActivity_set_1field(JNIEnv *env,
                                                                            jobject thisObj,
                                                                            jobject comlexData,
                                                                            jobject foo);

}


JNIEXPORT jobject JNICALL
Java_org_arguslab_native_1set_1field_1from_1arg_MainActivity_set_1field(JNIEnv *env,
                                                                            jobject thisObj,
                                                                            jobject comlexData,
                                                                            jobject foo) {
    jclass complexDataClass = env->GetObjectClass(comlexData);
    jfieldID fooFieldID = env->GetFieldID(complexDataClass, "foo",
                                          "Lorg/arguslab/native_set_field_from_arg/Foo;");
    env->SetObjectField(comlexData, fooFieldID, foo);
    jobject fooRet = env->GetObjectField(comlexData, fooFieldID);
    return fooRet;
}

