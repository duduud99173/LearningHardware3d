#pragma once
#include "DrawableBase.h"

class SolidSphere : public DrawableBase<SolidSphere> 
{
public:
	SolidSphere(Graph& gfx, float r);
	DirectX::XMMATRIX GetTransformMatrix() const override;
	void Update(float dt) override;
	void SetPosition(DirectX::XMFLOAT3 position);
	void SetColor(DirectX::XMFLOAT3 col);
	void UpdateColorPSBuf(Graph& gfx);
	
private:
	struct LightColor
	{
		DirectX::XMFLOAT3 col;
		float padding;
	};
private:
	DirectX::XMFLOAT3 pos = { 0.0f,0.0f,0.0f };
	DirectX::XMFLOAT3 color = { 1.0f,1.0f,1.0f };
	float radius;
};