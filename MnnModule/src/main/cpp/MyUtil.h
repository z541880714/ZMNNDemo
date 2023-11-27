//
// Created by Lionel_zc on 2023/6/7.
//

#ifndef MYDEMO_TEXTUTIL_H
#define MYDEMO_TEXTUTIL_H

#include <locale>
#include <codecvt>
#include <string>
#include <jni.h>
#include "android/log.h"

#define TAG "log_zc_jni" // 这个是自定义的LOG的标识
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG,TAG ,__VA_ARGS__) // 定义LOGD类型
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO,TAG ,__VA_ARGS__) // 定义LOGI类型
#define LOGW(...) __android_log_print(ANDROID_LOG_WARN,TAG ,__VA_ARGS__) // 定义LOGW类型
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR,TAG ,__VA_ARGS__) // 定义LOGE类型
#define LOGF(...) __android_log_print(ANDROID_LOG_FATAL,TAG ,__VA_ARGS__) // 定义LOGF类型

class MyUtil {

public :

};


std::string JavaStringToString(JNIEnv *env, jstring str);

jstring StringToJavaString(JNIEnv *env, const std::string &u8_string);


#endif //MYDEMO_TEXTUTIL_H
