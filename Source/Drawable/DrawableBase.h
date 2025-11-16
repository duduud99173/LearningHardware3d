#pragma once
#include "Drawable.h"

template<typename T>
class DrawableBase : public Drawable
{
protected:
	void AddStaticBind(std::unique_ptr<Bindable> bind);
	void AddStaticIndexBuffer(std::unique_ptr<IndexBuffer> ibuf);
	void SetIndexPointer();
	std::vector<std::unique_ptr<Bindable>>& GetStaticBinds();
	bool IsStaticInitialized();
	
	template<typename B>
	static B* QueryStaticBindable()
	{
		for (auto& pb : staticBinds)
		{
			if (auto pt = dynamic_cast<B*>(pb.get()))
			{
				return pt;
			}
		}
		return nullptr;
	}

private:
	static std::vector<std::unique_ptr<Bindable>> staticBinds;
};

template<typename T>
std::vector<std::unique_ptr<Bindable>> DrawableBase<T>::staticBinds;

template<typename T>
void DrawableBase<T>::AddStaticBind(std::unique_ptr<Bindable> bind)
{
	staticBinds.push_back(std::move(bind));
}

template<typename T>
void DrawableBase<T>::AddStaticIndexBuffer(std::unique_ptr<IndexBuffer> ibuf)
{
	pIndexBuffer = ibuf.get();
	staticBinds.push_back(std::move(ibuf));
}

template<typename T>
void DrawableBase<T>::SetIndexPointer()
{
	for (auto& b : staticBinds)
	{
		if (auto p = dynamic_cast<IndexBuffer*>(b.get()))
		{
			pIndexBuffer = p;
		}
	}
}

template<typename T>
std::vector<std::unique_ptr<Bindable>>& DrawableBase<T>::GetStaticBinds()
{
	return staticBinds;
}

template<typename T>
bool DrawableBase<T>::IsStaticInitialized()
{
	return !staticBinds.empty();
}
