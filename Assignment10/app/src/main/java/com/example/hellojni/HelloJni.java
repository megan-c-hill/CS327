package com.example.hellojni;

import android.graphics.Color;
import android.graphics.Typeface;
import android.support.constraint.ConstraintLayout;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.KeyEvent;
import android.widget.TextView;

public class HelloJni extends AppCompatActivity {
	public static final int SIZE = 55;
	TextView[][] textViews = new TextView[17][26];

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);

		setContentView(R.layout.activity_hello_jni);
		ConstraintLayout cv = (ConstraintLayout) findViewById(R.id.activity_hello_jni);
		for (int i = 0; i < textViews.length; i++) {
			for (int j = 0; j < textViews[0].length; j++) {
				TextView initialTextView = new TextView(this);
				initialTextView.setX(SIZE * j);
				initialTextView.setWidth(SIZE);
				initialTextView.setY((SIZE + 30) * i);
				initialTextView.setTypeface(Typeface.MONOSPACE);
				initialTextView.setHeight(SIZE + 30);
				initialTextView.setText(" ");
				initialTextView.setTextSize(20);
				initialTextView.setTextColor(Color.parseColor("#000000"));
				cv.addView(initialTextView);
				textViews[i][j] = initialTextView;
			}
		}
	}

	@Override
	public boolean dispatchKeyEvent(KeyEvent KEvent) {
		if (KEvent.getAction()== KeyEvent.ACTION_UP) {
			char character = (char) KEvent.getUnicodeChar(KEvent.getMetaState());

			if (((Character) character).equals('s')) {
				startGame();
			}
		}

		return super.dispatchKeyEvent(KEvent);
	}

	private void startGame() {
		Thread gameThread = new Thread(new Runnable() {
			@Override
			public void run() {
				setup();
				while (isOver() == 1) {
					playGame();
				}
				cleanup();
			}
		});
		gameThread.start();
	}

	public void displayChar(int y, int x, String c) {
		textViews[y][x].setText(c);
	}

	public native void setup();

	public native int isOver();

	public native void playGame();

	public native void cleanup();

	static {
		System.loadLibrary("hello-jni");
	}
}
