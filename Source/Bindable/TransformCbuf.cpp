#include "TransformCbuf.h"

TransformCbuf::TransformCbuf(Graph& gfx, const Drawable& parent,UINT slot)
	: parent(parent) 
{
	if (!pVcbuf)
	{
		pVcbuf = std::make_unique<VertexConstantBuffer<Transforms>>(gfx,slot);
	}
}

void TransformCbuf::Bind(Graph& gfx)
{
	const DirectX::XMMATRIX modelView = parent.GetTransformMatrix()*gfx.GetCameraMatrix();

	const Transforms tf =
	{
		DirectX::XMMatrixTranspose(modelView),

		DirectX::XMMatrixTranspose(
			modelView *
			gfx.GetProjMatrix()
		)
	};

	pVcbuf->Update(gfx, tf);
	pVcbuf->Bind(gfx);
}   

std::unique_ptr<VertexConstantBuffer<TransformCbuf::Transforms>> TransformCbuf::pVcbuf;