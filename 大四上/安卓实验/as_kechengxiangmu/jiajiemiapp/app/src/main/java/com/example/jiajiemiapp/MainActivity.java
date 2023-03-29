package com.example.jiajiemiapp;

import androidx.annotation.RequiresApi;
import androidx.appcompat.app.AppCompatActivity;

import android.content.ClipData;
import android.content.ClipboardManager;
import android.content.Context;
import android.os.Build;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.TextView;
import android.widget.Toast;

import java.util.Random;

public class MainActivity extends AppCompatActivity {
    private EditText emiwen,emishi;
    private Button bjiami,bjiemi;
    private TextView txianshi;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        kongjianfuzhi();
        bjiami.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                String miwen=emiwen.getText().toString();
                String mishi=emishi.getText().toString();
                if(miwen=="null"|miwen=="")Toast.makeText(getApplicationContext(), "密文不能为空", Toast.LENGTH_SHORT).show();
                txianshi.setText(shujuchuli(miwen,mishi,1));

            }
        });

        bjiemi.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                String miwen=emiwen.getText().toString();
                String mishi=emishi.getText().toString();
                if(miwen=="null"|miwen==""|miwen.length()<4)Toast.makeText(getApplicationContext(), "密文不能为空|太短", Toast.LENGTH_SHORT).show();
                txianshi.setText(shujuchuli(miwen,mishi,0));
            }
        });
        txianshi.setOnClickListener(new View.OnClickListener() {
            @RequiresApi(api = Build.VERSION_CODES.M)
            @Override
            public void onClick(View v) {
                String st=txianshi.getText().toString();
                //获取剪贴板管理器：
                ClipboardManager cm = (ClipboardManager) getSystemService(Context.CLIPBOARD_SERVICE);
                // 创建普通字符型ClipData
                ClipData mClipData = ClipData.newPlainText("密文", st);
                // 将ClipData内容放到系统剪贴板里。
                cm.setPrimaryClip(mClipData);
                Toast toast=Toast.makeText(getApplicationContext(), "复制成功", Toast.LENGTH_SHORT);
                //显示toast信息
                toast.show();
            }
        });
    }


    private void kongjianfuzhi(){
        emishi=findViewById(R.id.mishi);
        emiwen=findViewById(R.id.miwen);
        bjiami=findViewById(R.id.jiami_button);
        bjiemi=findViewById(R.id.jiemi_button);
        txianshi=findViewById(R.id.xianshi);
    }
    private String shujuchuli(String miwen,String mishi ,int pd){
        if(mishi==null|mishi.isEmpty())mishi="1";
        Log.d("jiami",miwen);

        int j=miwen.length();
        int ms=Integer.parseInt(mishi);
        char st[]=miwen.toCharArray();
        int y,b,l;
        if(pd==1){
            Random r = new Random();
            y = r.nextInt(10);
            b=r.nextInt(10);
            l=r.nextInt(10);
        } else{
            y=Integer.parseInt(st[0]+"");
            b=Integer.parseInt(st[1]+"");
            l=Integer.parseInt(st[2]+"");
        }
        Log.d("jiami","ybl:"+y+b+l);
        char mi[]=(y+"2000"+b+"0510"+l+"5656").toCharArray();
        int i=0,t=0;
        if(pd!=1)i=3;
        for(;i<j;i++,t++){
            if(t>=mi.length)t=0;
            if(mi[t]%2==0){
                Log.d("jiami","偶qian"+st[i]);
                if(pd==1) st[i]= (char) (st[i]+mi[t]+ms);
                else  st[i]= (char) (st[i]-mi[t]-ms);
                Log.d("jiami","偶hou"+st[i]);

            }else{
                Log.d("jiami","奇qian"+st[i]);
                if(pd==1) st[i]=(char)(st[i]+mi[t]+ms*ms);
                else st[i]=(char)(st[i]-mi[t]-ms*ms);
                Log.d("jiami","奇hou"+st[i]);
            }
        }
        String jieguo=new String(st);
        if(pd==1){
            Log.d("jiami",y+"");
            Log.d("jiami",y+"");
            Log.d("jiami",l+"");
            Log.d("jiami",""+y+b+l+jieguo);
            return ""+y+b+l+jieguo;
        }else{
            jieguo=jieguo.substring(3);
            Log.d("jiami",jieguo);
            return jieguo;
        }

    }

}

