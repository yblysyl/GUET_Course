package com.example.suijishu;

import static java.lang.Thread.sleep;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.TextView;
import android.widget.Toast;

import java.util.Random;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

public class MainActivity extends AppCompatActivity {
    private int count=0;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        final EditText shuzi=findViewById(R.id.suijifanwei);
        final TextView xianshi=findViewById(R.id.suijijieguo);
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

                   xianshi.setText(jieguo+"!");

                }else{

                    Toast.makeText(getApplicationContext(),"请输入有效整数",Toast.LENGTH_LONG).show();
                }
               // xianshi.setText(st);




            }
        });
    }
}