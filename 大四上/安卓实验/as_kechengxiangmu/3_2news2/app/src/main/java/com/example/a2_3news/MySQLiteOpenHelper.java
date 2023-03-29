package com.example.a2_3news;

import android.content.ContentValues;
import android.content.Context;
import android.content.res.Resources;
import android.content.res.TypedArray;
import android.database.sqlite.SQLiteDatabase;
import android.database.sqlite.SQLiteOpenHelper;

//SQLiteOpenHelper类介绍
//定义：SQLiteOpenHelper是一个辅助类
//作用：管理数据库（创建、增、修、删） & 版本的控制。
//使用过程：通过创建子类继承SQLiteOpenHelper类，实现它的一些方法来对数据库进行操作。
//  在实际开发中，为了能够更好的管理和维护数据库，我们会封装一个继承自SQLiteOpenHelper类的数据库操作类，然后以这个类为基础，再封装我们的业务逻辑方法。
//SQLiteOpenHelper类的数据库操作方法介绍
//onCreate()  创建数据库  创建数据库时自动调用   onUpgrade()   升级数据库
//close()  关闭所有打开的数据库对象
//execSQL()  可进行增删改操作, 不能进行查询操作
//query()、rawQuery()   查询数据库
//insert()   插入数据
//delete()  删除数据
//getWritableDatabase()   创建或打开可以读/写的数据库  通过返回的SQLiteDatabase对象对数据库进行操作
//getReadableDatabase()  创建或打开可读的数据库    通过返回的SQLiteDatabase对象对数据库进行操作

public class MySQLiteOpenHelper extends SQLiteOpenHelper {
    private static final String SQL_CREATE_ENTRIES=
            "CREATE TABLE " + NewsContract.NewsEntry.TABLE_NAME + " (" +
             NewsContract.NewsEntry._ID + " INTEGER PRIMARY KEY, " +
             NewsContract.NewsEntry.COLUMN_NAME_TITLE + " VARCHAR(200), " +
             NewsContract.NewsEntry.COLUMN_NAME_AUTHOR + " VARCHAR(100), " +
             NewsContract.NewsEntry.COLUMN_NAME_IMAGE + " VARCHAR(100) " + ")";
    private static final String SQL_DELETE_ENTRIES =
            "DROP TABLE IF EXISTS " + NewsContract.NewsEntry.TABLE_NAME;
    public static final int DATABASE_VERSION = 1;
    public static final String DATABASE_NAME = "news.db";
    private Context mContext;
    //SQLiteOpenHelper 基类构造函数接收四个参数：
    //• Context context，上下⽂对象；
    //• String name，数据库名；
    //• SQLiteDatabase.CursorFactory factory，创建 Cursor 的⼯⼚类，默认传递 null 即可；
    //• int version，数据库版本号；
    //如果数据库结构发⽣了变化，则递增 version 即可
    public MySQLiteOpenHelper(Context context){
        super(context,DATABASE_NAME,null,DATABASE_VERSION);
        mContext=context;
    }
    //onCreate() ⽅法在数据库⽂件不存在时将被执⾏，通常只执⾏⼀次，因此
    //在该⽅法中应该完成数据库表的创建以及数据初始化的操作，如代码3.10所⽰
    @Override
    public void onCreate(SQLiteDatabase db) {
        db.execSQL(SQL_CREATE_ENTRIES);
        initDb(db);
    }
    private void initDb(SQLiteDatabase db){
        Resources resources=mContext.getResources();
        String[]  titles=resources.getStringArray(R.array.titles);
        String[] authors=resources.getStringArray(R.array.authors);
        TypedArray images = resources.obtainTypedArray(R.array.images);
        int length=0;
        length=Math.min(titles.length,authors.length);
        length=Math.min(length,images.length());
        for(int i=0;i<length;i++){
            ContentValues values=new ContentValues();
            values.put(NewsContract.NewsEntry.COLUMN_NAME_TITLE,titles[i]);
            values.put(NewsContract.NewsEntry.COLUMN_NAME_AUTHOR,authors[i]);
            values.put(NewsContract.NewsEntry.COLUMN_NAME_IMAGE,images.getString(i));
            long r=db.insert(NewsContract.NewsEntry.TABLE_NAME,null,values);
            values.clear();
        }
    }

    @Override
    public void onUpgrade(SQLiteDatabase db, int oldVersion, int newVersion) {
        db.execSQL(SQL_DELETE_ENTRIES);
        onCreate(db);
    }
}
