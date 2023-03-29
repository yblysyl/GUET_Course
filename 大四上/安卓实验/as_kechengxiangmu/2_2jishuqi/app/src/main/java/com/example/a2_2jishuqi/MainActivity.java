package com.example.a2_2jishuqi;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;

public class MainActivity extends AppCompatActivity {

    private static final String COUNT_VALUE = "count_value";
    private int count=0;

    protected void onSaveInstanceState (Bundle outstatr) {
        outstatr.putInt(COUNT_VALUE,count);
        super.onSaveInstanceState(outstatr);
    }

    protected void onRestoreInstanceState(Bundle savedInstanceState){
        super.onRestoreInstanceState(savedInstanceState);
        count=savedInstanceState.getInt(COUNT_VALUE);
        final TextView test1=findViewById(R.id.text);
        test1.setText(Integer.toString(count));

    }


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