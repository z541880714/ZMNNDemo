#include <jni.h>
#include <android/asset_manager_jni.h>
#include <android/bitmap.h>
#include <android/log.h>

#include <jni.h>
#include <string>
#include <vector>
#include <sstream>
#include <thread>
#include <MNN/Tensor.hpp>


#include "MyUtil.h"
//
// Created by Lionel_zc on 2023/6/6.
//
#define JNI_PREFIX(arg) Java_com_lionel_zc_mnn_TextProcess_##arg


//loadModel  String modelPath, String vocabPath
extern "C" JNIEXPORT jint JNICALL
JNI_PREFIX(loadVocabFile)(JNIEnv *env, jclass thiz, jstring vocabPath) {
    //加载 vocab
    std::string s_vocabPath = JavaStringToString(env, vocabPath);
    return 0;
}

extern "C" JNIEXPORT jint JNICALL
JNI_PREFIX(nativeUpdateTensor)(JNIEnv *env, jclass clazz,
                               jlong tensorPtr, jintArray data) {
    auto tensor = (MNN::Tensor *) tensorPtr;

    LOGI("tensor data size:%d,  width:%d, height:%d, batch:%d,  buffer type:%d,  dimensions:%d",
         tensor->size(), tensor->width(), tensor->height(), tensor->batch(),
         tensor->buffer().type.code, tensor->dimensions());

    //    halide_type_int = 0,   //!< signed integers
    //    halide_type_uint = 1,  //!< unsigned integers
    //    halide_type_float = 2, //!< floating point numbers
    //    halide_type_handle = 3 //!< opaque pointer type (void *)
    LOGI("dim code: %d", tensor->getType().code);
    //        TENSORFLOW,
    //        CAFFE,
    //        CAFFE_C4
    LOGI("dim getDimensionType: %d", tensor->getDimensionType());
    int dim = tensor->buffer().dimensions;
    for (int i = 0; i < dim; i++) {
        int min = tensor->buffer().dim[i].min;
        int extent = tensor->buffer().dim[i].extent;
        int stride = tensor->buffer().dim[i].stride;
        LOGI("dim [%d] min: %d ,extent:%d, stride:%d", i, min, extent, stride);
    }
    LOGI("dim buffer dimensions: %d", tensor->buffer().dimensions);

    jint *intArrays = env->GetIntArrayElements(data, JNI_FALSE);
    memcpy(tensor->buffer().host, intArrays, 52 * sizeof(jint));
    auto *num = (int32_t *) tensor->buffer().host;
    return 0;
}

extern "C" JNIEXPORT jint JNICALL
JNI_PREFIX(resetTensor)(JNIEnv *env, jclass clazz, jlong tensorPtr) {
    auto tensor = (MNN::Tensor *) tensorPtr;
//    LOGI("tensor data size:%d,  width:%d, height:%d, batch:%d,  buffer type:%d",
//         tensor->size(), tensor->width(), tensor->height(), tensor->batch(),
//         tensor->buffer().type.code);
    for (int i = 0; i < tensor->size(); i++) {
        tensor->buffer().host[i] = 0;
    }
    return 0;
}



