#include "VertexShader.h"


VertexShader::VertexShader(Graph& gfx, const wstring& path)
{
	GFX_THROW(D3DReadFileToBlob(path.c_str(), pBlob.GetAddressOf()));
	GFX_THROW(GetDevice(gfx)->CreateVertexShader(pBlob->GetBufferPointer(), pBlob->GetBufferSize(), 0, pVertexShader.GetAddressOf()));
}

void VertexShader::Bind(Graph& gfx)
{
	GetContext(gfx)->VSSetShader(pVertexShader.Get(), 0, 0);
}

Microsoft::WRL::ComPtr<ID3DBlob>& VertexShader::GetByteCode()
{
	return pBlob;
}