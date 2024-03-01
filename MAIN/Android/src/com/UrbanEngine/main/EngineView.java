package com.UrbanEngine.main;

import android.view.SurfaceView;
import android.view.SurfaceHolder;
import android.content.Context;

public class EngineView extends SurfaceView implements SurfaceHolder.Callback
{
	Context context;
	
	public EngineView(Context context)
	{
		super(context);
		
		SurfaceHolder surfaceHolder = getHolder();
		surfaceHolder.addCallback(this);
		
		this.context = context;
		
		
		setFocusable(true);
	}
	
	public void surfaceCreated(SurfaceHolder holder)
	{
		
	}
	
	public void surfaceChanged(SurfaceHolder holder, int format, int width, int height)
	{
		
	}
	
	public void surfaceDestroyed(SurfaceHolder holder)
	{
		
	}
	
	public void draw(Canvas canvas)
	{
		super.draw(canvas);
	}
};