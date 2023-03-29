package com.example.a2_3denglu;

import androidx.appcompat.app.AppCompatActivity;

import android.graphics.Typeface;
import android.os.Bundle;
import android.text.InputType;
import android.view.View;
import android.widget.EditText;
import android.widget.ImageView;

public class MainActivity extends AppCompatActivity {
    private Boolean bPwdSwitch = false;
    private EditText et;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        final ImageView ivPwdSwitch = findViewById(R.id.iv_pwd_switch);
        et = findViewById(R.id.et_pwd);

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
}