#include "window.h"
#include "imgui_impl_win32.h"

Window::WindowClass Window::WindowClass::wndClass;

LRESULT					ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);


Window::WindowClass::WindowClass()
	: 
	hInst(GetModuleHandle(nullptr))
{
	WNDCLASS wc = {};
	wc.hInstance = hInst;
	wc.lpfnWndProc = HandleMsg;
	wc.lpszClassName = wndClass.GetName();
	RegisterClass(&wc);
}

Window::WindowClass::~WindowClass()
{
	UnregisterClass(wndClass.wndClassName, wndClass.hInst);
}

HINSTANCE Window::WindowClass::GetInstance()
{
	return wndClass.hInst;
}

const wchar_t* Window::WindowClass::GetName()
{
	return wndClass.wndClassName;
}

Window::Window(int w, int h)
{
	hWnd = CreateWindow(WindowClass::GetName(), wndName, WS_OVERLAPPEDWINDOW, 
		100, 100, w, h,
		0, 0, WindowClass::GetInstance(), 0
	);
	ShowWindow(hWnd, SW_SHOW);
	ImGui_ImplWin32_Init( hWnd );
}

Window::~Window()
{
	ImGui_ImplWin32_Shutdown();
	if (hWnd != nullptr)
	{
		DestroyWindow(hWnd);
	}
}

HWND Window::GetHandle()
{
	return hWnd;
}

std::optional<int> Window::ProcessMessage()
{
	MSG msg;
	while (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
	{
		if (msg.message == WM_QUIT)
			return (int)msg.wParam;

		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return std::nullopt;
}

LRESULT Window::HandleMsg(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	if (ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam))
	{
		return true;
	}
	switch (msg)
	{
	case WM_CLOSE:
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hWnd, msg, wParam, lParam);
}

