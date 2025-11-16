#pragma once
#include <wrl.h>
#include "window.h"
#include <DirectXMath.h>
#include <d3d11.h>
#include <exception>
#include "GraphMicro.h"
#include "Camera.h"
#pragma comment(lib,"d3d11.lib")


class Graph
{
	friend class Bindable;
public:
	class HrException : std::exception
	{
	public:
		HrException(int line, const char* file, HRESULT hr) : line(line), file(file), hr(hr) {};
		const char* what();
		int line;
		const char* file;
		HRESULT hr;
	};
	Graph(HWND hWnd);
	~Graph();
	void Draw(UINT nVertex);
	void DrawIndexed( UINT nIndex );
	void Present();
	void ClearBuffer(float r, float g, float b);
	DirectX::XMMATRIX GetProjMatrix();
	void SetProjMatrix(float FovAngleY, float AspectRatio, float Nearz, float Farz);
	void BeginFrame(float r, float g, float b);
	void EndFrame();
	void EnableImgui();
	void DisableImgui();
	bool IsImguiEnabled();
	void SetCameraMatrix(DirectX::FXMMATRIX cam);
	DirectX::XMMATRIX GetCameraMatrix();
private:
	bool imguiEnabled = true;
	Microsoft::WRL::ComPtr<ID3D11DeviceContext> pContext;
	Microsoft::WRL::ComPtr<ID3D11Device> pDevice;
	Microsoft::WRL::ComPtr<IDXGISwapChain> pSwap;
	Microsoft::WRL::ComPtr<ID3D11RenderTargetView> pRenderTargetView;
	Microsoft::WRL::ComPtr<ID3D11DepthStencilView> pDepthStencilView;
	DirectX::XMMATRIX projMatrix = DirectX::XMMatrixPerspectiveFovLH(1.0f, 4.0f/3.0f ,0.1f, 50.0f);
	DirectX::XMMATRIX cameraMatrix;
};