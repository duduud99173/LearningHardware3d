#include "Drawable.h"

void Drawable::BindAndDraw( Graph& gfx )
{
	for (auto& b : binds)
	{
		b->Bind(gfx);
	}
	for (auto& b : GetStaticBinds())
	{
		b->Bind(gfx);
	}

	if (pIndexBuffer->Count() == 0)
	{
		gfx.Draw(4u);
	}
	else
	{
		gfx.DrawIndexed(pIndexBuffer->Count());
	}

}

void Drawable::AddBind(std::unique_ptr<Bindable> bind)
{
	binds.push_back(std::move(bind));
}

void Drawable::AddIndexBuffer(std::unique_ptr<IndexBuffer> ibuf)
{
	pIndexBuffer = ibuf.get();
	binds.push_back(std::move(ibuf));
}


