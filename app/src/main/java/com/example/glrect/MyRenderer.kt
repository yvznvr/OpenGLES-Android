package com.example.glrect

import android.opengl.GLSurfaceView
import javax.microedition.khronos.egl.EGLConfig
import javax.microedition.khronos.opengles.GL10
import kotlinx.android.synthetic.main.activity_main.*

class MyRenderer : GLSurfaceView.Renderer {
    // Native functions
    external fun drawFrame()
    external fun surfaceCreated()
    external fun setPoints(arr:FloatArray)

    fun updatePoints(points:FloatArray){
        setPoints(points)
    }

    override fun onDrawFrame(gl: GL10?) {
        drawFrame()
    }

    override fun onSurfaceChanged(gl: GL10?, width: Int, height: Int) {
        gl?.glViewport(0, 0, width, height);
    }

    override fun onSurfaceCreated(gl: GL10?, config: EGLConfig?) {
        surfaceCreated()
    }

    companion object {

        // Used to load the 'native-lib' library on application startup.
        init {
            System.loadLibrary("native-lib")
        }
    }
}
