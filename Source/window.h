#pragma once
#include <Windows.h>
#include <optional>

class Window
{
	class WindowClass
	{
	public:
		static HINSTANCE GetInstance();
		static const wchar_t* GetName();
	private:
		WindowClass();
		~WindowClass();
		HINSTANCE hInst;
		static WindowClass wndClass;
		const wchar_t* wndClassName = L"myclass";
	};
public:
	Window(int w, int h);
	~Window();
	HWND GetHandle();
	static std::optional<int> ProcessMessage();

private:
	static LRESULT CALLBACK HandleMsg(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
private:
	const wchar_t* wndName = L"myengine";
	HWND hWnd;
};