#pragma once
#include "Bindable.h"
#include <string.h>
#include <d3dcompiler.h>
#pragma comment(lib,"d3dcompiler.lib")
using std::wstring;

class VertexShader :public Bindable
{
public:
	VertexShader(Graph& gfx, const wstring& path);
	void Bind(Graph& gfx);
	Microsoft::WRL::ComPtr<ID3DBlob>& GetByteCode();
private:
	Microsoft::WRL::ComPtr<ID3DBlob> pBlob;
	Microsoft::WRL::ComPtr<ID3D11VertexShader> pVertexShader;
};