#include "Window.h"
#include "../../MAIN/resource.h"


LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
		case WM_DESTROY:
		{
			PostQuitMessage(0);
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
	HGLRC hRC;

	width = 1024;
	height = 768;
	
	WNDCLASSEX wc = {};
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wc.hCursor = LoadCursor(GetModuleHandle(NULL), IDC_ARROW);
	wc.hIcon = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_ICON));
	wc.hInstance = NULL;
	wc.lpszClassName = "UrbanEngineClass";
	wc.lpszMenuName = "";
	wc.lpfnWndProc = WndProc;

	if (!RegisterClassEx(&wc)) {
		return 1;
	}

	RECT rc = { 0, 0, width, height };
	AdjustWindowRect(&rc, WS_SYSMENU, false);

	_hwnd = CreateWindowEx(WS_EX_APPWINDOW,
		"UrbanEngineClass", "UrbanEngine",
		WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU,
		CW_USEDEFAULT, CW_USEDEFAULT,
		rc.right, rc.bottom, NULL, NULL, NULL, NULL);

	if (!_hwnd)
	{
		return 1;
	}

	ShowWindow(_hwnd, SW_SHOW);





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


	Sleep(1);
	return 0;
}



Rect Window::getInnerSize()
{
	RECT rc;
	GetClientRect(_hwnd, &rc);
	return Rect(rc.right - rc.left, rc.bottom - rc.top);
}