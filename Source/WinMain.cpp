#include "app.h"
#include <exception>



int WINAPI wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ PWSTR pCmdLine, _In_ INT nCmdShow)
{
	try
	{
		App app(800, 600);
		app.Go();
		
		return 0;
	}
	catch (std::exception& e)
	{
		MessageBox(nullptr, (wchar_t*)e.what(), nullptr, MB_OK | MB_ICONEXCLAMATION);
	}
	return -1;
}