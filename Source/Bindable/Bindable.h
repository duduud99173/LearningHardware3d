#pragma once
#include <vector>
#include <iostream>
#include "graphic.h"

class Bindable
{
public:
	virtual void Bind(Graph &gfx) = 0;
	virtual ~Bindable() = default;
protected:
	static ID3D11DeviceContext* GetContext(Graph& gfx);
	static ID3D11Device* GetDevice(Graph& gfx);
};