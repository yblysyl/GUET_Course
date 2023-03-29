package com.example.a4_1gongxiangshuju;

import androidx.annotation.RequiresApi;
import androidx.appcompat.app.AppCompatActivity;
import androidx.core.app.ActivityCompat;
import androidx.core.app.NotificationCompat;
import androidx.core.content.ContextCompat;

import android.Manifest;
import android.app.Notification;
import android.app.NotificationChannel;
import android.app.NotificationManager;
import android.app.PendingIntent;
import android.content.BroadcastReceiver;
import android.content.ComponentName;
import android.content.ContentResolver;
import android.content.ContentUris;
import android.content.Context;
import android.content.Intent;
import android.content.IntentFilter;
import android.content.ServiceConnection;
import android.content.pm.PackageManager;
import android.database.Cursor;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.media.MediaPlayer;
import android.net.Uri;
import android.os.Build;
import android.os.Bundle;
import android.os.Handler;
import android.os.IBinder;
import android.os.Looper;
import android.os.Message;
import android.provider.MediaStore;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.widget.AdapterView;
import android.widget.ImageView;
import android.widget.ListView;
import android.widget.ProgressBar;
import android.widget.TextView;

import com.bumptech.glide.Glide;
import com.google.android.material.bottomnavigation.BottomNavigationItemView;
import com.google.android.material.bottomnavigation.BottomNavigationView;

import java.io.IOException;

public class MainActivity extends AppCompatActivity implements View.OnClickListener{
    private final int REQUEST_EXTERNAL_STORAGE = 1;
    private static String[] PERMISSIONS_STORAGE = {
            Manifest.permission.READ_EXTERNAL_STORAGE,
            Manifest.permission.WRITE_EXTERNAL_STORAGE
    };
    private Cursor mCursor;
    private ContentResolver  mContentResolver;
    private ListView mPlaylist;
    private MediaCursorAdapter mCursorAdapter;
    private final String SELECTION=
            MediaStore.Audio.Media.IS_MUSIC + " = ? " + " AND " +
                    MediaStore.Audio.Media.MIME_TYPE + " LIKE ? ";
    private final String[]  SELECTION_ARGS ={
            Integer.toString(1),
            "audio/mpeg"
    };
//    总体思路  在项目十的基础上  1新增BottomNavigationView 控件 //详见 MainActivity_main.xml 中  2在bottom xml中实际实现BottomNavigationView
    //调用setOnItemClickListener函数，绑定每一项 点击细项监听事件
    //实现音乐播放主要依靠 MediaPlayer类
    //本次项目主要熟悉以上两个类  已经 mediaplayer周期流程

    //music3总结
    // 先创建 频道  在建立intener  最后startForeground实现 发送
    //将近三个小时浪费在找错误上   总结 以后先看日志通过日志结果找解决方法  注意赋予权限的问题。无权限易崩溃。

//以下三组仅为键值对，贡其他类调用。intent指示数据键值对中的key
    //music3 定义参数
    public static  final String DATA_URI=
            "com.glriverside.xgqin.ggmusic.DATA_URI";

    //music3_2定义参数
    public static  final String TITLE=
            " com.glriverside.xgqin.ggmusic.TITLE";
    public static final String ARTIST =
             "com.glriverside.xgqin.ggmusic.ARTIST";

    //music2 添加部分
    private BottomNavigationView navigation;
    private TextView tvBottomTitle;
    private TextView tvBottomArtist;
    private ImageView ivAlbumThumbnail;
    private ImageView ivPaly;
    private MediaPlayer mMediaPlayer = null;

    //music4参数
    //第六章实验总结--绑定服务与自定义广播--6-1
    /*
    本实验主要是 绑定服务与广播的应用
    绑定服务提供 回调binder对象   在onbinder里定义返回内部类MusicServiceBinder
    再通过MusicServiceBinder getService将MusicService本身传递过来 然后再MusicService写公开函数来访问内部数据
    绑定服务 用bindService(intent,mConn,Context.BIND_AUTO_CREATE); inten和普通服务相同
    mConn回调接口 接口实现两个方法 一个和服务建立有关onServiceConnected，一个和注销有关onServiceDisconnected
    onServiceConnected的第二个参数为服务类里的onbind返回的内部类MusicServiceBinder

    实现绑定服务之后 用线程MusicProgressRunnable 来控制进度条
    线程继承Runnable类 在线程中利用Handler message来传递信息
    以此来实现线程获取数据然后再主线程中更新控件
    在主类中定义Handler内部类 实现接口方法handleMessage 来更新控件数据

    为了保证计数线程在服务线程之后启动， 将线程的启动放在广播中。 广播监听服务线程发出的信号来唤醒计时线程
    public class MusicReceiver extends BroadcastReceiver（）；实现 onReceive方法来操作线程
    注册广播如
        musicReceiver=new MusicReceiver();
        IntentFilter intentFilter=new IntentFilter();
        intentFilter.addAction(ACTION_MUSIC_START);  添加广播响应的参数
        registerReceiver(musicReceiver,intentFilter);
        发送广播代码如下
        Intent musicStartIntent=new Intent(MainActivity.ACTION_MUSIC_START);
                sendBroadcast(musicStartIntent);

         最后小点 ProgressBar控件 有两个参数 一个最大值一个当前值来实现进度显示 详见 广播类和Handler类的调用过程
    * */
    private MusicService mService;
    private MusicReceiver musicReceiver;
    private boolean mBound=false;
    private Boolean mPlayststus=true;
    private static final int UPDATE_PROGRESS=1;
    private ProgressBar pbprogess;

    public static final String ACTION_MUSIC_STOP="com.glriverside.xgqin.ggmusic.ACTION_MUSIC_STOP";
    public static final String ACTION_MUSIC_START="com.glriverside.xgqin.ggmusic.ACTION_MUSIC_START";
    private Handler mHandler=new Handler(Looper.getMainLooper()){
        public void handleMessage(Message msg){
            Log.d("6211","进入数据设置");
            switch (msg.what){
                case UPDATE_PROGRESS:
                    int position=msg.arg1;
                    pbprogess.setProgress(position);
                    Log.d("6211","数据设置成功"+position);

                    break;
                default:
                    break;
            }
        }
    };
    private ServiceConnection mConn=new ServiceConnection() {
        @Override
        public void onServiceConnected(ComponentName name, IBinder service) {
            MusicService.MusicServiceBinder binder=(MusicService.MusicServiceBinder) service;
            mService=binder.getService();
            mBound=true;
        }

        @Override
        public void onServiceDisconnected(ComponentName name) {
            mService=null;
            mBound=false;
        }
    };


    @Override
    protected void onStart() {
        Log.d("61jiance","活动打开");
        super.onStart();
        Intent intent=new Intent(MainActivity.this,MusicService.class);
        bindService(intent,mConn,Context.BIND_AUTO_CREATE);
    }
    @Override
    protected void onStop() {
        unbindService(mConn);
        mBound=false;
        super.onStop();
    }
    @Override
    protected void onDestroy() {
        unregisterReceiver(musicReceiver);
        super.onDestroy();
    }

   // @Override
    public void onRequestPermissionsResult(int requestCode,String[] permissions,int[]grantResults){
        switch (requestCode){
            case REQUEST_EXTERNAL_STORAGE:
                if(grantResults.length>0 && grantResults[0]==PackageManager.PERMISSION_GRANTED){
                    initplaylist();
                    Log.d("TESTMAIN","onrp");

            }
                break;
            default:
                break;
        }
    }

    @RequiresApi(api = Build.VERSION_CODES.M)
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        Log.d("51jiance","active调用");

        yingshenavigation();
        Log.d("51jiance","navigation实例化完成调用");


        mContentResolver=getContentResolver();
        mPlaylist = findViewById(R.id.lv_playlist);
        mCursorAdapter=new MediaCursorAdapter(MainActivity.this);
        mPlaylist.setAdapter(mCursorAdapter);

        mPlaylist.setOnItemClickListener(itemClickListener);
        //注册广播
        musicReceiver=new MusicReceiver();
        IntentFilter intentFilter=new IntentFilter();
        intentFilter.addAction(ACTION_MUSIC_START);
        intentFilter.addAction(ACTION_MUSIC_STOP);
        registerReceiver(musicReceiver,intentFilter);

        Log.d("61","广播注册完毕");



        //ContextCompat类的checkSelfPermission方法用于检测用户是否授权了某个权限
        //checkSelfPermission()方法需要传递两个参数，第一个参数需要传入Context,第二个参数需要传入需要检测的权限，
        // 方法返回值为-1（PackageManager.PERMISSION_DENIED）或者0（PackageManager.PERMISSION_GRANTED）。
        // 若返回值为GRANTED则为已授权，否则就需要进行申请授权了。
        if(ContextCompat.checkSelfPermission(this,
                Manifest.permission.READ_EXTERNAL_STORAGE)!= PackageManager.PERMISSION_GRANTED){
            Log.d("TESTMAIN","权限未获取1");
            //shouldShowRequestPermissionRationale()
            //1. 第一次请求权限时，用户拒绝了，下一次：shouldShowRequestPermissionRationale() 返回 true，应该显示一些为什么需要这个权限的说明
            //2.第二次请求权限时，用户拒绝了，并选择了“不在提醒”的选项时：shouldShowRequestPermissionRationale() 返回 false
            //3. 设备的策略禁止当前应用获取这个权限的授权：shouldShowRequestPermissionRationale() 返回 false
            if(ActivityCompat.shouldShowRequestPermissionRationale(
                    MainActivity.this,
                    Manifest.permission.READ_EXTERNAL_STORAGE)){
            }else {
                //requestPermissions，该⽅法是 Activity 类的⽅法，⽤于动态申请权限
                requestPermissions(PERMISSIONS_STORAGE,REQUEST_EXTERNAL_STORAGE);
            }
        }else{
            initplaylist();//获取数据 放入Cursor类中  Cursor见3——2详解

        }


    }
    //绑定navigation对应布局
    private void yingshenavigation(){
        Log.d("51jiance","navigation开始");
        Log.d("51jiance",findViewById(R.id.navigation).toString());
        navigation=findViewById(R.id.navigation);
        LayoutInflater.from(MainActivity.this).inflate(R.layout.bottom_media_toolbar,
                navigation,
                true);
        ivPaly =navigation.findViewById(R.id.iv_play);
        tvBottomArtist=navigation.findViewById(R.id.tv_bottom_artist);
        tvBottomTitle=navigation.findViewById(R.id.tv_bottom_title);
        ivAlbumThumbnail=navigation.findViewById(R.id.iv_thumbnail);
        pbprogess=navigation.findViewById(R.id.progress);
        if(ivPaly!=null){
            ivPaly.setOnClickListener(MainActivity.this);
            Log.d("51jiance","navi_ivplay no null");
        }
        navigation.setVisibility(View.GONE);
        Log.d("51jiance","navigation4");

    }

//music3重写music2中的方法
    private ListView.OnItemClickListener itemClickListener
            = new ListView.OnItemClickListener(){
        @RequiresApi(api = Build.VERSION_CODES.O)
        @Override
        public void onItemClick(AdapterView<?> adapterView, View view, int i, long id) {
            Log.d("51jiance","itemclick是否运行到");
            Cursor cursor=mCursorAdapter.getCursor();
            if(cursor!=null&&cursor.moveToPosition(i)){
                int titleIndex=cursor.getColumnIndex(MediaStore.Audio.Media.TITLE);
                int artistIndex=cursor.getColumnIndex(MediaStore.Audio.Media.ARTIST);
                int albmIdIndex=cursor.getColumnIndex(MediaStore.Audio.Media.ALBUM_ID);
                int dataIndex=cursor.getColumnIndex(MediaStore.Audio.Media.DATA);
                String title=cursor.getString(titleIndex);
                String artist=cursor.getString(artistIndex);
                Long albumId=cursor.getLong(albmIdIndex);
                String data=cursor.getString(dataIndex);

                Uri dataUri=Uri.parse(data);
                /*
                //music3_service变动部分
                Intent serviceIntent =new Intent(MainActivity.this,
                        MusicService.class);
                serviceIntent.putExtra(MainActivity.DATA_URI,data);
                startService(serviceIntent);*/


                //music3_2部分
                Intent serviceIntent =new Intent(MainActivity.this,
                        MusicService.class);
                serviceIntent.putExtra(MainActivity.DATA_URI,data);
                serviceIntent.putExtra(MainActivity.TITLE,title);
                serviceIntent.putExtra(MainActivity.ARTIST,artist);
                //startService(serviceIntent);

                startForegroundService(serviceIntent);

                //startService(serviceIntent);
                Log.d("51jiance","服务调用完成"+title);
                //tongzhiceshi();

                //music3取消

               /* if(mMediaPlayer!=null){
                    try{
                        mMediaPlayer.reset();
                        mMediaPlayer.setDataSource(MainActivity.this,dataUri);
                        mMediaPlayer.prepare();
                        mMediaPlayer.start();
                        mPlayststus=true;
                    } catch (IOException e) {
                        e.printStackTrace();
                    }
                }*/
                navigation.setVisibility(View.VISIBLE);
                Log.d("51jiance","服务调用2");
                if(tvBottomTitle!=null){
                    tvBottomTitle.setText(title);
                }
                if(tvBottomArtist!=null){
                    tvBottomArtist.setText(artist);
                }
                Uri albumUri= ContentUris.withAppendedId(MediaStore.Audio.Albums.EXTERNAL_CONTENT_URI,albumId);
                Cursor albumCursor=mContentResolver.query(
                        albumUri,
                        null,
                        null,
                        null,
                        null
                );
                Log.d("51jiance","服务调用3");
                if(albumCursor!=null&&albumCursor.getCount()>0){
                    albumCursor.moveToFirst();
                    int albumArtIndex=albumCursor.getColumnIndex(
                            MediaStore.Audio.Albums.ALBUM_ART
                    );
                    String albumArt=albumCursor.getString(albumArtIndex);
                    Glide.with(MainActivity.this)
                            .load(albumArt)
                            .into(ivAlbumThumbnail);
                    albumCursor.close();
                }
                Log.d("51jiance","点击事件结束");

            }
        }
    };

    private void initplaylist(){
        //ContentResolver 的 query 方法的查询条件
        //MediaStore.Audio.Media.IS_MUSIC，表⽰⾳频⽂件是否属于⾳乐类型的元数据字段；
        //MediaStore.Audio.Media.MIME_TYPE，表⽰⾳频⽂件的 MIME 类型， MP3⽂件对应的 MIME类型为 “audio/mpeg”。

        mCursor=mContentResolver.query(
                MediaStore.Audio.Media.EXTERNAL_CONTENT_URI,
                null,
                SELECTION,
                SELECTION_ARGS,
                MediaStore.Audio.Media.DEFAULT_SORT_ORDER
        );
        //参数问题详见query用法



        mCursorAdapter.swapCursor(mCursor);
        mCursorAdapter.notifyDataSetChanged();
    }

    @Override
    public void onClick(View v) {
        switch (v.getId()){
            case R.id.iv_play:
                mPlayststus=!mPlayststus;
                if(mPlayststus){
                   mService.play();
                }else{
                    mService.pause();

                }
                break;
        }
    }
    //线程接口，用以获取音乐播放的时间线
    private class MusicProgressRunnable implements Runnable{

        @Override
        public void run() {
            boolean mThreadWorking=true;
            while(mThreadWorking){
                try{
                    if(mService!=null){
                        int position=mService.getCurrentPosition();
                        Log.d("6211","播放进度  "+position);
                        Message message=new Message();
                        message.what=UPDATE_PROGRESS;
                        message.arg1=position;
                        mHandler.sendMessage(message);
                    }
                    mThreadWorking=mService.isPlaying();
                    Thread.sleep(100);
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }
            }
        }
    }
    public class MusicReceiver extends BroadcastReceiver{

        @Override
        public void onReceive(Context context, Intent intent) {
            if(mService!=null){
                Log.d("61","进入广播");

                pbprogess.setMax(mService.getDuration());
                Log.d("61","设置MAX完毕");
                new Thread(new MusicProgressRunnable()).start();
            }
        }
    }


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
        return;

    }
}