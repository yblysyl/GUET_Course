package com.example.ggnews;

import androidx.appcompat.app.AppCompatActivity;

import android.content.Intent;
import android.os.Bundle;
import android.webkit.WebView;
import android.webkit.WebViewClient;

public class DetailActivity extends AppCompatActivity {
    private WebView wvNewsDetail;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_detail);
        initView();
        initData();
    }
    private void initData(){
        Intent intent=getIntent();
        if(intent!=null){
            String url=intent.getStringExtra(Constants.NEWS_DETAIL_URL_KEY);
            if(url!=null){
                wvNewsDetail.loadUrl(url);
            }
        }
    }
    private void initView(){
        wvNewsDetail=findViewById(R.id.wv_detail);
        wvNewsDetail.getSettings().setJavaScriptEnabled(true);
        wvNewsDetail.setWebViewClient(new WebViewClient());
    }
}