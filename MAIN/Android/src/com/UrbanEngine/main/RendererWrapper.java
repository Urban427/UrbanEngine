package com.UrbanEngine.main;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

import android.content.Context;
import android.opengl.GLSurfaceView.Renderer;
import android.opengl.GLES20;


public class RendererWrapper implements Renderer
{
	private NativeLib nativeLib;
	public Context contect;
	
	public void create(Context content)
	{
		nativeLib = new NativeLib();
		nativeLib.contect = content;
		this.contect = content;
	}
	
	public void handleTouchPress(float x, float y) {
        nativeLib.on_touch_press(x, y);
    }
	
    public void onSurfaceCreated(GL10 gl, EGLConfig config) {
      GLES20.glClearColor(0, 0, 1, 1);
    }
 
    public void onSurfaceChanged(GL10 gl, int width, int height) {
         GLES20.glClearColor(0, 0, 1, 1);
    }
 
    public void onDrawFrame(GL10 gl) {
        nativeLib.AndroidLogicDraw();
    }	
};
