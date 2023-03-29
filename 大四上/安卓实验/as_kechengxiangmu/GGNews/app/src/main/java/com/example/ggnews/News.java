package com.example.ggnews;

import com.google.gson.annotations.Expose;
import com.google.gson.annotations.SerializedName;

public class News {

    public News(){
    }
    @Expose(serialize = false,deserialize = false)
    private Integer mId;
    @SerializedName("title")
    private String mTitle;
    @SerializedName("description")
    private String mSource;
    @SerializedName("picUrl")
    private String mPicUrl;
    @SerializedName("url")
    private String mContentUrl;
    @SerializedName("ctime")
    private String mPublishTime;

    public Integer getmId() {
        return mId;
    }

    public void setmId(Integer mId) {
        this.mId = mId;
    }

    public String getmTitle() {
        return mTitle;
    }

    public void setmTitle(String mTitle) {
        this.mTitle = mTitle;
    }

    public String getmSource() {
        return mSource;
    }

    public void setmSource(String mSource) {
        this.mSource = mSource;
    }

    public String getmPicUrl() {
        return mPicUrl;
    }

    public void setmPicUrl(String mPicUrl) {
        this.mPicUrl = mPicUrl;
    }

    public String getmContentUrl() {
        return mContentUrl;
    }

    public void setmContentUrl(String mContentUrl) {
        this.mContentUrl = mContentUrl;
    }

    public String getmPublishTime() {
        return mPublishTime;
    }

    public void setmPublishTime(String mPublishTime) {
        this.mPublishTime = mPublishTime;
    }
}
