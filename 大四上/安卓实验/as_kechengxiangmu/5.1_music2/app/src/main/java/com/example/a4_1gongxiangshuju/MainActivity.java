package com.example.a4_1gongxiangshuju;

import androidx.annotation.RequiresApi;
import androidx.appcompat.app.AppCompatActivity;
import androidx.core.app.ActivityCompat;
import androidx.core.content.ContextCompat;

import android.Manifest;
import android.content.ContentResolver;
import android.content.ContentUris;
import android.content.pm.PackageManager;
import android.database.Cursor;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.media.MediaPlayer;
import android.net.Uri;
import android.os.Build;
import android.os.Bundle;
import android.provider.MediaStore;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.widget.AdapterView;
import android.widget.ImageView;
import android.widget.ListView;
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



    //music2 添加部分
    private BottomNavigationView navigation;
    private TextView tvBottomTitle;
    private TextView tvBottomArtist;
    private ImageView ivAlbumThumbnail;
    private ImageView ivPaly;
    private MediaPlayer mMediaPlayer = null;

    @Override
    protected void onStart() {
        Log.d("51jiance","活动打开");
        super.onStart();
        if(mMediaPlayer==null){
            mMediaPlayer=new MediaPlayer();
        }
    }
    @Override
    protected void onStop() {
        if(mMediaPlayer!=null){
            mMediaPlayer.stop();
            mMediaPlayer.release();
            mMediaPlayer=null;
            Log.d("TAG","onStop invoked");
        }
        super.onStop();
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
        if(ivPaly!=null){
            ivPaly.setOnClickListener(MainActivity.this);
            Log.d("51jiance","navi_ivplay no null");
        }
        navigation.setVisibility(View.GONE);
        Log.d("51jiance","navigation4");

    }


    private ListView.OnItemClickListener itemClickListener
            = new ListView.OnItemClickListener(){
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
                if(mMediaPlayer!=null){
                    try{
                        mMediaPlayer.reset();
                        mMediaPlayer.setDataSource(MainActivity.this,dataUri);
                        mMediaPlayer.prepare();
                        mMediaPlayer.start();
                        mPlayststus=true;
                    } catch (IOException e) {
                        e.printStackTrace();
                    }
                }
                navigation.setVisibility(View.VISIBLE);
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

    private Boolean mPlayststus=false;
    @Override
    public void onClick(View v) {
        switch (v.getId()){
            case R.id.iv_play:
                mPlayststus=!mPlayststus;
                if(mPlayststus){
                    if(mMediaPlayer!=null){
                        mMediaPlayer.start();
                    }
                }else{
                    if(mMediaPlayer!=null){
                        mMediaPlayer.pause();
                    }

                }
                break;
        }

    }
}