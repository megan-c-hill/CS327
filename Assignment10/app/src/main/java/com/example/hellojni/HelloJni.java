package com.example.hellojni;

import android.graphics.Color;
import android.support.constraint.ConstraintLayout;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.widget.TextView;

public class HelloJni extends AppCompatActivity {
    public static final int SIZE = 55;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        setContentView(R.layout.activity_hello_jni);
        ConstraintLayout cv = (ConstraintLayout)findViewById(R.id.activity_hello_jni);
        TextView[][] textViews = new TextView[19][26];
        for(int i = 0; i < 19; i++) {
            for(int j = 0; j < 26; j++) {
                TextView initialTextView = new TextView(this);
                initialTextView.setX(SIZE * j);
                initialTextView.setWidth(SIZE);
                initialTextView.setY((SIZE + 20) * i);
                initialTextView.setHeight(SIZE + 20);
                initialTextView.setText(showString(i, j));
                initialTextView.setTextSize(20);
                initialTextView.setTextColor(Color.parseColor("#000000"));
                cv.addView(initialTextView);
                textViews[i][j] = initialTextView;
            }
        }
    }

    public native String showString(int y, int x);

    static {
        System.loadLibrary("hello-jni");
    }
}
