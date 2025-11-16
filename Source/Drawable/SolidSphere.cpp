#include "Drawable/SolidSphere.h"
#include "Geometry/Sphere.hpp"
#include "Bindable/TransformCbuf.h"

SolidSphere::SolidSphere(Graph& gfx, float r) : radius(r)
{
	if (!IsStaticInitialized())
	{
		struct Vertex
		{
			DirectX::XMFLOAT3 pos;
		};

		IndexedTriangleList<Vertex> model = Sphere::Make<Vertex>();

		auto pvs = std::make_unique<VertexShader>(gfx, L"Shader\\SolidVS.cso");
		auto vsbc = pvs->GetByteCode();

		std::vector<D3D11_INPUT_ELEMENT_DESC> layout = {
			{"Position",0,DXGI_FORMAT_R32G32B32_FLOAT,0,0,D3D11_INPUT_PER_VERTEX_DATA,0},
		};
		AddStaticIndexBuffer(std::make_unique<IndexBuffer>(gfx, model.indices));
		AddStaticBind(std::make_unique<VertexBuffer>(gfx, model.vertices));
		AddStaticBind(std::move(pvs));
		AddStaticBind(std::make_unique<PixelShader>(gfx, L"Shader\\SolidPS.cso"));
		AddStaticBind(std::make_unique<InputLayout>(gfx, layout, vsbc));
		AddStaticBind(std::make_unique<Topology>(D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST));

	}
	else
	{
		SetIndexPointer();
	}

	LightColor Color;
	Color.col = color;
	AddBind(std::make_unique<TransformCbuf>(gfx, *this));
	AddBind(std::make_unique<PixelConstantBuffer<LightColor>>(gfx, Color));
}

DirectX::XMMATRIX SolidSphere::GetTransformMatrix() const
{
	return DirectX::XMMatrixScaling(radius,radius,radius)*DirectX::XMMatrixTranslation(pos.x,pos.y,pos.z);
}

void SolidSphere::Update(float dt) {}

void SolidSphere::SetColor(DirectX::XMFLOAT3 col)
{
	color = col;
}

void SolidSphere::UpdateColorPSBuf(Graph& gfx)
{
	auto pb = QueryBindable<PixelConstantBuffer<LightColor>>();
	LightColor Color;
	Color.col = color;
	pb->Update(gfx, Color);
}

void SolidSphere::SetPosition(DirectX::XMFLOAT3 position)
{
	pos = position;
}
