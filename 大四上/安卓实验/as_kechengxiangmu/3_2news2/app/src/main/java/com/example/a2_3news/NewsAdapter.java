package com.example.a2_3news;

import android.content.Context;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.ArrayAdapter;
import android.widget.ImageView;
import android.widget.TextView;

import java.util.List;

public class NewsAdapter extends ArrayAdapter<News> {

    private List<News> mNewsData;
    private Context mContext;
    private int resourceId;

    public NewsAdapter(Context context , int resourceId , List<News> data) {
        super(context , resourceId , data);
        this.mContext = context;
        this.mNewsData = data;
        this.resourceId = resourceId;
    }
    @Override
    public View getView(int position , View convertView , ViewGroup parent) {
        News news = getItem(position);
        View view;
        view = LayoutInflater.from(getContext()).inflate(resourceId, parent, false);
        TextView tvTitle = view.findViewById(R.id.tv_title);
        TextView tvAuthor = view.findViewById(R.id.tv_subtitle);
        ImageView ivImage = view.findViewById(R.id.iv_image);
        tvTitle.setText(news.getTitle());
        tvAuthor.setText(news.getAuthor());
        ivImage.setImageBitmap(news.getImage());
        return view;
    }
//扩充 CursorAdapter这个类是继承于BaseAdapter的它是一个虚类它为Cursor和ListView连接提供了桥梁
    //CursorAdapter是专门给Cursor数据进行适配的  两个主要方法 newView  实例化view bindView 绑定view


    }
