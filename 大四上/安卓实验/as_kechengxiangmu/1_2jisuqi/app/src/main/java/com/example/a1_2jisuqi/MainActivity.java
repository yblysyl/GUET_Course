package com.example.a1_2jisuqi;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;

public class MainActivity extends AppCompatActivity {
    private int count=0;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        final TextView test1=findViewById(R.id.text);
        Button button=findViewById(R.id.btnCoubt);
        button.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                test1.setText(Integer.toString(++count));
            }
        });



    }
}