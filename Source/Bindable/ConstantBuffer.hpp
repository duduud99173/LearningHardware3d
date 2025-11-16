#pragma once
#include "Bindable.h"

template<typename T>
class ConstantBuffer : public Bindable
{
public:
	ConstantBuffer(Graph& gfx, T& constbuf, UINT slot=0u) : slot(slot)
	{
		D3D11_BUFFER_DESC desc = {};
		desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		desc.MiscFlags = 0;
		desc.Usage = D3D11_USAGE_DYNAMIC;
		desc.ByteWidth = sizeof(constbuf);
		D3D11_SUBRESOURCE_DATA cbsd = {};
		cbsd.pSysMem = &constbuf;
		GFX_THROW(GetDevice(gfx)->CreateBuffer(&desc, &cbsd, pConstantBuffer.GetAddressOf()));
	}
	ConstantBuffer(Graph& gfx,UINT slot=0u) : slot(slot)
	{
		D3D11_BUFFER_DESC desc = {};
		desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		desc.MiscFlags = 0;
		desc.Usage = D3D11_USAGE_DYNAMIC;
		desc.ByteWidth = sizeof(T);
		GFX_THROW(GetDevice(gfx)->CreateBuffer(&desc, nullptr, pConstantBuffer.GetAddressOf()));
	}
	void Update(Graph& gfx, const T& constbuf)
	{
		D3D11_MAPPED_SUBRESOURCE msr;
		GFX_THROW(GetContext(gfx)->Map(pConstantBuffer.Get(), 0u, D3D11_MAP_WRITE_DISCARD, 0u, &msr));
		memcpy(msr.pData, &constbuf, sizeof(constbuf));
		GetContext(gfx)->Unmap(pConstantBuffer.Get(), 0u);
	}
protected:
	Microsoft::WRL::ComPtr<ID3D11Buffer> pConstantBuffer;
	UINT slot;
};

template<typename C>
class VertexConstantBuffer : public ConstantBuffer<C>
{
	using ConstantBuffer<C>::pConstantBuffer;
	using ConstantBuffer<C>::slot;
	using Bindable::GetContext;
public:
	using ConstantBuffer<C>::ConstantBuffer;	
	void Bind(Graph& gfx) override
	{
		GetContext(gfx)->VSSetConstantBuffers(slot, 1, pConstantBuffer.GetAddressOf());
	}
};

template<typename C>
class PixelConstantBuffer : public ConstantBuffer<C>
{
	using Bindable::GetContext;
	using ConstantBuffer<C>::slot;
	using ConstantBuffer<C>::pConstantBuffer;
public:
	using ConstantBuffer<C>::ConstantBuffer;
	void Bind(Graph& gfx) override
	{
		GetContext(gfx)->PSSetConstantBuffers(slot, 1, pConstantBuffer.GetAddressOf());
	}
};