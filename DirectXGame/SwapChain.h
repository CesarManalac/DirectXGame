#pragma once
#include <d3d11.h>

#include "Prerequisites.h"
class SwapChain
{
public:
	SwapChain(RenderSystem* m_system);
	bool init(HWND hwnd, UINT width, UINT height);
	bool present(bool vsync);
	bool release();
	ID3D11RenderTargetView* getRenderTargetView();
	ID3D11DepthStencilView* getDepthStencilView();
	~SwapChain();
private:
	RenderSystem* m_system = nullptr;
	IDXGISwapChain* m_swap_chain;
	ID3D11RenderTargetView* m_rtv;
	ID3D11DepthStencilView* m_dsv;
private:
	friend class DeviceContext;
};

