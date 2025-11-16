#pragma once
#include "Box.h"
#include <memory>
#include "Geometry\Cube.hpp"
#include "Geometry\Sphere.hpp"
#include "imgui\imgui.h"
#include <assert.h>

Box::ObjectCBuf Box::staticObjCBuf;

Box::Box(Graph& gfx, std::mt19937& rng,
	std::uniform_real_distribution<float>& rdr,
	std::uniform_real_distribution<float>& rdd,
	std::uniform_real_distribution<float>& rda,
	std::uniform_real_distribution<float>& rdb)
	:
	gfx(gfx),
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
	dpitch(rdd(rng))
{
	if (!IsStaticInitialized())
	{
		struct Vertex
		{
			DirectX::XMFLOAT3 pos;
			DirectX::XMFLOAT3 n;
		};
		


		IndexedTriangleList<Vertex> model = Cube::MakeIndependent<Vertex>();

		model.SetNormalInpendentFlat();

		auto pvs = std::make_unique<VertexShader>(gfx, L"Shader\\PhongVS.cso");
		auto vsbc = pvs->GetByteCode();

		std::vector<D3D11_INPUT_ELEMENT_DESC> layout = {
			{"Position",0,DXGI_FORMAT_R32G32B32_FLOAT,0,0,D3D11_INPUT_PER_VERTEX_DATA,0},
			{"Normal",0,DXGI_FORMAT_R32G32B32_FLOAT,0,12,D3D11_INPUT_PER_VERTEX_DATA,0}
		};
		AddStaticIndexBuffer(std::make_unique<IndexBuffer>(gfx, model.indices));
		AddStaticBind(std::make_unique<VertexBuffer>(gfx, model.vertices));
		AddStaticBind(std::move(pvs));
		AddStaticBind(std::make_unique<PixelShader>(gfx, L"Shader\\PhongPS.cso"));
		AddStaticBind(std::make_unique<InputLayout>(gfx, layout, vsbc));
		AddStaticBind(std::make_unique<Topology>(D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST));

		AddStaticBind(std::make_unique<PixelConstantBuffer<ObjectCBuf>>(gfx, staticObjCBuf, 1u));

	}
	else
	{
		SetIndexPointer();
	}
	AddBind(std::make_unique<TransformCbuf>(gfx, *this));
	
	
}

DirectX::XMMATRIX Box::GetTransformMatrix() const 
{
	return DirectX::XMMatrixRotationRollPitchYaw(pitch, yaw, roll)
		* DirectX::XMMatrixTranslation(r, 0.0f, 0.0f)
		* DirectX::XMMatrixRotationRollPitchYaw(theta, phi, chi);

}

void Box::Update(float dt)
{
	chi += dt * dchi;
	theta += dt * dtheta;
	phi += dt * dphi;
	roll += dt * droll;
	yaw += dt * dyaw;
	pitch += dt * dpitch;
}

void Box::SpawnControlWindow()
{
	bool dirty = false;
	if (ImGui::Begin("a box"))
	{
		dirty = dirty || ImGui::SliderFloat("specular intensity", &objCBuf.specularIntensity, 0.0f, 1.0f);
		dirty = dirty || ImGui::SliderFloat("specular power", &objCBuf.specularPower, 0.0f, 30.0f, "%.1f", ImGuiSliderFlags_Logarithmic);
		dirty = dirty || ImGui::ColorEdit3("material color", &objCBuf.materialColor.x);
	}
	ImGui::End();
	if (dirty)
	{
		BindObjCBuf();
	}
}

void Box::SpawnStaticControlWindow(Graph& gfx)
{
	bool dirty = false;
	if (ImGui::Begin("all box"))
	{
		dirty = dirty || ImGui::SliderFloat("specular intensity", &staticObjCBuf.specularIntensity, 0.0f, 1.0f);
		dirty = dirty || ImGui::SliderFloat("specular power", &staticObjCBuf.specularPower, 0.0f, 30.0f, "%.1f", ImGuiSliderFlags_Logarithmic);
		dirty = dirty || ImGui::ColorEdit3("material color", &staticObjCBuf.materialColor.x);
	}
	ImGui::End();
	if (dirty)
	{
		BindStaticObjCBuf(gfx);
	}
}

void Box::BindObjCBuf()
{
	auto p = QueryBindable<PixelConstantBuffer<ObjectCBuf>>();
	assert(p != nullptr);
	p->Update(gfx, objCBuf);
}

void Box::BindStaticObjCBuf(Graph& gfx)
{
	auto p = QueryStaticBindable<PixelConstantBuffer<ObjectCBuf>>();
	assert(p != nullptr);
	p->Update(gfx, staticObjCBuf);
}
