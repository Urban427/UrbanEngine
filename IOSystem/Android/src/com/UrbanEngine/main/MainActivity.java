package com.UrbanEngine.main;

import android.app.Activity;
import android.os.Bundle;
import android.widget.TextView;

public class MainActivity extends Activity {
    static{
        System.loadLibrary("Filter");
    }
    public native String AndroidLogicProcess();
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.main);
        TextView text1 = (TextView)findViewById(R.id.my_text1);
        text1.setText(AndroidLogicProcess());
    }
}