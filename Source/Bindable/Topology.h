#pragma once
#include "Bindable.h"

class Topology : public Bindable
{
public:
	Topology(D3D11_PRIMITIVE_TOPOLOGY topo);
	void Bind(Graph& gfx) override;
private:
	D3D11_PRIMITIVE_TOPOLOGY topology;
};