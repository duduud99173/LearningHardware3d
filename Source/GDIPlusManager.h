#pragma once
#include <Windows.h>
#include <gdiplus.h>

class GDIPlusManager
{
public:
	GDIPlusManager();
	~GDIPlusManager();
private:
	static ULONG_PTR token;
	static int ref_count;
};