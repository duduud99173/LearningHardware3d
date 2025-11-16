#pragma once
#include "Bindable.h"
#include "Surface.h"
#include "Volume.h"

class Texture : public Bindable
{
public:
	Texture( Graph& gfx, const Surface& s, UINT slot = 0u);
	Texture(Graph& gfx, const Volume& v, UINT slot = 0u);
protected:
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> pTextureView;
	UINT slot;
};

class VSTexture : public Texture
{
public:
	using Texture::Texture;
	void Bind(Graph& gfx);
};

class PSTexture : public Texture
{
public:
	using Texture::Texture;
	void Bind(Graph& gfx);
};