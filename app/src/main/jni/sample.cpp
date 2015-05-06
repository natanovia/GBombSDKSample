#include <jni.h>
#include <android/log.h>
#include "GbombClient.h"

#define LOG_TAG    "main"
#define LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG,LOG_TAG,__VA_ARGS__)

extern "C" {

    JavaVM* javaVM = NULL;
    jclass activityClass;
    jobject activityObj;

    JNIEXPORT void Java_com_gbombgames_sdk_sample_MainActivity_login(JNIEnv* env, jobject obj) {

        LOGD("start jni");
        IGbombClient *client = GbombClient::getInstance();
        client->init("YOUR_GAME_ID");

        env->GetJavaVM(&javaVM);
        /* Same as sObj.getClass() */
        jclass cls = env->GetObjectClass(obj);
        activityClass = (jclass) env->NewGlobalRef(cls);
        activityObj = env->NewGlobalRef(obj);

        client->login([](const int code, const std::string data) {

            LOGD("start callback");

            JNIEnv *env;
            javaVM->AttachCurrentThread(&env, NULL);

            if ( activityClass != NULL ) {

                /* Same as clazz.getMethod("loginCallback", String.class) - assuming non-static */
                jmethodID methodId = env->GetMethodID(activityClass, "loginCallback", "(ILjava/lang/String;)V");

                if (methodId == 0) {

                    LOGD("cannot find callback method");

                } else { /* make sure we found the method */

                    LOGD("found callback method");

                    /* Create a new Java String */
                    jstring jstrData = env->NewStringUTF(data.c_str());

                    if ( jstrData != NULL ) {

                        /* Same as methodId.invoke(sObj, code, jstrData) */
                        env->CallVoidMethod(activityObj, methodId, code, jstrData);
                    }
                }
            }
        });
    }
}
