#include <Windows.h>
#include <string>
#include <iostream>     // std::cout, std::ios
#include <sstream>      // std::ostringstream

/*
	Callback on the messages received by the window
*/
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) 
{
	switch (msg)
	{
		case WM_CLOSE:
			PostQuitMessage(420);
			break;
		case WM_KEYDOWN:
			if (wParam == 'F') {
				SetWindowTextA(hWnd, "Respect");
			}
			break;
		case WM_KEYUP:
			if (wParam == 'F') {
				SetWindowTextA(hWnd, "Danger");
			}
			break;
		case WM_CHAR:
			{
				static std::string title;
				title.push_back((char)wParam);
				SetWindowTextA(hWnd, title.c_str());
			}
			break;
		case WM_LBUTTONDOWN:
			{
				POINTS pt = MAKEPOINTS(lParam);
				std::ostringstream oss;
				oss << "(" << pt.x << "," << pt.y << ")";
				SetWindowTextA(hWnd, oss.str().c_str());
			}
			break;
	}
	return DefWindowProc(hWnd, msg, wParam, lParam);
}

int CALLBACK WinMain(
	HINSTANCE	hInstance,
	HINSTANCE	hPrevInstance,
	LPSTR		lpCmdLine,
	int			nCmdShow)
{
	const wchar_t pClassName[] = L"GraphicsEngine";

	// register window class
	WNDCLASSEX wc = { 0 };
	wc.cbSize = sizeof(wc);
	wc.style = CS_OWNDC;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = nullptr;
	wc.hCursor = nullptr;
	wc.hbrBackground = nullptr;
	wc.lpszMenuName = nullptr;
	wc.lpszClassName = pClassName;
	wc.hIconSm = nullptr;
	RegisterClassEx(&wc);

	// create window instance
	HWND hWnd = CreateWindowEx(
		0, pClassName, L"Happy Window",
		WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU,
		200, 200, 640, 480,
		nullptr, nullptr, hInstance, nullptr
	);

	// show window
	ShowWindow(hWnd, SW_SHOW);

	// message pump
	MSG msg;
	BOOL gResult;
	while ( (gResult = GetMessage(&msg, nullptr, 0, 0)) > 0) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	if (gResult == -1)
		return -1;
	return msg.wParam;
}