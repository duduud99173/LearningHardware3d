#pragma once
#include "Bindable.h"


class InputLayout : public Bindable
{
public:
	InputLayout(Graph& gfx, std::vector<D3D11_INPUT_ELEMENT_DESC>& layout, Microsoft::WRL::ComPtr<ID3DBlob>& pBlob);
	void Bind(Graph& gfx);
private:
	Microsoft::WRL::ComPtr<ID3D11InputLayout> pInputLayout;
};