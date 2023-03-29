package com.example.ggnews;

import androidx.appcompat.app.AppCompatActivity;

import android.content.Intent;
import android.os.Bundle;
import android.os.NetworkOnMainThreadException;
import android.telecom.Call;
import android.util.Log;
import android.view.View;
import android.widget.AdapterView;
import android.widget.ListView;

import com.google.gson.Gson;
import com.google.gson.reflect.TypeToken;

import java.io.IOException;
import java.lang.reflect.Type;
import java.util.ArrayList;
import java.util.List;

import okhttp3.OkHttpClient;
import okhttp3.Request;
import okhttp3.Response;

public class MainActivity extends AppCompatActivity {
    String TAG="TAG";
    private ListView lvNewsList;
    private List<News> newsData;
    private NewsAdapter adapter;
    private int page=1;
    private int mCurrentColIndex = 0;

    // 总结
    /*
    实验页面分三个部分 listview主页列表 list_item每一项页面 detail详细内容

    先实例化listview 绑定 适配器与listitem_ news建立联系；
    news类 存储接受的数据。 NewsAdpter 适配器。绑定数据
    Constants 定义本实验中用到的常量；

    主要是引用的三个库的使用 okhttp （⽹络请求库）、 reques和onResponse的使用 发送和接受数据
    在reques中通过 类NewsRequest 来将访问的url作为一个类来调用，方便更改。
gson（json 解析库）、解析json里的泛型类然后再将泛型类转为news类
glide（图⽚加载库）用于适配器中的图像加载。
    *
    * */

    private int[] mCols = new int[]{Constants.NEWS_COL5 ,
            Constants.NEWS_COL7 , Constants.NEWS_COL8 ,
            Constants.NEWS_COL10 , Constants.NEWS_COL11};
    private okhttp3.Callback callback = new okhttp3.Callback() {
        @Override
        public void onFailure(okhttp3.Call call, IOException e) {
            Log.e(TAG, "Failed to connect server!");
            e.printStackTrace();
        }

        @Override
        public void onResponse(okhttp3.Call call, Response response) throws IOException {
            if(response.isSuccessful()){
                final String body=response.body().string();
                runOnUiThread(new Runnable() {
                    @Override
                    public void run() {
                        Gson gson=new Gson();
                        Type jsonType=new TypeToken<BaseResponse<List<News>>>(){}.getType();
                        BaseResponse<List<News>> newsListResponse=gson.fromJson(body,jsonType);
                        for(News news: newsListResponse.getData()){
                            adapter.add(news);
                        }
                        adapter.notifyDataSetChanged();
                    }
                });
            }else {

            }
        }
    };

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        initView();//绑定列表每一项点击事件
        initData();//绑定适配器

    }

    private void initData(){
        newsData=new ArrayList<>();
        adapter=new NewsAdapter(MainActivity.this,R.layout.list_item,newsData);
        lvNewsList.setAdapter(adapter);
        rerfreshData(1);   //调用request 申请数据
    }
    private void rerfreshData(final int page){
        new Thread(new Runnable() {
            @Override
            public void run() {
                NewsRequest requestObj=new NewsRequest();
                requestObj.setCol(mCols[mCurrentColIndex]);
                requestObj.setNum(Constants.NEWS_NUM);
                requestObj.setPage(page);
                String urlParams=requestObj.toString();
                Request request=new Request.Builder().url(Constants.GENERAL_NEWS_URL+urlParams)
                        .get().build();
                try {
                    OkHttpClient client=new OkHttpClient();
                    client.newCall(request).enqueue(callback);
                }catch (NetworkOnMainThreadException e){
                    e.printStackTrace();
                }

            }
        }).start();
    }


    private void initView(){
        lvNewsList=findViewById(R.id.new_list);
        lvNewsList.setOnItemClickListener(new AdapterView.OnItemClickListener() {
            @Override
            public void onItemClick(AdapterView<?> parent, View view, int position, long id) {
                Intent intent=new Intent(MainActivity.this, DetailActivity.class);
                News news=adapter.getItem(position);
                intent.putExtra(Constants.NEWS_DETAIL_URL_KEY,news.getmContentUrl());
                startActivity(intent);
            }
        });
    }
}