package com.example.ggnews;

import com.google.gson.annotations.SerializedName;

public class BaseResponse <T>{
    private int code;
    private String msg;
    private final static int  RESPONSE_SUCCESS = 0;

    @SerializedName("newslist")
    private T data;
    public BaseResponse(){

    }

    public static int getResponseSuccess() {
        return RESPONSE_SUCCESS;
    }

    public int getCode(){
        return code;
    }

    public void setCode(int code) {
        this.code = code;
    }

    public String getMsg() {
        return msg;
    }

    public void setMsg(String msg) {
        this.msg = msg;
    }

    public T getData() {
        return data;
    }

    public void setData(T data) {
        this.data = data;
    }
}
