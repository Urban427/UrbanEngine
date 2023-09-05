package com.UrbanEngine.main;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

import android.widget.Toast;
import android.opengl.GLES20;
import android.opengl.GLSurfaceView.Renderer;

import android.content.res.Resources;
import android.app.Activity;
import java.io.FileOutputStream;
import java.io.ByteArrayOutputStream;
import java.io.InputStream;
import java.io.BufferedInputStream;
import java.io.File;
import java.io.InputStreamReader;
import java.io.BufferedReader;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.IOException;
import android.content.Context;
import android.os.Environment;
import java.nio.charset.StandardCharsets;


public class RendererWrapper implements Renderer
{
	public Context contect;
	
    static{
        System.loadLibrary("Filter");
    }
    public native void AndroidLogicCreate();
    public native void AndroidLogicUpdate();
    public native void AndroidLogicDraw();
	
    public void onSurfaceCreated(GL10 gl, EGLConfig config) {
       AndroidLogicCreate();
    }
 
    public void onSurfaceChanged(GL10 gl, int width, int height) {
        AndroidLogicUpdate();
    }
 
    public void onDrawFrame(GL10 gl) {
        AndroidLogicDraw();
		//AndroidLogicUpdate();
		//GLES20.glClear(GLES20.GL_COLOR_BUFFER_BIT);
    }
	
	
	
	public void printText(byte[] text) 
	{
		Toast.makeText(contect, new String(text, StandardCharsets.UTF_8), Toast.LENGTH_SHORT).show();
    }
	
	public byte[] readFile(byte[] filename)
	{
		String filenm = new String(filename, StandardCharsets.UTF_8);
		byte buffer[];
		try{
			InputStream is = contect.getResources().getAssets().open(filenm);
			int size = is.available();
			buffer = new byte[size];
			is.read(buffer);
			is.close();
		}
		catch(IOException io) {
			buffer = new byte[1];
		}
		
		return buffer;
	}	
};
