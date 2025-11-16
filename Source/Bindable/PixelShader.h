#pragma once
#include "Bindable.h"
#include <string.h>
#include <d3dcompiler.h>
#pragma comment(lib,"d3dcompiler.lib")
using std::wstring;

class PixelShader :public Bindable
{
public:
	PixelShader(Graph& gfx, const wstring& path);
	void Bind(Graph& gfx);
private:
	Microsoft::WRL::ComPtr<ID3DBlob> pBlob;
	Microsoft::WRL::ComPtr<ID3D11PixelShader> pPixelShader;
};