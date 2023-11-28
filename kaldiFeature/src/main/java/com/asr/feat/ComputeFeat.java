package com.asr.feat;

public class ComputeFeat {
    static {
        System.loadLibrary("compute_feats");
    }

    public native static long init();

}
