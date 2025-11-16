#pragma once
#include "Bindable.h"
 
class Sampler : public Bindable
{
public:
	Sampler(Graph& gfx, UINT slot = 0u);

protected:
	Microsoft::WRL::ComPtr<ID3D11SamplerState> pSampler;
	UINT slot;
};

class PSSampler : public Sampler
{
public:
	using Sampler::Sampler;
	void Bind(Graph& gfx);
};

class VSSampler : public Sampler
{
public:
	using Sampler::Sampler;
	void Bind(Graph& gfx);
};