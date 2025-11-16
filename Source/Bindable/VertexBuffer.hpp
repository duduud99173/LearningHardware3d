#pragma once
#include "Bindable.h"



class VertexBuffer : public Bindable
{
public:
	template<typename V>
	VertexBuffer(Graph& gfx, std::vector<V>& vertices) : stride(sizeof(V))
	{
		D3D11_SUBRESOURCE_DATA vtb = {};
		vtb.pSysMem = vertices.data();

		D3D11_BUFFER_DESC bd = {};
		bd.ByteWidth = UINT(sizeof(V) * vertices.size());
		bd.Usage = D3D11_USAGE_DEFAULT;
		bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		bd.CPUAccessFlags = 0;
		bd.StructureByteStride = sizeof(V);
		GetDevice(gfx)->CreateBuffer(&bd, &vtb, pVertexBuffer.GetAddressOf());
		
	}
	void Bind(Graph& gfx) override
	{
		const UINT offset = 0u;
		GetContext(gfx)->IASetVertexBuffers(0, 1, pVertexBuffer.GetAddressOf(), &stride, &offset);
	}
private:
	const UINT stride;
	Microsoft::WRL::ComPtr<ID3D11Buffer> pVertexBuffer;
};