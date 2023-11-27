//
// Created by Lionel_zc on 2023/6/7.
//

#include "MyUtil.h"


std::string JavaStringToString(JNIEnv *env, jstring str) {
    if (env == nullptr || str == nullptr) {
        return "";
    }
    const jchar *chars = env->GetStringChars(str, NULL);
    std::u16string u16_string(reinterpret_cast<const char16_t *>(chars), env->GetStringLength(str));
    std::string u8_string = std::wstring_convert<std::codecvt_utf8_utf16<char16_t>, char16_t>{}
            .to_bytes(u16_string);

    env->ReleaseStringChars(str, chars);
    return u8_string;
}

jstring StringToJavaString(JNIEnv *env, const std::string &u8_string) {
    std::u16string u16_string = std::wstring_convert<std::codecvt_utf8_utf16<char16_t>, char16_t>{}
            .from_bytes(u8_string);
    auto result = env->NewString(reinterpret_cast<const jchar *>(u16_string.data()),
                                 u16_string.length());
    return result;
}
