package com.example.f_service;

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

import androidx.core.app.NotificationCompat;

public class MyService extends Service {
    int id = 1111;
    private static final String TAG="TAG";

    NotificationManager mNotificationManager;
    public MyService() {
    }
    @Override
    public void onCreate() {
      super.onCreate();
        Log.d(TAG, "onCreate()");
    }

    @Override
    public IBinder onBind(Intent intent) {
        // TODO: Return the communication channel to the service.
        throw new UnsupportedOperationException("Not yet implemented");
    }
    @Override
    public int onStartCommand(Intent intent,int flags,int startId) {
        if (Build.VERSION.SDK_INT >= 26) {
            Log.d("TAG", "1");
            String CHANNEL_ID = "my_channel_01";
            NotificationChannel channel = new NotificationChannel(CHANNEL_ID,
                    "Channel human readable title",
                    NotificationManager.IMPORTANCE_DEFAULT);
            Log.d("TAG", "2");
            mNotificationManager = (NotificationManager) getSystemService(Context.NOTIFICATION_SERVICE);

            mNotificationManager.createNotificationChannel(channel);

            Notification notification = new NotificationCompat.Builder(this, CHANNEL_ID)
                    .setContentTitle(intent.getStringExtra(MainActivity.TITLE).toString())
                    .setSmallIcon(R.mipmap.ic_launcher)
                    .setContentText(intent.getStringExtra(MainActivity.TEXT).toString()).build();
            Log.d("TAG", "3");
           // mNotificationManager.notify(id, notification);  //单普通通知

             startForeground(id, notification);

        }
        return super.onStartCommand(intent, flags, startId);
    }
}






