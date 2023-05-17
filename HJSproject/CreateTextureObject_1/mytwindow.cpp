#include "mytwindow.h"

BOOL MyWindow::run()
{
	if (!init()) { release(); return FALSE; };

	MSG msg = { 0 };
	BOOL runFlag = TRUE;

	while (TRUE)
	{
		if (msg.message == WM_QUIT) { break; }

		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			if (!frame() || !render())
			{
				runFlag = FALSE; break;
			}
		}
	}

	release();

	return runFlag;
}

LRESULT MyWindow::MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_DESTROY:
	{
		PostQuitMessage(0);
		return 0;
	}
	case WM_CLOSE:
	{
		if (MessageBox(hwnd, L"Quit Application?", L"Close Box", MB_OKCANCEL) == IDOK)
		{
			DestroyWindow(hwnd);
		}

		return 0;
	}
	}

	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

PCWSTR MyWindow::WindowClassName()
{
	return L"CreateTextureObject_1";
}

bool MyWindow::init()
{
	MyDXDevice::getInstance().create();
	MyDXDevice::getInstance().init();
	MyRenderManager::getInstance().create(hwnd, clientWidth, clientHeight);
	MyRenderManager::getInstance().init();

	return true;
}

bool MyWindow::frame()
{
	return true;
}

bool MyWindow::render()
{
	PRERENDER;

	//TO DO

	POSTRENDER;
	return true;
}

bool MyWindow::release()
{
	return false;
}