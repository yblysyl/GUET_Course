package com.example.bombtest2;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.widget.Toast;

import cn.bmob.v3.Bmob;
import cn.bmob.v3.exception.BmobException;
import cn.bmob.v3.listener.SaveListener;

public class MainActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        Bmob.initialize(this, "9790092874a82b83963e75598da447c1");
        Person p2 = new Person();
        p2.setName("lucky");
        p2.setAddress("北京海淀");
        p2.save(new SaveListener<String>() {
            @Override
            public void done(String objectId, BmobException e) {
                if(e==null){
                    Toast toast=Toast.makeText(getApplicationContext(), "添加数据成功，返回objectId为："+objectId, Toast.LENGTH_SHORT);
                    //显示toast信息
                    toast.show();
                }else{
                    Toast toast=Toast.makeText(getApplicationContext(), "创建数据失败：" + e.getMessage(), Toast.LENGTH_SHORT);
                    //显示toast信息
                    toast.show();
                }
            }
        });
    }
    public void indes(){


    }




}