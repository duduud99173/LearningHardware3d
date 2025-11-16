#pragma once
#include "Bindable/VertexBuffer.hpp"
#include "Bindable/IndexBuffer.h"
#include "Bindable/InputLayout.h"
#include "Bindable/PixelShader.h"
#include "Bindable/VertexShader.h"
#include "Bindable/ConstantBuffer.hpp"
#include "Bindable/Topology.h"
#include "Bindable/Sampler.h"
#include "Bindable/Texture.h"
#include "DirectXMath.h"


class Drawable
{
	template<typename T>
	friend class DrawableBase;
public:
	void BindAndDraw( Graph& gfx );
	virtual DirectX::XMMATRIX GetTransformMatrix() const = 0;
	virtual void Update(float dt) = 0;
	virtual ~Drawable() = default;
protected:
	void AddBind(std::unique_ptr<Bindable> bind); 
	void AddIndexBuffer(std::unique_ptr<IndexBuffer> ibuf);
	virtual std::vector<std::unique_ptr<Bindable>>& GetStaticBinds() = 0;
	template<typename T>
	T* QueryBindable()
	{
		for (auto& pb : binds)
		{
			if (auto pt = dynamic_cast<T*>(pb.get()))
			{
				return pt;
			}
		}
		return nullptr;
	}
private:
	std::vector<std::unique_ptr<Bindable>> binds;
	IndexBuffer* pIndexBuffer = nullptr;

};