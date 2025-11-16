#include "PixelShader.h"

PixelShader::PixelShader(Graph& gfx, const wstring& path)
{
	D3DReadFileToBlob(path.c_str(), pBlob.GetAddressOf());
	GFX_THROW(GetDevice(gfx)->CreatePixelShader(pBlob->GetBufferPointer(), pBlob->GetBufferSize(), 0, pPixelShader.GetAddressOf()));
}

void PixelShader::Bind(Graph& gfx)
{
	GetContext(gfx)->PSSetShader(pPixelShader.Get(), 0, 0);
}