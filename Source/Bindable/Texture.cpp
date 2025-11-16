#include "Texture.h"
#include "Surface.h"

Texture::Texture( Graph& gfx, const Surface& s , UINT slot)
	:
	slot(slot)
{
	D3D11_TEXTURE2D_DESC td = {};
	td.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
	td.Height = s.GetHeight();
	td.Width = s.GetWidth();
	td.MipLevels = 1;
	td.ArraySize = 1;
	td.SampleDesc.Count = 1;
	td.SampleDesc.Quality = 0;
	td.BindFlags = D3D11_BIND_SHADER_RESOURCE;
	td.CPUAccessFlags = 0;
	td.Usage = D3D11_USAGE_DEFAULT;
	td.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA sbr = {};
	sbr.pSysMem = s.GetBufferPtr();
	sbr.SysMemPitch = s.GetWidth() * sizeof(Surface::Color);

	D3D11_SHADER_RESOURCE_VIEW_DESC srv = {};
	srv.Format = td.Format;
	srv.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	srv.Texture2D.MipLevels = 1;
	srv.Texture2D.MostDetailedMip = 0;
	
	Microsoft::WRL::ComPtr<ID3D11Texture2D> pTexture;
	GetDevice(gfx)->CreateTexture2D(&td,&sbr,pTexture.GetAddressOf());
	GetDevice(gfx)->CreateShaderResourceView(pTexture.Get(), &srv, pTextureView.GetAddressOf());
}

Texture::Texture(Graph& gfx, const Volume& v, UINT slot)
	:
	slot(slot)
{
	D3D11_TEXTURE3D_DESC td = {};
	td.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
	td.Height = v.GetHeight();
	td.Width = v.GetWidth();
	td.Depth = v.GetDepth();
	td.MipLevels = 1;
	td.BindFlags = D3D11_BIND_SHADER_RESOURCE;
	td.CPUAccessFlags = 0;
	td.Usage = D3D11_USAGE_DEFAULT;
	td.MiscFlags = 0;

	const UINT bytesPerPixel = 4u;
	D3D11_SUBRESOURCE_DATA sbr = {};
	sbr.pSysMem = v.GetBufferPtr();
	sbr.SysMemPitch = v.GetWidth() * bytesPerPixel;
	sbr.SysMemSlicePitch = sbr.SysMemPitch * v.GetHeight();
	

	D3D11_SHADER_RESOURCE_VIEW_DESC srv = {};
	srv.Format = td.Format;
	srv.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE3D;
	srv.Texture3D.MipLevels = 1;
	srv.Texture3D.MostDetailedMip = 0;

	Microsoft::WRL::ComPtr<ID3D11Texture3D> pTexture;
	GetDevice(gfx)->CreateTexture3D(&td, &sbr, pTexture.GetAddressOf());
	GetDevice(gfx)->CreateShaderResourceView(pTexture.Get(), &srv, pTextureView.GetAddressOf());
}

void VSTexture::Bind( Graph& gfx )
{
	GetContext(gfx)->VSSetShaderResources(slot, 1u, pTextureView.GetAddressOf());
}

void PSTexture::Bind(Graph& gfx)
{
	GetContext(gfx)->PSSetShaderResources(slot, 1u, pTextureView.GetAddressOf());
}
