#pragma once
#include <DirectXMath.h>

class Camera
{
public:
	DirectX::XMMATRIX GetMatrix();
	void Reset();
	void SpawnControlWindow();
private:
	float r = 20.0f;
	float roll = 0.0f;
	float pitch = 0.0f;
	float yaw = 0.0f;
	float theta = 0.0f;
	float phi = 0.0f;
};