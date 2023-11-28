package com.lionel.zc.kaldifeature

import android.content.Context
import android.util.Log
import com.asr.feat.ComputeFeat
import java.io.FileInputStream
import java.io.FileOutputStream

class NativeLib {

    /**
     * A native method that is implemented by the 'kaldifeature' native library,
     * which is packaged with this application.
     */
    external fun featureTest(waveFile: String, dstFile: String): String

    companion object {
        // Used to load the 'kaldifeature' library on application startup.
        init {
            System.loadLibrary("kaldifeature")
        }

        fun test(context: Context) {
            val targetFile = FileOutputStream("${context.getExternalFilesDir(null)}/aaa.wav")
            context.assets.open("aaa.wav").use {
                targetFile.use { out ->
                    it.copyTo(out)
                }
            }

//            val ret = ComputeFeat.init();
//            Log.i("log_zc", "NativeLib-> test: ret:$ret")
        }

    }
}