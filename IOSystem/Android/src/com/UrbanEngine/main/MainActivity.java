package com.UrbanEngine.main;

import android.app.Activity;
import android.os.Bundle;
import android.widget.TextView;
import android.widget.Toast;
import android.app.ActivityManager;
import android.content.Context;

import android.opengl.GLSurfaceView;

public class MainActivity extends Activity {
	
	private GLSurfaceView glSurfaceView;
	private boolean rendererSet;
	
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        
		ActivityManager activityManager = (ActivityManager) getSystemService(Context.ACTIVITY_SERVICE);
		final boolean supportsEs2 = activityManager.getDeviceConfigurationInfo().reqGlEsVersion >= 0x20000;
 
		if (!supportsEs2) 
		{
			Toast.makeText(this, "This device does not support OpenGL ES 2.0.", Toast.LENGTH_LONG).show();
			return;
		} 
		
		RendererWrapper rend = new RendererWrapper();
		rend.contect = this;
		//rend.AndroidLogicCreate();
		//rend.debug();
		
		rendererSet = true;
		glSurfaceView = new GLSurfaceView(this);
		glSurfaceView.setEGLContextClientVersion(2);
		glSurfaceView.setRenderer(rend);
		setContentView(glSurfaceView);
		
		//setContentView(R.layout.main);
    }
	
	@Override
	protected void onPause() {
		super.onPause();
	 
		if (rendererSet) {
			glSurfaceView.onPause();
		}
	}
	 
	@Override
	protected void onResume() {
		super.onResume();
	 
		if (rendererSet) {
			glSurfaceView.onResume();
		}
	}
}