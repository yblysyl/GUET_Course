package com.example.tongzhilx;

import androidx.annotation.RequiresApi;
import androidx.appcompat.app.AppCompatActivity;
import androidx.core.app.NotificationCompat;

import android.app.NotificationChannel;
import android.app.NotificationManager;
import android.content.Context;
import android.content.Intent;
import android.content.IntentFilter;
import android.os.Build;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;

public class MainActivity extends AppCompatActivity implements View.OnClickListener{
    Button b1;
    EditText t1;
    String s;
    static final  String TEXT="text";
    static final String TITLE="title";

   // 通知相关
    private int id = 1111;
    private String channelId = "channelId1";//渠道id
    private NotificationManager mNotificationManager;
    private String BROADCAST_ACTION="android.intent.action.BROADCAST_ACTION";

    public MainActivity() {
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        b1=findViewById(R.id.button);
        t1=findViewById(R.id.txtview);
        s=t1.getText().toString();


       b1.setOnClickListener(this);


        mNotificationManager = (NotificationManager) getSystemService(Context.NOTIFICATION_SERVICE);
        addNotificationChannel();


       /* //动态注册广播
        dynamicBroadcast=new DynamicBroadcast();
        IntentFilter intentFilter=new IntentFilter(BROADCAST_ACTION);
        registerReceiver(dynamicBroadcast,intentFilter);*/


    }


    public void addNotificationChannel() {
        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.O) {
            //创建通知渠道
            CharSequence name = "渠道名称1";
            int importance = NotificationManager.IMPORTANCE_DEFAULT;//重要性级别 这里用默认的
            NotificationChannel mChannel = new NotificationChannel(channelId, name, importance);
            mNotificationManager.createNotificationChannel(mChannel);//创建通知渠道
        }
    }
    @RequiresApi(api = Build.VERSION_CODES.O)
    @Override
    public void onClick(View v) {
        Log.d("TAG","jinruclick");
       switch (v.getId()) {
            case R.id.button:
                NotificationCompat.Builder mBuilder1 = new NotificationCompat.Builder(this, channelId)
                        .setSmallIcon(R.mipmap.ic_launcher)//小图标
                        .setContentTitle("我是标题")
                        .setContentText("我是内容内容");
                Log.d("TAG","我被点击");

                mNotificationManager.notify(id, mBuilder1.build());


                Intent serviceIntent =new Intent(MainActivity.this,
                        MyService.class);
                serviceIntent.putExtra(MainActivity.TEXT,s+s);
                serviceIntent.putExtra(MainActivity.TITLE,s);
                startService(serviceIntent);
                //startForegroundService(serviceIntent);
                break;
        }
    }


}