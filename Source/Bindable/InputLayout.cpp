#include "InputLayout.h"

InputLayout::InputLayout(Graph& gfx, std::vector<D3D11_INPUT_ELEMENT_DESC>& layout, Microsoft::WRL::ComPtr<ID3DBlob>& pBlob)
{

	GFX_THROW(GetDevice(gfx)->CreateInputLayout(layout.data(), (UINT)std::size(layout), pBlob->GetBufferPointer(), pBlob->GetBufferSize(), pInputLayout.GetAddressOf()));

}

void InputLayout::Bind(Graph& gfx)
{
	GetContext(gfx)->IASetInputLayout(pInputLayout.Get());
}
