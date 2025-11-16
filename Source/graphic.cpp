#include "graphic.h"
#include <sstream>
#include "imgui_impl_dx11.h"
#include "imgui_impl_win32.h"
#include "dxgidebug.h"


Graph::Graph(HWND hWnd)
{
	DXGI_SWAP_CHAIN_DESC sd = {};
	sd.BufferCount = 1;
	sd.BufferDesc.Width = 0;
	sd.BufferDesc.Height = 0;
	sd.BufferDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
	sd.BufferDesc.RefreshRate.Denominator = 0;
	sd.BufferDesc.RefreshRate.Numerator = 0;
	sd.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	sd.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	sd.Windowed = TRUE;
	sd.SampleDesc.Count = 1;
	sd.SampleDesc.Quality = 0;
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	sd.Flags = 0;
	sd.OutputWindow = hWnd;
	sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

	GFX_THROW(D3D11CreateDeviceAndSwapChain(nullptr,
		D3D_DRIVER_TYPE_HARDWARE, 
		NULL, 
		D3D11_CREATE_DEVICE_DEBUG, 
		nullptr, 0, D3D11_SDK_VERSION, 
		&sd, 
		pSwap.GetAddressOf(), 
		pDevice.GetAddressOf(), 
		nullptr, 
		pContext.GetAddressOf()
	));

	D3D11_VIEWPORT vp = {};
	vp.TopLeftX = 0;
	vp.TopLeftY = 0;
	vp.Width = 800;
	vp.Height = 600;
	vp.MaxDepth = 1.0;
	vp.MinDepth = 0.0;
	pContext->RSSetViewports(1, &vp);


	RECT rect;
	GetClientRect(hWnd, &rect);
	int width = rect.right - rect.left;
	int height = rect.bottom - rect.top;
	Microsoft::WRL::ComPtr<ID3D11Texture2D> pbackbuffer;
	GFX_THROW(pSwap->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)pbackbuffer.GetAddressOf()));
	GFX_THROW(pDevice->CreateRenderTargetView(pbackbuffer.Get(), nullptr, pRenderTargetView.GetAddressOf()));

	Microsoft::WRL::ComPtr<ID3D11Texture2D> pdepthstencil;
	D3D11_TEXTURE2D_DESC desc = {};
	desc.Format = DXGI_FORMAT_D32_FLOAT;
	desc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	desc.ArraySize = 1;
	desc.CPUAccessFlags = 0;
	desc.Height = height;
	desc.Width = width;
	desc.MipLevels = 1;
	desc.MiscFlags = 0;
	desc.Usage = D3D11_USAGE_DEFAULT;
	desc.SampleDesc.Count = 1;
	desc.SampleDesc.Quality = 0;
	GFX_THROW(pDevice->CreateTexture2D(&desc, 0, &pdepthstencil));
	D3D11_DEPTH_STENCIL_VIEW_DESC dsvDesc = {};
	dsvDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	dsvDesc.Format = DXGI_FORMAT_D32_FLOAT;
	dsvDesc.Texture2D.MipSlice = 0u;
	GFX_THROW(pDevice->CreateDepthStencilView(pdepthstencil.Get(), &dsvDesc, pDepthStencilView.GetAddressOf()));

	D3D11_DEPTH_STENCIL_DESC dsDesc = {};
	dsDesc.DepthEnable = true;
	dsDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	dsDesc.DepthFunc = D3D11_COMPARISON_LESS;
	Microsoft::WRL::ComPtr<ID3D11DepthStencilState> pDSstate;
	GFX_THROW(pDevice->CreateDepthStencilState(&dsDesc, pDSstate.GetAddressOf()));
	pContext->OMSetDepthStencilState(pDSstate.Get(), 1u);

	
	pContext->OMSetRenderTargets(1, pRenderTargetView.GetAddressOf(), pDepthStencilView.Get());

	ImGui_ImplDX11_Init(pDevice.Get(), pContext.Get());
}

Graph::~Graph()
{
	ImGui_ImplDX11_Shutdown();
	
	/*
	Microsoft::WRL::ComPtr<ID3D11Debug> debugDevice;
	if (SUCCEEDED(pDevice.As(&debugDevice)))
	{
		debugDevice->ReportLiveDeviceObjects(D3D11_RLDO_DETAIL);
	}
	*/


	// 解绑所有绑定的资源
	/*
	pContext->PSSetShaderResources(0, 0, nullptr);
	ID3D11Buffer* nullBuffer = nullptr;
	pContext->IASetVertexBuffers(0, 0, &nullBuffer, nullptr, nullptr);
	pContext->IASetIndexBuffer(nullptr, DXGI_FORMAT_UNKNOWN, 0);
	pContext->VSSetConstantBuffers(0, 0, &nullBuffer);
	pContext->PSSetConstantBuffers(0, 0, &nullBuffer);
	ID3D11ShaderResourceView* nullSRV[1] = { nullptr };
	pContext->PSSetShaderResources(0, 1, nullSRV);
	pContext->VSSetShader(nullptr, nullptr, 0);
	pContext->PSSetShader(nullptr, nullptr, 0);
	pContext->IASetInputLayout(nullptr);
	ID3D11SamplerState* nullSampler[1] = { nullptr };
	pContext->PSSetSamplers(0, 1, nullSampler);
	// 刷新管线状态(立刻提交命令)
	pContext->Flush();
	*/
}

void Graph::Draw(UINT nVertex)
{
	pContext->Draw(nVertex, 0u);
}

void Graph::DrawIndexed(UINT nIndex)
{
	pContext->DrawIndexed(nIndex, 0, 0);
}
void Graph::Present()
{
	GFX_THROW(pSwap->Present(1u, 0u));
}
void Graph::ClearBuffer(float r, float g,float b)
{
	const float color[4] = { r, g , b, 1.0f };
	pContext->ClearRenderTargetView(pRenderTargetView.Get(), color);
	pContext->ClearDepthStencilView(pDepthStencilView.Get(), D3D11_CLEAR_DEPTH, 1u, 0u);
}
DirectX::XMMATRIX Graph::GetProjMatrix()
{
	return projMatrix;
}

void Graph::SetProjMatrix(float FovAngleY, float AspectRatio, float Nearz, float Farz)
{
	projMatrix = DirectX::XMMatrixPerspectiveFovLH(FovAngleY, AspectRatio, Nearz, Farz);
}

void Graph::BeginFrame(float r, float g, float b)
{

	if (IsImguiEnabled())
	{
		ImGui_ImplWin32_NewFrame();
		ImGui_ImplDX11_NewFrame();
		ImGui::NewFrame();
	}
	

	const float color[4] = { r, g , b, 1.0f };
	pContext->ClearRenderTargetView(pRenderTargetView.Get(), color);
	pContext->ClearDepthStencilView(pDepthStencilView.Get(), D3D11_CLEAR_DEPTH, 1u, 0u);
}

void Graph::EndFrame()
{
	if (IsImguiEnabled())
	{
		ImGui::Render();
		ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
	}
	Present();
}

void Graph::EnableImgui()
{
	imguiEnabled = true;
}

void Graph::DisableImgui()
{
	imguiEnabled = false;
}

bool Graph::IsImguiEnabled()
{
	return imguiEnabled;
}

void Graph::SetCameraMatrix(DirectX::FXMMATRIX cam)
{
	cameraMatrix = cam;
}

DirectX::XMMATRIX Graph::GetCameraMatrix()
{
	return cameraMatrix;
}

const char* Graph::HrException::what()
{
	std::ostringstream oss;
	oss << "HRESULT failed with code " << std::hex << hr << " at " << file << ":" << line;
	return oss.str().c_str();
}
