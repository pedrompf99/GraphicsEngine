#include "App.h"

App::App()
	:
	wnd(800, 600, "Test Window")
{};

int App::Go() {
	while (true) {
		if (const auto ecode = Window::ProcessMessages()) {
			return *ecode;
		}
		DoFrame();
	}
}

void App::DoFrame() {

	//const float c = sin(timer.Peek()) / 2.0f + 0.5f;
	wnd.Gfx().ClearBuffer(0, 0, 0);
	wnd.Gfx().DrawTestTriangle();
	wnd.Gfx().EndFrame();
}