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
#include "InputListener.h"
#include <conio.h>
#include <vector>

class AppWindow :public Window, public InputListener
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
	float rotX = 0;
	float rotY = 0;
	int m_scale_cube = 1;

private:
	POINT old_mouse = {};

	// Inherited via InputListener
	virtual void onKeyDown(int key) override;
	virtual void onKeyUp(int key) override;

	// Inherited via InputListener
	virtual void onMouseMove(const Point& delta_mouse) override;

	// Inherited via InputListener
	virtual void onLeftMouseDown(const Point& mouse_pos) override;
	virtual void onLeftMouseUp(const Point& mouse_pos) override;
	virtual void onRightMouseDown(const Point& mouse_pos) override;
	virtual void onRightMouseUp(const Point& mouse_pos) override;
	virtual void onFocus()override;
	virtual void onKillFocus()override;
};

