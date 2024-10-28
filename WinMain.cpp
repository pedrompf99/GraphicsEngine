#include "Window.h"
#include <string>
#include <iostream>     // std::cout, std::ios
#include <sstream>      // std::ostringstream

/*
	Callback on the messages received by the window
*/

int CALLBACK WinMain(
	HINSTANCE	hInstance,
	HINSTANCE	hPrevInstance,
	LPSTR		lpCmdLine,
	int			nCmdShow)
{
	Window wnd(800, 300, L"Test Window");
	
	MSG msg;
	BOOL gResult;
	while ((gResult = GetMessage(&msg, nullptr, 0, 0)) > 0) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	if (gResult == -1)
		return -1;
	return msg.wParam;
}