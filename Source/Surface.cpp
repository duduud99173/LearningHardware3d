#include "Surface.h"
#include <Windows.h>
#include <gdiplus.h>
#pragma comment(lib,"gdiplus.lib")


Surface::Surface(unsigned int width, unsigned int height) : width(width), height(height), pBuffer(std::make_unique<Color[]>(width*height))
{
}

Surface::Color* Surface::GetBufferPtr() const
{
	return pBuffer.get();
}

unsigned int Surface::GetWidth() const
{
	return width;
}

unsigned int Surface::GetHeight() const
{
	return height;
}

Surface::Surface(unsigned int width, unsigned int height, std::unique_ptr<Color[]> pBuffer) : width(width), height(height), pBuffer(std::move(pBuffer))
{
}



Surface Surface::FromFile(const std::string& filename)
{
	unsigned int height = 0;
	unsigned int width = 0;
	std::unique_ptr<Color[]> pBuffer;

	wchar_t wideName[512];
	mbstowcs_s(nullptr, wideName, filename.c_str(), _TRUNCATE);
	Gdiplus::Bitmap bitmap(wideName);
	height = bitmap.GetHeight();
	width = bitmap.GetWidth();
	pBuffer = std::make_unique<Color[]>(height * width);
	for (unsigned int i = 0; i < height; i++)
	{
		for (unsigned int j = 0; j < width; j++)
		{
			Gdiplus::Color c;
			bitmap.GetPixel(j, i, &c);
			pBuffer[i * width + j] = c.GetValue();
		}
	}
	return Surface(width, height, std::move(pBuffer));
}
