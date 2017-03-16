package me.sheldon.gesture;

import android.os.Bundle;
import android.support.v4.view.GestureDetectorCompat;
import android.support.v7.app.AppCompatActivity;
import android.util.Log;
import android.view.GestureDetector;
import android.view.MotionEvent;
import android.widget.Toast;

/**
 * Sheldon Law on 2017-03-16
 *
 * reference:
 * https://developer.android.com/training/gestures/detector.html
 */

public class MainActivity extends AppCompatActivity {

    private GestureDetectorCompat mDetector;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        mDetector = new GestureDetectorCompat(this, new MyGestureListener());
    }

    @Override
    public boolean onTouchEvent(MotionEvent event){
        this.mDetector.onTouchEvent(event);
        return super.onTouchEvent(event);
    }

    class MyGestureListener extends GestureDetector.SimpleOnGestureListener {
        private static final String DEBUG_TAG = "Gestures";

        @Override
        public boolean onFling(MotionEvent event1, MotionEvent event2,
                               float velocityX, float velocityY) {
            String toastText = "Fling: ";
            if (Math.abs(velocityX) < Math.abs(velocityY)) return false;
            if (velocityX > 0) {
                toastText += "right";
            } else {
                toastText += "left";
            }
            Toast.makeText(MainActivity.this, toastText, Toast.LENGTH_SHORT).show();
            Log.d(DEBUG_TAG, "onFling: " + event1.toString()+event2.toString());
            return true;
        }
    }

}
