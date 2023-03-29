package com.example.foregroundservice;

import android.app.Notification;
import android.app.NotificationChannel;
import android.app.NotificationManager;
import android.app.PendingIntent;
import android.app.Service;
import android.content.Context;
import android.content.Intent;
import android.os.Build;
import android.os.IBinder;
import android.util.Log;

import androidx.annotation.RequiresApi;

public class MyService extends Service {
    public MyService() {
    }

    @Override
    public IBinder onBind(Intent intent) {
        // TODO: Return the communication channel to the service.
        throw new UnsupportedOperationException("Not yet implemented");
    }
    @RequiresApi(api = Build.VERSION_CODES.O)
    @Override
    public int onStartCommand(Intent intent, int flags, int startId) {
        Log.d("TAG","进入服务");
        // TODO Auto-generated method stub
        NotificationManager mNotificationManager;
        mNotificationManager=(NotificationManager) getSystemService(Context.NOTIFICATION_SERVICE);
        String CHANNEL_ID = "my_channel_01";
        NotificationChannel channel = new NotificationChannel(CHANNEL_ID,
                "Channel human readable title",
                NotificationManager.IMPORTANCE_DEFAULT);
        mNotificationManager.createNotificationChannel(channel);


        Notification notification = new Notification.Builder(this,CHANNEL_ID)
                .setAutoCancel(true).
                setSmallIcon(R.mipmap.ic_launcher)
                .setTicker("前台Service启动").setContentTitle("前台Service运行中").
                setContentText("这是一个正在运行的前台Service")
                .build();
        //mNotificationManager.notify(222, notification);
        startForeground(111, notification);
        return START_STICKY;
    }
}