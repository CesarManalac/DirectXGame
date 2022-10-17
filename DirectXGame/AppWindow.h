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
#include "Vector3D.h"
#include "Matrix4x4.h"
#include "AGameObject.h"
#include "Cube.h"
#include "Plane.h"
#include <conio.h>
#include <vector>

class AppWindow :public Window
{
public:
	AppWindow();
	~AppWindow();

	// Inherited via Window
	virtual void onCreate() override;
	virtual void onUpdate() override;
	virtual void onDestroy() override;
	virtual void onMouseClick(POINT) override;
private:
	SwapChain* m_swap_chain;
	//Quad* quad1;
	//std::vector <Cube*> cubeList;

	std::vector<AGameObject*> gameObj;

private:
	POINT old_mouse = {};
};

