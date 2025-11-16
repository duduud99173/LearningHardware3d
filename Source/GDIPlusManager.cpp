#include "GDIPlusManager.h"
#pragma comment (lib,"gdiplus.lib")


int GDIPlusManager::ref_count = 0;
ULONG_PTR GDIPlusManager::token = 0;

GDIPlusManager::GDIPlusManager()
{
	if (ref_count++ == 0)
	{
		Gdiplus::GdiplusStartupInput input;
		input.SuppressBackgroundThread = false;
		input.GdiplusVersion = 1;
		Gdiplus::GdiplusStartup(&token, &input, nullptr);
	}
}

GDIPlusManager::~GDIPlusManager()
{
	if (--ref_count == 0)
	{
		Gdiplus::GdiplusShutdown(token);
	}
}
