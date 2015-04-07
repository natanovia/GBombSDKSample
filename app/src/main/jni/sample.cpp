#include <jni.h>
#include <android/log.h>
#include "GbombClient.h"

#define  LOG_TAG    "main"
#define  LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG,LOG_TAG,__VA_ARGS__)

extern "C" {
    JNIEXPORT void Java_com_gbombgames_sdk_sample_MainActivity_login(JNIEnv* env, jobject thiz) {
        LOGD("start jni");
        IGbombClient *client = GbombClient::getInstance();
        client->init("YOUR_GAME_ID");
        static JNIEnv* sEnv = env;
        static jobject sObj = (jobject)env->NewGlobalRef(thiz);

        client->login([](const int code, const std::string data) {
           LOGD("start callback");

           jclass cls = sEnv->GetObjectClass(sObj);
           jmethodID mid = sEnv->GetMethodID(cls, "loginCallback", "(ILjava/lang/String;)V");
           if (mid == 0) {
            LOGD("cannot find method");
           } else {
            LOGD("found it");
           }
           jstring jstrData = sEnv->NewStringUTF(data.c_str());
           sEnv->CallVoidMethod(sObj, mid, code, jstrData);
        });
    }
}
