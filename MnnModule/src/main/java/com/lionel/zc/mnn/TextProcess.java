package com.lionel.zc.mnn;

import android.util.Log;

import androidx.annotation.NonNull;

import java.io.Serializable;

public class TextProcess implements Serializable {
    static {
        System.loadLibrary("myDemo");
    }

    public static int updateTensor(@NonNull MNNNetInstance.Session.Tensor tensor, int[] data) {
        nativeUpdateTensor(tensor.instance(), data);
        Log.i("log_zc", "updateTensor: tensor instance:" + tensor.instance());
        return 0;
    }

    public static void resetTensor(MNNNetInstance.Session.Tensor tensor) {
        resetTensor(tensor.instance());
    }


    public native static int loadVocabFile(String vocabPath);

    private native static int nativeUpdateTensor(long tensor, int[] data);

    private native static int resetTensor(long Tensor);
}
