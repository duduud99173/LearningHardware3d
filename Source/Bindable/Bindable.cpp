#include "Bindable.h"

ID3D11DeviceContext* Bindable::GetContext(Graph& gfx)
{
    return gfx.pContext.Get();
}

ID3D11Device* Bindable::GetDevice(Graph& gfx)
{
    return gfx.pDevice.Get();
}

