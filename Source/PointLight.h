#pragma once
#include "graphic.h"
#include "Bindable\ConstantBuffer.hpp"
#include "Drawable\SolidSphere.h"

class PointLight
{
public:
	PointLight(Graph& gfx, float r);
	void DrawMesh(Graph& gfx);
	void SpawnControlWindow();
	void BindCBuf(DirectX::FXMMATRIX viewMatrix);
private:
	void Reset();
	void BindMeshColor();
	DirectX::XMVECTOR GetViewedPos(DirectX::FXMMATRIX viewMatrix);
private:
	struct PointLightCBuf
	{
		DirectX::XMFLOAT3 pos;
		float lightIntensity;
		DirectX::XMFLOAT3 diffColor;
		float padding;
		DirectX::XMFLOAT3 ambient;
		float attCon;
		float attLin;
		float attQuad;
		float padding2;
		float padding3;
	};
private:
	Graph& gfx;
	PointLightCBuf cbData;
	PixelConstantBuffer<PointLightCBuf> cBuf;
	SolidSphere mesh;
};