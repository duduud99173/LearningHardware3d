#pragma once
#include "DrawableBase.h"
#include "Bindable/TransformCbuf.h"
#include <random>

class Box : public DrawableBase<Box>
{
public:
	Box( Graph& gfx, std::mt19937& rng, 
		std::uniform_real_distribution<float>& rdr,
		std::uniform_real_distribution<float>& rdd,
		std::uniform_real_distribution<float>& rda,
		std::uniform_real_distribution<float>& rdb);
	DirectX::XMMATRIX GetTransformMatrix() const override;
	void Update(float dt);
	void SpawnControlWindow();
	static void SpawnStaticControlWindow(Graph& gfx);
private:
	void BindObjCBuf();
	static void BindStaticObjCBuf(Graph& gfx);
private:
	struct ObjectCBuf
	{
		DirectX::XMFLOAT3 materialColor = {0.5f,0.5f,0.5f};
		float specularIntensity = 0.6f;
		float specularPower = 30.0f;
		float padding[3];
	};
	static ObjectCBuf staticObjCBuf;
	ObjectCBuf objCBuf;
	

	//positional
	float r;
	float chi;
	float theta; 
	float phi;
	float roll;
	float yaw;
	float pitch;

	float dchi;
	float dtheta;
	float dphi;
	float droll;
	float dyaw;
	float dpitch;

	Graph& gfx;
};

