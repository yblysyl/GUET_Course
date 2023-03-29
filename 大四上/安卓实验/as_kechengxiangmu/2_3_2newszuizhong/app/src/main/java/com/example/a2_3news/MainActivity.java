package com.example.a2_3news;

import androidx.appcompat.app.AppCompatActivity;

import android.content.res.TypedArray;
import android.os.Bundle;
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


        private void inotdata(){
        int length;
        String[]  titles=getResources().getStringArray(R.array.titles);
        String[] authors=getResources().getStringArray(R.array.authors);
        TypedArray images = getResources().obtainTypedArray(R.array.images);

        if(titles.length> authors.length){
            length=authors.length;
        }else{
            length=titles.length;
        }
        for(int i=0;i<length;i++){
            News news = new News();
            news.setTitle(titles[i]);
            news.setAuthor(authors[i]);
            news.setImageId(images.getResourceId(i, 0));
            newlist.add(news);
        }

    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        inotdata();

        NewsAdapter newsAdapter=new NewsAdapter(
                MainActivity.this,
                R.layout.list_item,
                newlist);


        ListView lvNewsList = findViewById(R.id.newslist);
        lvNewsList.setAdapter(newsAdapter);
    }
}