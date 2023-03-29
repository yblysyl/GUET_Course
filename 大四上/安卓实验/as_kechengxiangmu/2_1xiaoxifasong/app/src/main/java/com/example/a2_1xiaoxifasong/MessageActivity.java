package com.example.a2_1xiaoxifasong;

import androidx.appcompat.app.AppCompatActivity;

import android.content.Intent;
import android.os.Bundle;
import android.widget.TextView;

public class MessageActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_message);
        TextView te=findViewById(R.id.jsmessage);
        Intent intent=getIntent();
        String message=intent.getStringExtra(MainActivity.sd);
        if(message !=null){
            if(te !=null){
                te.setText(message);
            }
        }
    }
}