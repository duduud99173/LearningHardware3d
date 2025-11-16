#pragma once
#include "Bindable.h"


class IndexBuffer : public Bindable
{
public:
	IndexBuffer(Graph& gfx, std::vector<unsigned short>& indices);
	void Bind(Graph& gfx);
	UINT Count();
private:
	UINT count;
	Microsoft::WRL::ComPtr<ID3D11Buffer> pIndexBuffer = nullptr;
};