package com.example.a2_1xiaoxifasong;

import androidx.appcompat.app.AppCompatActivity;

import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.Toast;

public class MainActivity extends AppCompatActivity {
static String sd="chuansong";
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        final EditText et=findViewById(R.id.message);
        Button but =findViewById(R.id.send_message);
        but.setOnClickListener(new View.OnClickListener(){

            @Override
            public void onClick(View v) {
                String message=et.getText().toString();
                Intent intent=new Intent(MainActivity.this,MessageActivity.class);
                intent.putExtra(sd,message);
                startActivity(intent);
                Toast.makeText(MainActivity.this,message,Toast.LENGTH_SHORT).show();
            }
        });
    }
}