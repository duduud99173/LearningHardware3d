#include "Sampler.h"

Sampler::Sampler(Graph& gfx, UINT slot)
	:
	slot(slot)
{
	D3D11_SAMPLER_DESC sd = {};
	sd.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	sd.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	sd.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	sd.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	GetDevice(gfx)->CreateSamplerState(&sd, pSampler.GetAddressOf());
}

void PSSampler::Bind(Graph& gfx)
{
	GetContext(gfx)->PSSetSamplers(slot, 1u, pSampler.GetAddressOf());
}

void VSSampler::Bind(Graph& gfx)
{
	GetContext(gfx)->VSSetSamplers(slot, 1u, pSampler.GetAddressOf());
}
