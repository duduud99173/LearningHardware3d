#pragma once
#include "SkinnedBox.h"
#include <memory>
#include "Geometry\Cube.hpp"
#include "Geometry\Sphere.hpp"
#include "imgui\imgui.h"

SkinnedBox::ObjectCBuf SkinnedBox::staticObjCBuf;

SkinnedBox::SkinnedBox(Graph& gfx, std::mt19937& rng,
	std::uniform_real_distribution<float>& rdr,
	std::uniform_real_distribution<float>& rdd,
	std::uniform_real_distribution<float>& rda,
	std::uniform_real_distribution<float>& rdb)
	:
	r(rdr(rng)),
	chi(rdb(rng)),
	theta(rdb(rng)),
	phi(rdb(rng)),
	roll(rda(rng)),
	yaw(rda(rng)),
	pitch(rda(rng)),
	dchi(rdd(rng)),
	dtheta(rdd(rng)),
	dphi(rdd(rng)),
	droll(rdd(rng)),
	dyaw(rdd(rng)),
	dpitch(rdd(rng)),
	gfx(gfx)
{
	/*
	r = 0;
	chi = 0;
	theta = 0;
	phi = 0;
	roll = 0;
	yaw = 0;
	pitch = 0;
	dchi = 0;
	dtheta = 0;
	dphi = 0;
	droll = 0;
	dyaw = 0;
	dpitch = 0;
	*/
	if (!IsStaticInitialized())
	{
		struct Vertex
		{
			DirectX::XMFLOAT3 pos;
			DirectX::XMFLOAT2 texCoord;
			DirectX::XMFLOAT3 n;
			DirectX::XMFLOAT3 T;
		};



		IndexedTriangleList<Vertex> model = Cube::MakeSkinnedIndependent<Vertex>();

		model.SetNormalInpendentFlat();
		model.SetTinTBN();

		for (size_t i = 0; i < model.vertices.size(); i++)
		{
			model.vertices[i].texCoord.x /= 2.0f;
			model.vertices[i].texCoord.y /= 2.0f;
		}

		auto pvs = std::make_unique<VertexShader>(gfx, L"Shader\\NormalTexturePhongVS.cso");
		auto vsbc = pvs->GetByteCode();

		std::vector<D3D11_INPUT_ELEMENT_DESC> layout = {
			{"Position",0,DXGI_FORMAT_R32G32B32_FLOAT,0,0,D3D11_INPUT_PER_VERTEX_DATA,0},
			{"TexCoord",0,DXGI_FORMAT_R32G32_FLOAT,0,12,D3D11_INPUT_PER_VERTEX_DATA,0},
			{"Normal",0,DXGI_FORMAT_R32G32B32_FLOAT,0,20,D3D11_INPUT_PER_VERTEX_DATA,0},
			{"Tangent",0,DXGI_FORMAT_R32G32B32_FLOAT,0,32,D3D11_INPUT_PER_VERTEX_DATA,0}
		};
		AddStaticIndexBuffer(std::make_unique<IndexBuffer>(gfx, model.indices));
		AddStaticBind(std::make_unique<VertexBuffer>(gfx, model.vertices));
		AddStaticBind(std::move(pvs));
		AddStaticBind(std::make_unique<PixelShader>(gfx, L"Shader\\NormalTexturePhongPS.cso"));
		AddStaticBind(std::make_unique<InputLayout>(gfx, layout, vsbc));
		AddStaticBind(std::make_unique<Topology>(D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST));
		AddStaticBind(std::make_unique<PSSampler>(gfx));
		AddStaticBind(std::make_unique<PSTexture>(gfx, Surface::FromFile("Assets\\Image\\Tiles132A_2K-JPG_Color.jpg")));
		AddStaticBind(std::make_unique<PSTexture>(gfx, Surface::FromFile("Assets\\Image\\Tiles132A_2K-JPG_NormalDX.jpg"),1u));
		AddStaticBind(std::make_unique<PSTexture>(gfx, Surface::FromFile("Assets\\Image\\Tiles132A_2K-JPG_AmbientOcclusion.jpg"), 2u));
		AddStaticBind(std::make_unique<PixelConstantBuffer<ObjectCBuf>>(gfx, staticObjCBuf, 1u));
	}
	else
	{
		SetIndexPointer();
	}
	AddBind(std::make_unique<TransformCbuf>(gfx, *this));
}

DirectX::XMMATRIX SkinnedBox::GetTransformMatrix() const
{
	return DirectX::XMMatrixRotationRollPitchYaw(pitch, yaw, roll)
		* DirectX::XMMatrixTranslation(r, 0.0f, 0.0f)
		* DirectX::XMMatrixRotationRollPitchYaw(theta, phi, chi);

}

void SkinnedBox::Update(float dt)
{
	chi += dt * dchi;
	theta += dt * dtheta;
	phi += dt * dphi;
	roll += dt * droll;
	yaw += dt * dyaw;
	pitch += dt * dpitch;
}

void SkinnedBox::SpawnControlWindow()
{
	bool dirty = false;
	if (ImGui::Begin("a box"))
	{
		dirty = dirty || ImGui::SliderFloat("specular intensity", &objCBuf.specularIntensity, 0.0f, 1.0f);
		dirty = dirty || ImGui::SliderFloat("specular power", &objCBuf.specularPower, 0.0f, 30.0f, "%.1f", ImGuiSliderFlags_Logarithmic);

	}
	ImGui::End();
	if (dirty)
	{
		BindObjCBuf();
	}
}

void SkinnedBox::SpawnStaticControlWindow(Graph& gfx)
{
	bool dirty = false;
	if (ImGui::Begin("all box"))
	{
		dirty = dirty || ImGui::SliderFloat("specular intensity", &staticObjCBuf.specularIntensity, 0.0f, 1.0f);
		dirty = dirty || ImGui::SliderFloat("specular power", &staticObjCBuf.specularPower, 0.0f, 30.0f, "%.1f", ImGuiSliderFlags_Logarithmic);

	}
	ImGui::End();
	if (dirty)
	{
		BindStaticObjCBuf(gfx);
	}
}

void SkinnedBox::BindObjCBuf()
{
	auto p = QueryBindable<PixelConstantBuffer<ObjectCBuf>>();
	assert(p != nullptr);
	p->Update(gfx, objCBuf);
}

void SkinnedBox::BindStaticObjCBuf(Graph& gfx)
{
	auto p = QueryStaticBindable<PixelConstantBuffer<ObjectCBuf>>();
	assert(p != nullptr);
	p->Update(gfx, staticObjCBuf);
}
