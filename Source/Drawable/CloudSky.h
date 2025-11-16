#pragma once
#include "DrawableBase.h"
#include "Bindable/TransformCbuf.h"

class CloudSky : public DrawableBase<CloudSky>
{
public:
	CloudSky(Graph& gfx);
	DirectX::XMMATRIX GetTransformMatrix() const override;
	void Update(float dt);
	void UpdateCbuf(Graph& gfx);
	
	struct TimeData
	{
		float time;
		float padding[3];
	} timeData;

};