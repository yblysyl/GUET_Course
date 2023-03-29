package com.example.ggnews;

import android.content.Context;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.ArrayAdapter;
import android.widget.ImageView;
import android.widget.ListView;
import android.widget.TextView;

import androidx.annotation.NonNull;
import androidx.recyclerview.widget.RecyclerView;

import com.bumptech.glide.Glide;

import java.util.List;

public class NewsAdapter extends ArrayAdapter<News> {
    private List<News> mNewsData;
    private Context mContext;
    private int resourceId;

    public NewsAdapter(Context context, int resourceId ,List<News> data) {
        super(context, resourceId,data);
        this.mContext=context;
        this.mNewsData=data;
        this.resourceId=resourceId;
    }
    @Override
    public View getView(int position, View convertView, ViewGroup parent){
        News news=getItem(position);
        View view;
        final ViewHolder vh;
        if(convertView==null){
            view= LayoutInflater.from(getContext()).inflate(resourceId,parent,false);
            vh=new ViewHolder();
            vh.tvTitle=view.findViewById(R.id.tv_title);
            vh.tvSource=view.findViewById(R.id.tv_subtitle);
            vh.ivDelete=view.findViewById(R.id.iv_delete);
            vh.tvPublishTime=view.findViewById(R.id.tv_publish_time);
            vh.ivImage=view.findViewById(R.id.iv_image);
            view.setTag(vh);
        }else {
            view=convertView;
            vh=(ViewHolder) view.getTag();
        }
        vh.tvTitle.setText(news.getmTitle());
        vh.tvSource.setText(news.getmSource());
        vh.ivDelete.setTag(position);
        vh.tvPublishTime.setText(news.getmPublishTime());
        Glide.with(mContext).load(news.getmPicUrl()).into(vh.ivImage);
        return view;
    }
    class ViewHolder{
        TextView tvTitle;
        TextView tvSource;
        ImageView ivImage;
        TextView tvPublishTime;
        ImageView ivDelete;
    }
}
