package com.example.f_service;

import androidx.annotation.RequiresApi;
import androidx.appcompat.app.AppCompatActivity;

import android.content.Intent;
import android.os.Build;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;

public class MainActivity extends AppCompatActivity {
    Button b1;
    EditText t1;
    String s;
    static final  String TEXT="text";
    static final String TITLE="title";
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        b1=findViewById(R.id.button);
        t1=findViewById(R.id.txtview);
        s=t1.getText().toString();
        b1.setOnClickListener(new View.OnClickListener() {
            @RequiresApi(api = Build.VERSION_CODES.O)
            @Override
            public void onClick(View v) {
                Intent serviceIntent =new Intent(MainActivity.this,
                        MyService.class);
                serviceIntent.putExtra(MainActivity.TEXT,s+s);
                serviceIntent.putExtra(MainActivity.TITLE,s);
                startForegroundService(serviceIntent);
            }
        });

    }
}