package com.example.a2_3news;

import androidx.appcompat.app.AppCompatActivity;

import android.content.res.TypedArray;
import android.database.Cursor;
import android.database.sqlite.SQLiteDatabase;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.os.Bundle;
import android.util.Log;
import android.widget.ArrayAdapter;
import android.widget.ListView;
import android.widget.SimpleAdapter;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

public class MainActivity extends AppCompatActivity {
    private static final String NEWS_ID = "news_id";
    private static final String NEWS_AUTHOR = "news_author";
    private List<News> newlist = new ArrayList<>();

    MySQLiteOpenHelper myDbHlper;
        SQLiteDatabase db;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        myDbHlper = new MySQLiteOpenHelper(MainActivity.this);
        //详情注释见MySQLiteOpenHelpe.java
        db=myDbHlper.getReadableDatabase();
        //游标（cursor）：一个存储在mysql服务器上数据库查询，它不是一条select 语句，而是被语句检索出来的结果集。
        //  Cursor 是每行的集合。使用 moveToFirst() 定位第一行。你必须知道每一列的名称。你必须知道每一列的数据类型。Cursor 是一个随机的数据源。所有的数据都是通过下标取得。
        //关于 Cursor 的重要方法：
        //c.move(int offset); //以当前位置为参考,移动到指定行
        //c.moveToFirst();    移动到第一行    c.moveToLast();  移动到最后一行
        //c.moveToPrevious(); //移动到前一行
        //c.moveToNext();     //移动到下一行
        //c.isFirst();        是否指向第一条   c.isLast();     是否指向最后一条
        //c.isNull(int columnIndex);  //指定列是否为空(列基数为0)
        //c.isClosed();       //游标是否已关闭
        //c.getCount();       //总数据项数
        //c.getPosition();    //返回当前游标所指向的行数
        //c.getColumnIndex(String columnName);  返回某列名对应的列索引值，如果不存在返回-1
        //c.getString(int columnIndex);   返回当前行指定列的值  c.close()——关闭游标，释放资源
        Cursor cursor=db.query(
                NewsContract.NewsEntry.TABLE_NAME,
                null,null,null,null,null,null
        );

        //List<News>newsList=new ArrayList<>();
        int titleIndex = cursor.getColumnIndex(NewsContract.NewsEntry.COLUMN_NAME_TITLE);
        int authorIndex=cursor.getColumnIndex(NewsContract.NewsEntry.COLUMN_NAME_AUTHOR);
        int imageIndex=cursor.getColumnIndex(NewsContract.NewsEntry.COLUMN_NAME_IMAGE);
        while (cursor.moveToNext()){
            News news=new News();
            String title=cursor.getString(titleIndex);
            String author=cursor.getString(authorIndex);
            String image=cursor.getString(imageIndex);
            Bitmap bitmap = BitmapFactory.decodeStream(getClass().getResourceAsStream("/"+image));
            news.setTitle(title);
            news.setAuthor(author);

            news.setImage(bitmap);
            newlist.add(news);
        }


        NewsAdapter newsAdapter=new NewsAdapter(
                MainActivity.this,
                R.layout.list_item,
                newlist);


        ListView lvNewsList = findViewById(R.id.newslist);
        lvNewsList.setAdapter(newsAdapter);
    }
}