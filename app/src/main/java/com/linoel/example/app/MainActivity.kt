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
import com.lionel.zc.kaldifeature.NativeLib
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
        startWork1()
        startWork2()
    }

    private val sourceDir get() = "data/local/tmp/MNNDemo"
    private fun startWork1() = CoroutineScope(IO).launch {
        NativeLib.test(this@MainActivity)
    }

    private fun startWork2() = CoroutineScope(IO).launch {
        val modelDir = "data/local/tmp/MNNDemo"

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