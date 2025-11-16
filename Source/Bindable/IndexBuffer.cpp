#include "IndexBuffer.h"

IndexBuffer::IndexBuffer(Graph& gfx, std::vector<unsigned short>& indices) : count((UINT)indices.size())
{
	if (count == 0)
	{
		return;
	}

	D3D11_SUBRESOURCE_DATA isd = {};
	D3D11_BUFFER_DESC ibd = {};

	isd.pSysMem = indices.data();

	ibd.ByteWidth = UINT(count * sizeof(unsigned short));
	ibd.Usage = D3D11_USAGE_DEFAULT;
	ibd.BindFlags = D3D11_BIND_INDEX_BUFFER;
	ibd.CPUAccessFlags = 0;
	ibd.StructureByteStride = sizeof(unsigned short);
	GFX_THROW(GetDevice(gfx)->CreateBuffer(&ibd, &isd, pIndexBuffer.GetAddressOf()));
}

void IndexBuffer::Bind(Graph& gfx)
{
	GetContext(gfx)->IASetIndexBuffer(pIndexBuffer.Get(), DXGI_FORMAT_R16_UINT, 0);
}

UINT IndexBuffer::Count()
{
	return count;
}