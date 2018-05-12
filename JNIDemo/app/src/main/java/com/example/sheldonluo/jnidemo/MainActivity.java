package com.example.sheldonluo.jnidemo;

import android.app.Activity;
import android.content.pm.PackageManager;
import android.graphics.Bitmap;
import android.graphics.Canvas;
import android.graphics.Color;
import android.graphics.Paint;
import android.graphics.drawable.BitmapDrawable;
import android.graphics.drawable.Drawable;
import android.net.Uri;
import android.os.Environment;
import android.os.Handler;
import android.os.Message;
import android.support.v4.app.ActivityCompat;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.ImageView;

import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.OutputStream;
import java.util.Timer;
import java.util.TimerTask;

public class MainActivity extends AppCompatActivity {

    private String gifPath;
    private ImageView iv;
    private Bitmap bmp;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        verifyStoragePermissions(this);

        Log.i("test JNI", NativeMethod.print("Hello World."));

        iv = findViewById(R.id.imgView);
        Button btn = findViewById(R.id.btn);
        btn.setText("点击");

        String path = Environment.getExternalStorageDirectory().toString();
//        本地GIF图片
        gifPath = path + "/Download/giphy9.gif";

        // for test
        onClick(iv);
    }

    public void onClick(View v) {
        NativeMethod.loadGif(gifPath);
        Bitmap.Config conf = Bitmap.Config.ARGB_8888;
//        TODO：宽高应该从native中获取
        bmp = Bitmap.createBitmap(748, 561, conf);

//        Canvas canvas = new Canvas(bmp);
//        Paint paint = new Paint();
//        paint.setColor(getResources().getColor(R.color.colorPrimaryDark));
//        canvas.drawRect(0F, 0F, (float) 748, (float) 561, paint);
        iv.setImageBitmap(bmp);

        updateImageView();

        // start timer
        Timer timer = new Timer();
        timer.scheduleAtFixedRate(new UITask(), 0, 50 );
    }

    public void updateImageView() {
        NativeMethod.getNextFrame(bmp);
        iv.setImageBitmap(bmp);
    }


    // timer
    private Handler updateUI = new Handler() {
        @Override
        public void handleMessage(Message msg) {
            switch (msg.what) {
                case 1:
                    updateImageView();
                    break;
            }
        }
    };

    private class UITask extends TimerTask {// public abstract class TimerTask implements Runnable{}
        @Override
        public void run() {
            Message msg = new Message();
            msg.what = 1;
            updateUI.sendMessage(msg);
        }
    }

    // permission handle
    private static final int REQUEST_EXTERNAL_STORAGE = 1;
    private static String[] PERMISSIONS_STORAGE = {
            "android.permission.READ_EXTERNAL_STORAGE",
            "android.permission.WRITE_EXTERNAL_STORAGE" };


    public static void verifyStoragePermissions(Activity activity) {

        try {
            //检测是否有写的权限
            int permission = ActivityCompat.checkSelfPermission(activity,
                    "android.permission.WRITE_EXTERNAL_STORAGE");
            if (permission != PackageManager.PERMISSION_GRANTED) {
                // 没有写的权限，去申请写的权限，会弹出对话框
                ActivityCompat.requestPermissions(activity, PERMISSIONS_STORAGE,REQUEST_EXTERNAL_STORAGE);
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}
