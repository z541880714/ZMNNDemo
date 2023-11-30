package com.lionel.zc.feature

class JMatrix(val w: Int, val h: Int, val stride: Int, val dataPtr: Long) {
    override fun toString(): String {
        return "w:$w,  h:$h, stride:$stride, dataPtr:$dataPtr"
    }

    fun releaseData() = NativeLib.ReleaseMatrixData(dataPtr)
}