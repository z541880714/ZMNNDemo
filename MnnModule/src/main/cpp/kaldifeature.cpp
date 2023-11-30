#include <jni.h>
#include <string>


#include "feat-computer.h"
#include "matrix/matrix-common.h"
#include "util/kaldi-io.h"
#include "MyUtil.h"

#define JNIFunc(name) Java_com_lionel_zc_feature_NativeLib_##name

using namespace kaldi;
typedef MatrixIndexT INT;

void write_feats(Matrix<float> &feats, std::string path) {
    Output wavKi(std::string(path), false, false);
    feats.Write(wavKi.Stream(), false);
}

void splice_feats(Matrix<float> &feats, Matrix<float> &out) {
    INT w = feats.NumCols();
    INT h = feats.NumRows();
    int left_context = 2, right_context = 2, aub_sample = 3;

    Matrix<float> tmp1(h + (left_context + right_context), w);
    tmp1.CopyRowFromVec(feats.Row(0), 0);
    tmp1.CopyRowFromVec(feats.Row(0), 1);
    tmp1.Range(2, feats.NumRows(), 0, feats.NumCols()).CopyFromMat(feats);
    tmp1.Row(2 + h).CopyFromVec(feats.Row(h - 1));
    tmp1.Row(2 + h + 1).CopyFromVec(feats.Row(h - 1));

    int multiple = left_context + right_context + 1;
    Matrix<float> tmp2(h, w * multiple);

    for (int i = 0; i < multiple; i++) {
        tmp2.Range(0, h, w * i, w).CopyFromMat(tmp1.Range(i, h, 0, w));
    }
    out.Resize(ceil(h * 1.0 / aub_sample), tmp2.NumCols());
    for (int i = 0; i < out.NumRows(); i++) {
        out.CopyRowFromVec(tmp2.Row(i * aub_sample), i);
    }
}

jobject CreateJMatrix(JNIEnv *env, kaldi::Matrix<kaldi::BaseFloat> &matrix) {

    auto *data = (float *) malloc(matrix.SizeInBytes());
    memcpy(data, matrix.Data(), matrix.SizeInBytes());

    jclass JMatrix = env->FindClass("com/lionel/zc/feature/JMatrix");
    jmethodID contruct = env->GetMethodID(JMatrix, "<init>", "(IIIJ)V");
    jobject instance = env->NewObject(JMatrix, contruct, matrix.NumCols(), matrix.NumCols(),
                                      matrix.Stride(), *(long *) (&data));
    return instance;
}

extern "C" JNIEXPORT void JNICALL
JNIFunc(ReleaseMatrixData)(JNIEnv *env, jobject, jlong ptr) {
    auto *pp2 = (float *) ptr;
    if (pp2) {
        free(pp2);
    }
}

extern "C"
JNIEXPORT jobject JNICALL
JNIFunc(fbank)(JNIEnv *env, jclass, jstring wavfile, jstring dstfile) {
    FeatComputer computer;

    const char *wave_file_c = env->GetStringUTFChars(wavfile, 0);
    const char *dstfile_c = env->GetStringUTFChars(dstfile, 0);
    LOGI("wave file: %s", wave_file_c);

    kaldi::Input wavKi;
    bool binary = true;
    int ret = wavKi.Open(wave_file_c, &binary);
    KALDI_LOG << "open wavfile:" << wave_file_c << " open file ret: " << ret;
    std::istream &wavis = wavKi.Stream();

    kaldi::WaveData waveData;
    waveData.Read(wavis);
    waveData.FormatData();
    LOGI("waveData.Duration:%f, sampFreq:%f, cols:%d,  rows:%d", waveData.Duration(),
         waveData.SampFreq(), waveData.Data().NumCols(), waveData.Data().NumRows());
    kaldi::SubVector<kaldi::BaseFloat> waveform(waveData.Data(), 0); //-1:expect mono

    kaldi::Matrix<kaldi::BaseFloat> feature;
    computer.compute_fbank(wave_file_c, &feature);
    int rows = feature.NumCols();
    int cols = feature.NumRows();
    LOGI("rows: %d, cols:%d", rows, cols);
    Matrix<float> out;
    splice_feats(feature, out);
    LOGI("sizeOfByte:%zd,  stride:%d, col:%d, rows:%d", out.SizeInBytes(), out.Stride(),
         out.NumCols(), out.NumRows());
    return CreateJMatrix(env, out);
}