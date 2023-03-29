package com.example.a2_3news;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.widget.ArrayAdapter;
import android.widget.ListView;
import android.widget.SimpleAdapter;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

public class MainActivity extends AppCompatActivity {
    private static final String NEWS_TITLE = "news_title";
    private static final String NEWS_AUTHOR = "news_author";
    private List<Map<String, String>> dataList = new ArrayList<>();

    private void onotdata(){
        int length;
        String[]  titles=getResources().getStringArray(R.array.titles);
        String[] authors=getResources().getStringArray(R.array.authors);
        if(titles.length> authors.length){
            length=authors.length;
        }else{
            length=titles.length;
        }
        for(int i=0;i<length;i++){
            Map map=new HashMap();
            map.put(NEWS_TITLE,titles[i]);
            map.put(NEWS_AUTHOR,authors[i]);
            dataList.add(map);
        }

    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        //数据源的构造操作
        onotdata();
            // simpleAdapter构造器的用法

        //public SimpleAdapter(Context context , keywordstyle
        //              List <? extends Map<String , ?>> data, keywordstyle
        //              int resource , String[] from, int[] to);

        //Context context，表⽰上下⽂对象，可直接传递 MainActivity.this 对象；
        //List<? extends Map<String, ?> > data，表⽰绑定的数据 List 列表，其类型需为 Map<String, ?>；
        //int resource， ListView 的 Item 布局资源，可以为系统预定义或⽤户⾃定义的布局资源；
        //String[] from，  Map中的 String 类型的 Key，与 to 结合⼀起  将 Map中的该 key 对应的 value 绑定到 to 数组中的资源上；
        //int[]to，  resource布局资源中对应的控件 id，与 from 结合完成 Map中value数据与控件的绑定；

        SimpleAdapter simpleAdapter=new SimpleAdapter(
                MainActivity.this,
                dataList,
                android.R.layout.simple_list_item_2,
                //from 数组，则是构造 List<Map<String, String> > 对象时所使⽤到的两个 key： NEWS_TITLE 及 NEWS_AUTHOR
                //to 数组中则是 android.R.layout.simple_list_item_2 资源中的两个 TextView 控件标签的 id。
                new String[]{NEWS_TITLE,NEWS_AUTHOR},
                new int[]{android.R.id.text1,android.R.id.text2});


        ListView lvNewsList = findViewById(R.id.newslist);
        lvNewsList.setAdapter(simpleAdapter);




    }
}


//    //adapeterr 绑定 titles 字符串数组作为 ListView 控件的数据源。
//    // 并指定 Item 的布局为系统预定义的 android.R.layout.simple_list_item_1，
//    //该布局指包含 1 个 TextView 控件。
//    ArrayAdapter<String> adapter=new ArrayAdapter<String>(
//            MainActivity.this,android.R.layout.simple_list_item_1,titles);
//    ListView newlist=findViewById(R.id.newslist);
//        newlist.setAdapter(adapter);//设置数据适配器adapte