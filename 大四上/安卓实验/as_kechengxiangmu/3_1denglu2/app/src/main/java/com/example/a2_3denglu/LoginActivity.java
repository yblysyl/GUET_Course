package com.example.a2_3denglu;

import androidx.appcompat.app.AppCompatActivity;

import android.content.Context;
import android.content.SharedPreferences;
import android.graphics.Typeface;
import android.os.Bundle;
import android.text.InputType;
import android.text.TextUtils;
import android.view.View;
import android.widget.Button;
import android.widget.CheckBox;
import android.widget.EditText;
import android.widget.ImageView;

public class LoginActivity extends AppCompatActivity {
    private Boolean bPwdSwitch = false;
    private EditText et;
    private EditText etaccount;
    private EditText etpwd;
    private CheckBox cbrember;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        final ImageView ivPwdSwitch = findViewById(R.id.iv_pwd_switch);
        et = findViewById(R.id.et_pwd);
        etaccount=findViewById(R.id.et_account);
        etpwd=findViewById(R.id.et_pwd);
        cbrember=findViewById(R.id.cb_remember_pwd);
        Button btLogin = findViewById(R.id.bt_login);
        button_onclick(btLogin);
        xinxijiazai();

        ivPwdSwitch.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                 bPwdSwitch = !bPwdSwitch;
                 if (bPwdSwitch) {
                     ivPwdSwitch.setImageResource(
                             R.drawable.ic_baseline_visibility_24);
                     et.setInputType(InputType.TYPE_TEXT_VARIATION_VISIBLE_PASSWORD);
                     } else {
                            ivPwdSwitch.setImageResource(
                            R.drawable.ic_baseline_visibility_off_24);
                            et.setInputType(InputType.TYPE_TEXT_VARIATION_PASSWORD | InputType.TYPE_CLASS_TEXT);
                            et.setTypeface(Typeface.DEFAULT);
                     }
                 }
        });

    }

    //SharedPreferences是一种轻量级的数据存储方式，采用键值对的存储方式。
    //SharedPreferences只能存储少量数据，大量数据不能使用该方式存储，支持存储的数据类型有booleans, floats, ints, longs, and strings。
    //SharedPreferences存储到一个XML文件中的，路径在/data/data/<packagename>/shared_prefs/下，

    //getSharedPreferences(String name, int mode)
    //通过Context调用该方法获得对象。它有两个参数，第一个name 指定了SharedPreferences存储的文件的文件名，第二个参数mode 指定了操作的模式。
    // 这种方式获取的对象创建的文件 可以被整个应用所有组件使用，有指定的文件名。
    //Context.MODE_PRIVATE：默认模式，创建的文件只能由 调用的应用程序（或者共享相同用户ID的应用程序）访问。

    //SharedPreferences添加或更新数据，通过SharedPreferences 获取 SharedPreferences.Editor，操作文件数据，最后通过commit()或apply()提交修改。

    public void button_onclick(Button buent){
        buent.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                String spFileName=getResources().getString(R.string.shared_preferences_file_name);
                String accountKey=getResources().getString(R.string.login_account_name);
                String passwordKey=getResources().getString(R.string.login_password);
                String rememberPassworKey=getResources().getString(R.string.login_remember_password);
                SharedPreferences spFile=getSharedPreferences(
                        spFileName,
                        Context.MODE_PRIVATE);
                SharedPreferences.Editor editor=spFile.edit();
                if(cbrember.isChecked()){
                    String password=etpwd.getText().toString();
                    String account=etaccount.getText().toString();
                    editor.putString(accountKey,account);
                    editor.putString(passwordKey,password);
                    editor.putBoolean(rememberPassworKey,true);
                    editor.apply();
                }else {
                    editor.remove(accountKey);
                    editor.remove(passwordKey);
                    editor.remove(rememberPassworKey);
                    editor.apply();

                }
            }
        });
    }
    public void xinxijiazai(){
        String spFileName=getResources().getString(R.string.shared_preferences_file_name);
        String accountKey=getResources().getString(R.string.login_account_name);
        String passwordKey=getResources().getString(R.string.login_password);
        String rememberPassworKey=getResources().getString(R.string.login_remember_password);
        SharedPreferences spFile=getSharedPreferences(
                spFileName,
                Context.MODE_PRIVATE);
        String account=spFile.getString(accountKey,null);
        String password=spFile.getString(passwordKey,null);
        Boolean rememberPassword=spFile.getBoolean(rememberPassworKey,false);
        if(account != null &&!TextUtils.isEmpty(account)){
            etaccount.setText(account);
        }
        if(password !=null && !TextUtils.isEmpty(password)){
            etpwd.setText(password);
        }
        cbrember.setChecked(rememberPassword);
    }

}