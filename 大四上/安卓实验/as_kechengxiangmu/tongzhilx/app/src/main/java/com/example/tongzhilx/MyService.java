package com.example.tongzhilx;

import android.app.NotificationChannel;
import android.app.NotificationManager;
import android.app.Service;
import android.content.Context;
import android.content.Intent;
import android.net.Uri;
import android.os.Build;
import android.os.IBinder;
import android.util.Log;

import androidx.core.app.NotificationCompat;

import java.io.IOException;

public class MyService extends Service {
    int id = 1111;
    String channelId = "channelId1";//渠道id
    NotificationManager mNotificationManager;
    String BROADCAST_ACTION="android.intent.action.BROADCAST_ACTION";
    public MyService() {
    }

    @Override
    public IBinder onBind(Intent intent) {
        // TODO: Return the communication channel to the service.
        throw new UnsupportedOperationException("Not yet implemented");
    }


    public int onStartCommand(Intent intent,int flags,int startId){
        String title=intent.getStringExtra(MainActivity.TITLE);
        String text=intent.getStringExtra(MainActivity.TEXT);
        mNotificationManager = (NotificationManager) getSystemService(Context.NOTIFICATION_SERVICE);
        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.O) {
            //创建通知渠道
            CharSequence name = "渠道名称1";
            int importance = NotificationManager.IMPORTANCE_DEFAULT;//重要性级别 这里用默认的
            NotificationChannel mChannel = new NotificationChannel(channelId, name, importance);
            mNotificationManager.createNotificationChannel(mChannel);//创建通知渠道
        }

        NotificationCompat.Builder mBuilder1 = new NotificationCompat.Builder(this, channelId)
                .setSmallIcon(R.mipmap.ic_launcher)//小图标
                .setContentTitle(title)
                .setContentText(text);
        Log.d("TAG","我被点击");
        mNotificationManager.notify(id, mBuilder1.build());
        //startForeground(id,mBuilder1.build());

        return super.onStartCommand(intent,flags,startId);
    }


}