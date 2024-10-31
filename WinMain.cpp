#include "Window.h"
#include <string>
#include <iostream>     // std::cout, std::ios
#include <sstream>      // std::ostringstream
#include "Exception.h"

/*
	Callback on the messages received by the window
*/

int CALLBACK WinMain(
	HINSTANCE	hInstance,
	HINSTANCE	hPrevInstance,
	LPSTR		lpCmdLine,
	int			nCmdShow)
{
	try {
		Window wnd(800, 300, "Test Window");

		MSG msg;
		BOOL gResult;
		while ((gResult = GetMessage(&msg, nullptr, 0, 0)) > 0) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
			if (wnd.kbd.KeyIsPressed(VK_MENU)) {
				MessageBox(nullptr, "Something happened!", "alt key was pressed", MB_OK | MB_ICONEXCLAMATION);
			}
		}
		if (gResult == -1)
			return -1;
		return msg.wParam;
	}
	catch (const Exception& e) {
		MessageBox(nullptr, e.what(), e.GetType(), MB_OK | MB_ICONEXCLAMATION);
	} 
	catch (const std::exception& e) {
		MessageBox(nullptr, e.what(), "Standard Exception", MB_OK | MB_ICONEXCLAMATION);
	}
	catch (...) {
		MessageBox(nullptr, "No details available", "Unknown Exception", MB_OK | MB_ICONEXCLAMATION);
	}
	
}