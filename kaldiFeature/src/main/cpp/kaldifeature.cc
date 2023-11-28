#include <jni.h>
#include <string>


#include "feat-computer.h"
#include "matrix/matrix-common.h"
#include "util/kaldi-io.h"

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
    // h =

    Vector<float> head(w);
    head.Add(1);
    Vector<float> tail(w);
    tail.Add(1);

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
    //splice
    out.Resize(ceil(h * 1.0 / aub_sample), tmp2.NumCols());


    for (int i = 0; i < out.NumRows(); i++) {
        out.CopyRowFromVec(tmp2.Row(i * aub_sample), i);
    }

    write_feats(out, "../ccc");
}

void splice_test() {
    int w = 20, h = 20;
    kaldi::Matrix<kaldi::BaseFloat> a(h, w);
    a.Add(1);
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            a.Data()[i * a.Stride() + j] = (float) (i * w + j);
        }
    }
//    KALDI_LOG << " matrix a: " << a << " stride: " << a.Stride();
    Matrix<float> test;
    splice_feats(a, test);
}

using namespace kaldi;
extern "C" JNIEXPORT jstring JNICALL
Java_com_lionel_zc_kaldifeature_NativeLib_featureTest(
        JNIEnv *env,
        jobject /* this */, jstring wavfile, jstring dstfile) {
    std::string hello = "Hello from C++";

    const char *usage = "Usage: compute-feats <wavfile> <dstfile>\n";

    FeatComputer computer;

    const char *wave_file_c = env->GetStringUTFChars(wavfile, 0);
    const char *dstfile_c = env->GetStringUTFChars(dstfile, 0);
    computer.wav2fbank(wave_file_c, dstfile_c);
//    kaldi::Matrix<kaldi::BaseFloat> feature;
//    computer.compute_fbank(wavfile, &feature);
//    Matrix<float> out;
//    splice_feats(feature, out);



    return env->NewStringUTF(hello.c_str());
}