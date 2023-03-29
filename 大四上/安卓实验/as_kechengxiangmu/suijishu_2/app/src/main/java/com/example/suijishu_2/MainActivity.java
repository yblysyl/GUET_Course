package com.example.suijishu_2;

import static java.lang.Thread.interrupted;
import static java.lang.Thread.sleep;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.os.Message;
import android.util.Log;
import android.view.View;
import android.view.animation.AnimationUtils;
import android.widget.Button;
import android.widget.EditText;
import android.widget.TextView;
import android.widget.Toast;

import java.util.Random;
import java.util.logging.Handler;
import java.util.logging.LogRecord;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

public class MainActivity extends AppCompatActivity {

    public class  xiancheng implements Runnable{
        int st;
        int i;
        TextView xianshi;
        xiancheng(int st, int i){
            this.st=st;
            this.i=i;
            xianshi=findViewById(R.id.suijijieguo);
        }
        public synchronized void gaibian(int ts)  {
            MainActivity.this.runOnUiThread(new Runnable() {
                public void run() {
                        xianshi.setText(ts+"");
                        Log.println(Log.WARN,ts+"",ts+"");
                    }
            });
        }
        @Override
        public void run() {
            int d=0;int t=0;
            if(i<=10){
                d=10;
                t=20;
            }else if(i<=100){
                d=2;
                t=5;
            }else {
                d=1;
                t=3;
            }
            for(int j=0;j<(i*t+st);j++) {
                gaibian(j%i+1);
                try {
                    sleep(d);
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }
            }
        }
    }
        @Override
    protected void onCreate(Bundle savedInstanceState) {

        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        final EditText shuzi=findViewById(R.id.suijifanwei);

        Pattern pattern = Pattern.compile("[1-9][0-9]*");
        Button button=findViewById(R.id.kaishisuiji);

        button.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                String st=shuzi.getText().toString();
                Matcher m = pattern.matcher(st);
                if(m.matches()){
                    int i=Integer.parseInt(st);
                    Random r = new Random();

                    int jieguo = r.nextInt(i)+1;
                    Log.println(Log.WARN,jieguo+"",jieguo+"");
                       Thread th= new Thread(new xiancheng(jieguo,i));
                       th.start();

                }else{
                    Toast.makeText(getApplicationContext(),"请输入有效整数",Toast.LENGTH_LONG).show();
                }




            }
        });
    }
}