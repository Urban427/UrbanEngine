#include "Window.h"
#include <stdio.h>
#include <time.h>
#include "../../MAIN/resource.h"

Window* win;

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
		case WM_DESTROY:
		{
			PostQuitMessage(0);
			break;
		}
		case WM_MOVE:
		{
			int left = (int)(short) LOWORD(lParam);
			int top  = (int)(short) HIWORD(lParam);
			win->setPos(left, top);
			break;
		}
		case WM_SIZE:
		{
			unsigned int width  = LOWORD(lParam);
            unsigned int height = HIWORD(lParam);
			win->setSize(width, height);
			break;
		}
		case WM_SETFOCUS:
		{
			win->onFocus();
			break;
		}
		case WM_KILLFOCUS:
		{
			win->onKillFocus();
			break;
		}
		default:
		{
			return DefWindowProc(hwnd, msg, wParam, lParam);
		}
	}
	return DefWindowProc(hwnd, msg, wParam, lParam);
}

Window::Window()
{
}

Window::~Window()
{
	DestroyWindow(_hwnd);
}

char Window::init()
{
	win = this;
	HGLRC hRC;

	width = 1680;
	height = 1024;
	
	WNDCLASSEX wc = {};
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wc.hCursor = LoadCursor(GetModuleHandle(NULL), IDC_ARROW);
	wc.hIcon = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_ICON));
	wc.hInstance = NULL;
	wc.lpszClassName = "Urban";
	wc.lpszMenuName = "";
	wc.lpfnWndProc = WndProc;
	wc.style = NULL;

	if (!RegisterClassEx(&wc)) {
		return 1;
	}

	RECT rc = { 0, 0, width, height };
	AdjustWindowRect(&rc, WS_SYSMENU, false);

	_hwnd = CreateWindowEx(WS_EX_OVERLAPPEDWINDOW,
		"Urban", "Urban",
		WS_OVERLAPPEDWINDOW,
		rc.left,  rc.top,
		rc.right, rc.bottom, NULL, NULL, NULL, NULL);

	if (!_hwnd)
	{
		return 1;
	}
	GetClientRect(_hwnd, &rc);
	width   = rc.right - rc.left;
	height  = rc.bottom - rc.top;
	left    = rc.left;
	top     = rc.top;
	centerX = left + width  / 2;
	centerY = top  + height / 2;

	ShowWindow(_hwnd, SW_SHOW);
	UpdateWindow(_hwnd);



	//OpenGL
	PIXELFORMATDESCRIPTOR pfd;
	int iFormat;
	hDC = GetDC(_hwnd);
	ZeroMemory(&pfd, sizeof(pfd));
	pfd.nSize = sizeof(pfd);
	pfd.nVersion = 1;
	pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
	pfd.iPixelType = PFD_TYPE_RGBA;
	pfd.cColorBits = 24;
	pfd.cDepthBits = 16;
	pfd.iLayerType = PFD_MAIN_PLANE;
	iFormat = ChoosePixelFormat(hDC, &pfd);
	SetPixelFormat(hDC, iFormat, &pfd);
	hRC = wglCreateContext(hDC);
	wglMakeCurrent(hDC, hRC);
	
	
	return 0;
}

char Window::broadcast()
{
	MSG msg;
	if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
	{
		if (msg.message == WM_QUIT)
		{
			return 1;
		}
		else
		{
			DispatchMessage(&msg);
		}
	}
	SwapBuffers(hDC);
	return 0;
}

void Window::setSize(unsigned int width, unsigned int height)
{
	RECT rc;
	GetClientRect(_hwnd, &rc);
	this->width   = width;
	this->height  = height;
	this->left    = rc.left;
	this->top     = rc.top;
	this->centerX = left + width  / 2;
	this->centerY = top  + height / 2;
}

void Window::setPos(int x, int y)
{
	left = x;
	top  = y;
	centerX = left + width  / 2;
	centerY = top  + height / 2;
}
Rect Window::getCenter()
{
	return Rect(centerX, centerY);
}

Rect Window::getInnerSize()
{
	return Rect(left, top, width, height);
}

void Window::onFocus()
{
	
}

void Window::onKillFocus()
{
	
}



//time
void Window::initTime()
{
	time = GetTickCount();
}

double Window::getDeltaTime()
{
	long new_time = GetTickCount();
	double ans = (new_time - time) / 1000.0f;
	time = new_time;
    return ans;
}