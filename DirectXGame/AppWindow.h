#pragma once
#include "Window.h"
#include "GraphicsEngine.h"
#include "SwapChain.h"
#include "DeviceContext.h"
#include "VertexBuffer.h"
#include "VertexShader.h"
#include "PixelShader.h"
#include "ConstantBuffer.h"
#include "Quad.h"
#include "EngineTime.h"


class AppWindow :public Window
{
public:
	AppWindow();
	~AppWindow();

	// Inherited via Window
	virtual void onCreate() override;
	virtual void onUpdate() override;
	virtual void onDestroy() override;
private:
	SwapChain* m_swap_chain;
	//VertexBuffer* m_vb;
	VertexBuffer* m_vb_rect;
	VertexBuffer* m_vb_rect2;
	VertexShader* m_vs;
	PixelShader* m_ps;
	ConstantBuffer* m_cb;
	Quad* quad1;
	Quad* quad2;
	Quad* quad3;

private:
	unsigned long m_old_time = 0;
	float m_delta_time = 0;
	float m_speed = 1;
	/*float max_speed = 20;*/
	float time = 0;
	bool reset = true;
};

