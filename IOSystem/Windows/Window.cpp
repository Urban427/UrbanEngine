#include "Window.h"

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
	width = 1024;
	height = 768;
	
	WNDCLASSEX wc = {};
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
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

	dummyDc = GetDC(_hwnd);

	if (!_hwnd)
	{
		return 1;
	}

	ShowWindow(_hwnd, SW_SHOW);
	UpdateWindow(_hwnd);


	buffer = new int[width * height];
	for(int i = 0; i < width * height; i++)
	{
		buffer[i] = 0;
	}
	
	HDC hdc = GetDC(_hwnd);
	HBITMAP map = CreateBitmap(width, height, 1, 8 * 4, buffer);
	SetBitmapBits(map, width * height * 4, buffer);
	HDC src = CreateCompatibleDC(hdc);
	SelectObject(src, map);
	BitBlt(hdc, 0, 0, width, height, src, 0, 0, SRCCOPY);
	DeleteDC(src);
	DeleteObject(map);
	ReleaseDC(_hwnd, hdc);
	
	return 0;
}

char Window::broadcast()
{
	MSG msg;
	while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
	{
		if (msg.message == WM_QUIT)
		{
			return 1;
		}
		DispatchMessage(&msg);
	}

	for(int i = 0; i < width * height; i++)
	{
		buffer[i] += 1;
	}
	
	HDC hdc = GetDC(_hwnd);
	HBITMAP map = CreateBitmap(width, height, 1, 8 * 4, buffer);
	SetBitmapBits(map, width * height * 4, buffer);
	HDC src = CreateCompatibleDC(hdc);
	SelectObject(src, map);
	BitBlt(hdc, 0, 0, width, height, src, 0, 0, SRCCOPY);
	DeleteDC(src);
	DeleteObject(map);
	ReleaseDC(_hwnd, hdc);

	//SetBitmapBits(renderer->map, renderer->buffer.height * 4 * renderer->buffer.width, renderer->buffer.buffer);
	//HDC src = CreateCompatibleDC(hdc);
	//SelectObject(src, renderer->map);
	//BitBlt(hdc, 0, 0, renderer->buffer.width, renderer->buffer.height, src, 0, 0, SRCCOPY);
	//DeleteDC(src);


	Sleep(1);
	return 0;
}