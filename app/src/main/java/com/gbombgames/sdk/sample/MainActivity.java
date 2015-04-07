package com.gbombgames.sdk.sample;

import android.content.Intent;
import android.os.Bundle;
import android.support.v7.app.ActionBarActivity;
import android.util.Log;
import android.view.View;
import android.widget.Button;

import com.gbombgames.GbombClient;


public class MainActivity extends ActionBarActivity {

    private static final String TAG = MainActivity.class.getSimpleName();

    static {
        System.loadLibrary("gbombsdk");
        System.loadLibrary("gbombsample");
    }

    native void login();

    void loginCallback(int code, String data) {

        Log.d(TAG, "code: " + code + ", data: " + data);
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        GbombClient.init(this);

        Button loginBtn = (Button) findViewById(R.id.btn);
        loginBtn.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {

                login();
            }
        });
    }

    protected void onActivityResult(int requestCode, int resultCode, Intent data) {
        GbombClient.onActivityResult(requestCode, resultCode, data);
        super.onActivityResult(requestCode, resultCode, data);
    }

    protected void onResume() {
        GbombClient.onResume();
        super.onResume();
    }
}
