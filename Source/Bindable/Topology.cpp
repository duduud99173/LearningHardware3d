#include "Topology.h"

Topology::Topology(D3D11_PRIMITIVE_TOPOLOGY topo)
	: topology(topo) {}

void Topology::Bind(Graph& gfx)
{
	GetContext(gfx)->IASetPrimitiveTopology(topology);
}