#include "AppWindow.h"
#include <Windows.h>



AppWindow::AppWindow()
{
}

AppWindow::~AppWindow()
{
}

void AppWindow::onCreate()
{
	Window::onCreate();
	EngineTime::initialize();
	GraphicsEngine::get()->init();
	m_swap_chain = GraphicsEngine::get()->createSwapChain();
	RECT rc = this->getClientWindowRect();
	m_swap_chain->init(this->m_hwnd, rc.right - rc.left, rc.bottom - rc.top);
}

void AppWindow::onUpdate()
{
	Window::onUpdate();
	GraphicsEngine::get()->getImmediateDeviceContext()->clearRenderTargetColor(this->m_swap_chain,
		0, 0.3f, 0.4f, 1);
	RECT rc = this->getClientWindowRect();
	//Set default shader in the graphics pipelinee to be able to draw
	GraphicsEngine::get()->getImmediateDeviceContext()->setViewportSize(rc.right - rc.left, rc.bottom - rc.top);

	if (quadList.size() != 0) {
		for (int i = 0; i < quadList.size(); i++) {
			//also the draw function
			quadList[i]->Update();
		}
	}

	//quad1->Update();
	
	m_swap_chain->present(true);
}

void AppWindow::onDestroy()
{
	Window::onDestroy();
	quad1->Release();
	m_swap_chain->release();
	GraphicsEngine::get()->release();
}

void AppWindow::onMouseClick(POINT new_pos)
{
	RECT rc = this->getClientWindowRect();
	float width, height;
	width = rc.right - rc.left;
	height = rc.bottom - rc.top;
	width /= 2;
	height /= 2;
	if (new_pos.x >= width) {
		new_pos.x *= 1;
	}
	if (new_pos.y >= height) {
		new_pos.y *= -1;
	}
	//FIX ACCURACY PROBS COMPUTATIONS
	float x = 0, y = 0;
	x = ((new_pos.x / width) + x) / 2;
	y = ((new_pos.y / height) + y) / 2;
	float x_int, y_int;
	x = std::modf(x, &x_int);
	y = std::modf(y, &y_int);
	std::cout << x << " " << y << "\n";
	std::cout << new_pos.x << " " << new_pos.y << "\n";
	//std::cout << width << "\n";
	//1004, 725
	quad1 = new Quad(Vector3(x, y, 0), rc);
	quadList.push_back(quad1);
}
