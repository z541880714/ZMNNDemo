package com.linoel.example.app

import android.os.Bundle
import android.util.Log
import androidx.activity.ComponentActivity
import androidx.activity.compose.setContent
import androidx.compose.foundation.layout.fillMaxSize
import androidx.compose.material.MaterialTheme
import androidx.compose.material.Surface
import androidx.compose.material.Text
import androidx.compose.runtime.Composable
import androidx.compose.ui.Modifier
import androidx.compose.ui.tooling.preview.Preview
import com.linoel.example.app.ui.theme.MyMnnDemoTheme
import com.linoel.example.mydemo.MyMnnApi
import com.linoel.example.mydemo.mnn.processText
import com.linoel.example.mydemo.mnn.testImage
import com.linoel.example.mydemo.mnn.testText
import kotlinx.coroutines.CoroutineScope
import kotlinx.coroutines.Dispatchers.IO
import kotlinx.coroutines.launch

class MainActivity : ComponentActivity() {
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContent {
            MyMnnDemoTheme {
                // A surface container using the 'background' color from the theme
                Surface(
                    modifier = Modifier.fillMaxSize(),
                    color = MaterialTheme.colors.background
                ) {
                    Greeting("Android")
                }
            }
        }
        startWork2()
    }

    private val sourceDir get() = "data/local/tmp/MNNDemo"
    private val TargetPicPath get() = "$sourceDir/pikaqiu.jpg"
    private val vocabPath get() = "$sourceDir/cn_vocab.txt"
    private val imgModelPath get() = "$sourceDir/vit-b-16-img-fp32.mnn"
    private val textModelPath get() = "$sourceDir/cn_vocab.txt"
    var mnnApi = MyMnnApi
    private fun startWork1() = CoroutineScope(IO).launch {
        testImage()
        testText()
    }

    private fun startWork2() = CoroutineScope(IO).launch {
        val modelDir = "data/local/tmp/MNNDemo"
        mnnApi.loadImageModel("$modelDir/vit-b-16-img-fp32.mnn")
        mnnApi.loadTextModel(
            "$modelDir/vit-b-16-txt-fp32.mnn",
            "$modelDir/cn_vocab.txt"
        )
        mnnApi.analyzeImageFeature(TargetPicPath)
        mnnApi.releaseImageModel()

        mnnApi.analyzeTextFeature("一个在海上游泳的乌龟")
            .also { Log.i("log_zc", "test-> testText: score:$it") }
        mnnApi.analyzeTextFeature("小火龙").also { Log.i("log_zc", "test-> testText: score:$it") }
        mnnApi.analyzeTextFeature("妙蛙种子").also { Log.i("log_zc", "test-> testText: score:$it") }
        mnnApi.analyzeTextFeature("杰尼龟").also { Log.i("log_zc", "test-> testText: score:$it") }
        mnnApi.analyzeTextFeature("皮卡丘").also { Log.i("log_zc", "test-> testText: score:$it") }

    }
}

@Composable
fun Greeting(name: String) {
    Text(text = "Hello $name!")
}

@Preview(showBackground = true)
@Composable
fun DefaultPreview() {
    MyMnnDemoTheme {
        Greeting("Android")
    }
}