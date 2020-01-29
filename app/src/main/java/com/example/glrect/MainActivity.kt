package com.example.glrect

import android.content.Intent
import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.widget.Button
import android.widget.TextView
import android.widget.EditText
import android.widget.Toast
import kotlinx.android.synthetic.main.activity_main.*

class MainActivity : AppCompatActivity() {

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)
        val drawButton = findViewById(R.id.drawButton) as Button
        val textView = findViewById(R.id.textView) as TextView
        var editText = findViewById(R.id.editText) as EditText
        textView.setText("Write a corner points of polygon and click draw button. " +
                "Points must be between -1.0 and 1.0. Separate points by comma")


        drawButton.setOnClickListener{
            // Split string by comma and add each value to float array
            var str = editText.text.split(",").toTypedArray()
            var points = FloatArray(str.size)
            var error: Boolean = true
            try {
                for (i in 0..str.size-1) {
                    points[i] = str[i].toFloat()
                }
                error = false
            }catch (error : NumberFormatException){
                Toast.makeText(this, "String Error", Toast.LENGTH_LONG).show()
            }
            // If there is no error in given string, draw polygon
            if(!error){
                val intent = Intent(this, DrawingActivity::class.java)
                val bundle = Bundle()
                bundle.putFloatArray("points", points)
                intent.putExtras(bundle)
                startActivity(intent)
            }
        }


    }

    // Native functions
    //external fun findTriangles(): Float
    //external fun getPoints(arr:FloatArray): FloatArray
}
