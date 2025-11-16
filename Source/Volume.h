#pragma once
#include <memory>
#include <string>

class Volume
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
		Color& operator=(Color col) { dword = col.dword; return *this; }
	};
	Volume(unsigned int width, unsigned int height, unsigned int depth);
	Color* GetBufferPtr() const;
	unsigned int GetWidth()	const;
	unsigned int GetHeight() const;
	unsigned int GetDepth() const;
	static Volume FromRawFile(const std::string& filename,
		unsigned int width, unsigned int height, unsigned int depth,
		size_t channels = 4);
private:
	Volume(unsigned int width, unsigned int height, unsigned int depth, std::unique_ptr<Color[]> pBuffer);
private:
	std::unique_ptr<Color[]> pBuffer;
	unsigned int height;
	unsigned int width;
	unsigned int depth;
};