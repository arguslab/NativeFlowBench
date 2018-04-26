//
// Created by Xingwei Lin on 3/4/18.
//

#include <jni.h>
#include <android/log.h>
#include <stddef.h>

#define LOG_TAG    "multiple_interactions"
#define LOGI(...)  __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)
#define LOGE(...)  __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)
#define LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__)

extern "C" {
JNIEXPORT void JNICALL
Java_org_arguslab_native_1multiple_1interactions_MainActivity_propagateImei(JNIEnv *env, jobject thisObj,
                                                                      jobject mContext);

JNIEXPORT void JNICALL
Java_org_arguslab_native_1multiple_1interactions_MainActivity_leakImei(JNIEnv *env, jobject thisObj,
                                                                       jstring imei);

}

const char *getCharFromString(JNIEnv *env, jstring string) {
    if (string == NULL)
        return NULL;

    return env->GetStringUTFChars(string, 0);
}

jstring getImei(JNIEnv *env, jobject context) {
    jclass cls = env->FindClass("android/content/Context");
    jmethodID mid = env->GetMethodID(cls, "getSystemService",
                                     "(Ljava/lang/String;)Ljava/lang/Object;");
    jfieldID fid = env->GetStaticFieldID(cls, "TELEPHONY_SERVICE",
                                         "Ljava/lang/String;");
    jstring str = (jstring) env->GetStaticObjectField(cls, fid);
    jobject telephony = env->CallObjectMethod(context, mid, str);
    cls = env->FindClass("android/telephony/TelephonyManager");
    mid = env->GetMethodID(cls, "getDeviceId", "()Ljava/lang/String;");
    jstring imei = (jstring) env->CallObjectMethod(telephony, mid); // source
    return imei;
}

JNIEXPORT void JNICALL
Java_org_arguslab_native_1multiple_1interactions_MainActivity_propagateImei(JNIEnv *env, jobject thisObj,
                                                                      jobject mContext) {
    jstring deviceid = getImei(env, mContext);
    jclass cd = env->FindClass("org/arguslab/native_multiple_interactions/MainActivity");
    jmethodID constructionMethod = env->GetMethodID(cd, "<init>", "()V");
    jobject ma = env->NewObject(cd, constructionMethod);
    jmethodID gd = env->GetMethodID(cd, "toNativeAgain", "(Ljava/lang/String;)V");
    env->CallVoidMethod(ma, gd, deviceid);
    return;
}

JNIEXPORT void JNICALL
Java_org_arguslab_native_1multiple_1interactions_MainActivity_leakImei(JNIEnv *env, jobject thisObj,
                                                                       jstring imei) {
    LOGI("%s", getCharFromString(env, imei)); // leak
    return;
}