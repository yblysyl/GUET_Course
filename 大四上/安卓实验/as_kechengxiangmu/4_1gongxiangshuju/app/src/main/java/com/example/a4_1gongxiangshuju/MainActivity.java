package com.example.a4_1gongxiangshuju;

import androidx.annotation.RequiresApi;
import androidx.appcompat.app.AppCompatActivity;
import androidx.core.app.ActivityCompat;
import androidx.core.content.ContextCompat;

import android.Manifest;
import android.content.ContentResolver;
import android.content.pm.PackageManager;
import android.database.Cursor;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.os.Build;
import android.os.Bundle;
import android.provider.MediaStore;
import android.util.Log;
import android.widget.ListView;

public class MainActivity extends AppCompatActivity {
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
//手机app运行通过，单模拟器不行，怀疑为模拟器上传文件问题

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

        mContentResolver=getContentResolver();
        mPlaylist = findViewById(R.id.lv_playlist);
        mCursorAdapter=new MediaCursorAdapter(MainActivity.this);
        mPlaylist.setAdapter(mCursorAdapter);


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

}