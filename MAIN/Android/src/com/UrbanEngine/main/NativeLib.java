package com.UrbanEngine.main;

import android.widget.Toast;
import android.content.Context;

import java.io.IOException;
import java.io.InputStream;
import java.nio.charset.StandardCharsets;


public class NativeLib
{
	public Context contect;
	static
	{
        System.loadLibrary("Filter");
    }
	
	public native void AndroidLogicCreate();
    public native void AndroidLogicUpdate(int width, int height);
    public native void on_touch_press(float x, float y);
    public native void AndroidLogicDraw();
	
	
	public void debug() 
	{
		
    }	
	
	public void printText(byte[] text, byte[] text2, int number) 
	{
		Toast.makeText(contect, new String(text, StandardCharsets.UTF_8), Toast.LENGTH_SHORT).show();
		Toast.makeText(contect, new String(text2, StandardCharsets.UTF_8), Toast.LENGTH_SHORT).show();
		Toast.makeText(contect, Integer.toString(number), Toast.LENGTH_SHORT).show();
    }
	
	public byte[] readFile(byte[] filename)
	{
		String filenm = new String(filename, StandardCharsets.UTF_8);
		byte buffer[];
		try{
			InputStream is = contect.getResources().getAssets().open(filenm);
			int size = is.available();
			buffer = new byte[size + 4];
			is.read(buffer, 4, size);
			is.close();
			
			buffer[0] = (byte) (size >> 24);
			buffer[1] = (byte) (size >> 16);
			buffer[2] = (byte) (size >> 8);
			buffer[3] = (byte) (size     );
		}
		catch(IOException io) 
		{
			buffer = new byte[1];
		}
		
		return buffer;
	}	
};