#pragma once
#include "DrawableBase.h"


class ImportedObject : public DrawableBase<ImportedObject>
{
public:
	ImportedObject(Graph& gfx, const char* filename);
	DirectX::XMMATRIX GetTransformMatrix() const override;
	void Update(float dt);

private:
	struct ObjectCBuf
	{
		DirectX::XMFLOAT3 materialColor = { 0.5f,0.5f,0.5f };
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
};