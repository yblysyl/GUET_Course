package com.example.foregroundservice;

import androidx.appcompat.app.AppCompatActivity;

import android.content.Intent;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.Button;

public class MainActivity extends AppCompatActivity {

    Button startService;
    Intent intent;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        startService = (Button)findViewById(R.id.button);
        startService.setOnClickListener(new View.OnClickListener() {

            @Override
            public void onClick(View v) {
                // TODO Auto-generated method stub
                intent = new Intent(MainActivity.this, MyService.class);
                Log.d("TAG","开启服务");
                startService(intent);
                Log.d("TAG","结束服务");
            }
        });
    }
    protected void onStop() {
        // TODO Auto-generated method stub
        super.onStop();
        stopService(intent);
    }
}