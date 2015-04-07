#include <jni.h>
#include <android/log.h>
#include "GbombClient.h"

#define LOG_TAG    "main"
#define LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG,LOG_TAG,__VA_ARGS__)

extern "C" {
    JNIEXPORT void Java_com_gbombgames_sdk_sample_MainActivity_login(JNIEnv* env, jobject thiz) {

        LOGD("start jni");
        IGbombClient *client = GbombClient::getInstance();
        client->init("YOUR_GAME_ID");
        static JNIEnv* sEnv = env;
        static jobject sObj = (jobject)env->NewGlobalRef(thiz);

        client->login([](const int code, const std::string data) {

            LOGD("start callback");

            /* Same as sObj.getClass() */
            jclass clazz = sEnv->GetObjectClass(sObj);

            if ( clazz != NULL ) {

                /* Same as clazz.getMethod("loginCallback", String.class) - assuming non-static */
                jmethodID methodId = sEnv->GetMethodID(clazz, "loginCallback", "(ILjava/lang/String;)V");

                if (methodId == 0) {

                    LOGD("cannot find callback method");

                } else { /* make sure we found the method */

                    LOGD("found callback method");

                    /* Create a new Java String */
                    jstring jstrData = sEnv->NewStringUTF(data.c_str());

                    if ( jstrData != NULL ) {

                        /* Same as methodId.invoke(sObj, code, jstrData) */
                        sEnv->CallVoidMethod(sObj, methodId, code, jstrData);
                    }
                }
            }
        });
    }
}
