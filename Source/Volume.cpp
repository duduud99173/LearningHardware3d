#include "Volume.h"
#include <Windows.h>
#include <gdiplus.h>
#pragma comment(lib,"gdiplus.lib")
#include <stdexcept>
#include <fstream>
#include <iostream>
#include <filesystem>

Volume::Volume(unsigned int width, unsigned int height, unsigned int depth) 
	: width(width), height(height), depth(depth), pBuffer(std::make_unique<Color[]>(width* height))
{
}

Volume::Color* Volume::GetBufferPtr() const
{
	return pBuffer.get();
}

unsigned int Volume::GetWidth() const
{
	return width;
}

unsigned int Volume::GetHeight() const
{
	return height;
}

unsigned int Volume::GetDepth() const
{
	return depth;
}

Volume::Volume(unsigned int width, unsigned int height, unsigned int depth,  
			std::unique_ptr<Color[]> pBuffer) 
	: 
	width(width), 
	height(height), 
    depth(depth),
	pBuffer(std::move(pBuffer))
{
}



Volume Volume::FromRawFile(const std::string& filename, 
    unsigned int width, unsigned int height, unsigned int depth, 
    size_t channels)
{
    std::ifstream file(filename, std::ios::binary | std::ios::ate);
    if (!file) {
        // 处理文件打开失败
        throw std::runtime_error("Could not open raw file.");
    }

    // 检查文件大小是否匹配预期
    size_t expectedSize = width * height * depth * channels;
    if (file.tellg() != expectedSize) {
        // 处理文件大小不匹配
        throw std::runtime_error("Raw file size mismatch.");
    }

    // 分配内存
    std::unique_ptr<Color[]> pBuffer = std::make_unique<Color[]>(width * height * depth);

    // 读取原始数据（假设文件数据格式与 Color 匹配）
    file.seekg(0, std::ios::beg);
    file.read(reinterpret_cast<char*>(pBuffer.get()), expectedSize);

    return Volume(width, height, depth, std::move(pBuffer));
}
