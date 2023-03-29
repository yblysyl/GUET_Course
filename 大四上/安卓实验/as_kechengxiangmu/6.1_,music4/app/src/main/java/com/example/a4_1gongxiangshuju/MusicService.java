package com.example.a4_1gongxiangshuju;

import android.app.Notification;
import android.app.NotificationChannel;
import android.app.NotificationManager;
import android.app.PendingIntent;
import android.app.Service;
import android.content.Context;
import android.content.Intent;
import android.media.MediaPlayer;
import android.net.Uri;
import android.os.Binder;
import android.os.Build;
import android.os.IBinder;
import android.util.Log;

import androidx.core.app.NotificationCompat;

import java.io.IOException;

//重载 onCreate onDestroy onBind
public class MusicService extends Service {
    MediaPlayer mMediaPlayer;

    //通知测试
    int id = 1111;
    String channelId = "channelId1";//渠道id
    NotificationManager mNotificationManager;
    String BROADCAST_ACTION="android.intent.action.BROADCAST_ACTION";

    //music3_2参数
    private static final int ONGOING_NOTIFICATION_ID = 1001;
    private static final String CHANNEL_ID = "Music channel";
   // NotificationManager mNotificationManager;

    //music 4参数
    private final IBinder mbinder=new MusicServiceBinder();

    public MusicService() {
    }

    @Override
    public void onDestroy() {
        mMediaPlayer.stop();
        mMediaPlayer.release();
        mMediaPlayer=null;
        super.onDestroy();
    }
    @Override
    public void onCreate(){
        super.onCreate();
        mMediaPlayer=new MediaPlayer();
    }

    @Override
    public IBinder onBind(Intent intent) {
        // TODO: Return the communication channel to the service.
        return mbinder;
    }

    @Override
    public int onStartCommand(Intent intent,int flags,int startId){
        String data=intent.getStringExtra(MainActivity.DATA_URI);
        String title=intent.getStringExtra(MainActivity.TITLE);
        String artist=intent.getStringExtra(MainActivity.ARTIST);
        Uri dataUri=Uri.parse(data);
        if(mMediaPlayer!=null){
            try{
                if(mMediaPlayer.isPlaying()){
                    mMediaPlayer.stop();
                }
                mMediaPlayer.reset();
                mMediaPlayer.setDataSource(getApplicationContext(),dataUri);
                mMediaPlayer.prepare();
                mMediaPlayer.start();
                Intent musicStartIntent=new Intent(MainActivity.ACTION_MUSIC_START);
                sendBroadcast(musicStartIntent);
            } catch (IOException e) {
                e.printStackTrace();
            }
        }
        //music3改动
        if(Build.VERSION.SDK_INT >= Build.VERSION_CODES.O){
            mNotificationManager=(NotificationManager) getSystemService(NOTIFICATION_SERVICE);
            NotificationChannel channel=new NotificationChannel(CHANNEL_ID,
                    "misic channel",NotificationManager.IMPORTANCE_HIGH);
            if(mNotificationManager!=null){
                mNotificationManager.createNotificationChannel(channel);
            }
        }
        //其中 setContentIntent() 为通知设置延迟意图，当⽤户点击该通知时，通常希望能查看通知详情。
        // 在本项⽬中由于只有⼀个 Activity，因此我们将该延迟意图设为打开 MainActivity 活动即可。
        // 延迟意图在 Intent 的基础上进⾏了封装
        // 通过 PendingIntent.geActivity() ⽅法构造⼀个启动活动的延迟意图，
        Intent notificationIntent=new Intent(getApplicationContext(),MainActivity.class);
        PendingIntent pendingIntent=PendingIntent.getActivity(
                getApplicationContext(),
                0,notificationIntent,0);
        NotificationCompat.Builder builder;
        if(Build.VERSION.SDK_INT>=Build.VERSION_CODES.O){
            builder=new NotificationCompat.Builder(getApplicationContext(),CHANNEL_ID);
        }else{
             builder=new NotificationCompat.Builder(getApplicationContext());
        }

        Notification notification=builder
                .setContentTitle(title)
                .setContentText(artist)
                .setSmallIcon(R.drawable.ic_tongzhi)
                .setContentIntent(pendingIntent).build();
        startForeground(ONGOING_NOTIFICATION_ID,notification);//*/
        return super.onStartCommand(intent,flags,startId);
    }

    //music3的通知测试
    public void tongzhiceshi(){
        int id = 1111;
        String channelId = "channelId1";//渠道id
        NotificationManager mNotificationManager;
        String BROADCAST_ACTION="android.intent.action.BROADCAST_ACTION";

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
                .setContentTitle("我是标题")
                .setContentText("我是内容内容");
        Log.d("TAG","我被点击");

        mNotificationManager.notify(id, mBuilder1.build());
        return;}

        //music4
      public  class MusicServiceBinder extends Binder {

        MusicService getService(){
            return MusicService.this;
        }
    }
    //给其他组件的接口方法
    public void pause(){
        if(mMediaPlayer!=null&&mMediaPlayer.isPlaying()){
            mMediaPlayer.pause();
        }
    }
    public void play(){
        if(mMediaPlayer!=null){
            mMediaPlayer.start();
        }
    }
    public int getDuration(){
        int duration=0;
        if(mMediaPlayer!=null){
            duration=mMediaPlayer.getDuration();
            Log.d("61",duration+"");
        }
        return duration;
    }
    public int getCurrentPosition(){
        int position=0;
        if(mMediaPlayer!=null){
            position=mMediaPlayer.getCurrentPosition();
        }
        return position;
    }
    public boolean isPlaying(){
        if(mMediaPlayer!=null){
            return mMediaPlayer.isPlaying();
        }
        return false;
    }


}


