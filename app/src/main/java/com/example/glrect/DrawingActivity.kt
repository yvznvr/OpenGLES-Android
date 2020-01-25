package com.example.glrect

import android.opengl.GLSurfaceView
import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.widget.Toast
import com.example.glrect.R


class DrawingActivity : AppCompatActivity() {

    private lateinit var glSurfaceView : GLSurfaceView
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_drawing)
        glSurfaceView = findViewById<GLSurfaceView>(R.id.glSurfaceView)
        glSurfaceView.setEGLContextClientVersion(2)
        var renderer = MyRenderer()
        renderer.updatePoints(intent.getFloatArrayExtra("points"))
        glSurfaceView.setRenderer(renderer)
    }


    override fun onPause() {
        super.onPause()
        glSurfaceView.onPause()
    }

    override fun onResume() {
        super.onResume()
        glSurfaceView.onResume()
    }
}
