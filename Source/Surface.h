#pragma once
#include <memory>
#include <string>

class Surface
{
public:
	class Color
	{
	private:
		unsigned int dword;
	public:
		Color() : dword() {}
		Color(Color& color) : dword(color.dword) {}
		Color(unsigned int dword) : dword(dword) {}
		Color(unsigned int a, unsigned int r, unsigned int g, unsigned int b) : dword(a << 24u | r << 16u | g << 8u | b) {}
		Color(unsigned int r, unsigned int g, unsigned int b) : dword(r << 16u | g << 8u | b) {}
		Color& operator=(Color col){ dword = col.dword; return *this; }
	};
	Surface( unsigned int width, unsigned int height );
	Color* GetBufferPtr() const;
	unsigned int GetWidth()	const;
	unsigned int GetHeight() const ;
	static Surface FromFile(const std::string& filename);
private:
	Surface(unsigned int width, unsigned int height, std::unique_ptr<Color[]> pBuffer);
private:
	std::unique_ptr<Color[]> pBuffer;
	unsigned int height;
	unsigned int width;
};