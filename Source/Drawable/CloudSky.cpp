#include "CloudSky.h"
#include <memory>

CloudSky::CloudSky(Graph& gfx)
{
	auto pvs = std::make_unique<VertexShader>(gfx, L"Shader\\CloudVS.cso");
	auto vsbc = pvs->GetByteCode();
	std::vector<unsigned short> indices;

	AddStaticIndexBuffer(std::make_unique<IndexBuffer>(gfx, indices));
	AddStaticBind(std::move(pvs));
	AddStaticBind(std::make_unique<PixelShader>(gfx, L"Shader\\CloudPS.cso"));
	AddStaticBind(std::make_unique<Topology>(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP));
	AddStaticBind(std::make_unique<PSSampler>(gfx, 3u));
	AddStaticBind(std::make_unique<PSTexture>(gfx, Volume::FromRawFile("Assets\\Noise\\worleynoise.raw", 256,256,256),3u));


	AddBind(std::make_unique<PixelConstantBuffer<TimeData>>(gfx, timeData, 3u));
}

DirectX::XMMATRIX CloudSky::GetTransformMatrix() const
{
	return DirectX::XMMatrixIdentity();
}

void CloudSky::Update(float dt)
{
	timeData.time += dt;

}

void CloudSky::UpdateCbuf(Graph& gfx)
{
	auto p = QueryBindable<PixelConstantBuffer<TimeData>>();
	assert(p != nullptr);
	p->Update(gfx, timeData);
}