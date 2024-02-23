package com.UrbanEngine.main;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

import android.content.Context;
import android.opengl.GLSurfaceView.Renderer;
import android.opengl.GLES20;


public class RendererWrapper implements Renderer
{
	private NativeLib nativeLib;
	
	public void create(Context content)
	{
		nativeLib = new NativeLib();
		nativeLib.contect = content;
	}
	
	public void handleTouchPress(float x, float y) {
        nativeLib.on_touch_press(x, y);
    }
	
    public void onSurfaceCreated(GL10 gl, EGLConfig config) {
		nativeLib.AndroidLogicCreate();
    }
 
    public void onSurfaceChanged(GL10 gl, int width, int height) {
		nativeLib.AndroidLogicUpdate(width, height);
    }
 
    public void onDrawFrame(GL10 gl) {
        nativeLib.AndroidLogicDraw();
    }	
};
