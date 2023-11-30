package com.lionel.zc.feature

import android.content.Context
import android.util.Log
import java.io.File
import java.io.FileOutputStream

object NativeLib {
    init {
        System.loadLibrary("mnn-module")
    }

    @JvmStatic
    external fun fbank(waveFile: String, dstFile: String): JMatrix

    external fun ReleaseMatrixData(ptr: Long)


    @JvmStatic
    fun test(context: Context) {
        val targetFile = File("${context.getExternalFilesDir(null)}/aaa.wav")
        val outFileDir = "${context.getExternalFilesDir(null)}/bbb"
        val fos = FileOutputStream(targetFile)
        context.assets.open("aaa.wav").use {
            fos.use { out ->
                it.copyTo(out)
            }
        }
        val matrix = fbank(targetFile.path, outFileDir);
        Log.i("log_zc", "NativeLib-> test:  matrix: $matrix")
    }


}