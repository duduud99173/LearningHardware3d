#pragma once
#include "Bindable.h"
#include "Drawable/Drawable.h"

class TransformCbuf : public Bindable
{
public:
	TransformCbuf(Graph& gfx, const Drawable& parent, UINT slot = 0u);
	void Bind(Graph& gfx) override;
private:
	struct Transforms
	{
		DirectX::XMMATRIX modelView;
		DirectX::XMMATRIX modelProjView;
	};
	static std::unique_ptr<VertexConstantBuffer<Transforms>> pVcbuf;
	const Drawable& parent;
};