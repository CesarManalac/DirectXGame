#include "AppWindow.h"
#include <stdlib.h>
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
	
	for (int i = 0; i < 100; i++) {
		float min = -0.75f;
		float max = 0.75f;
		float minSpeed = -3.75;
		float maxSpeed = 2;
		float speed = ((((float)rand() / (float)RAND_MAX) * (maxSpeed - minSpeed)) + minSpeed);
		float x = ((((float)rand() / (float)RAND_MAX) * (max - min)) + min);
		float y = ((((float)rand() / (float)RAND_MAX) * (max - min))+min);
		Cube* cubeObj = new Cube("Cube");
		cubeObj->setSpeed(speed);
		cubeObj->setPosition(Vector3D(x, y, 0.0f));
		cubeObj->setScale(Vector3D(0.25, 0.25, .25));
		this->cubeList.push_back(cubeObj);
	}
}

void AppWindow::onUpdate()
{
	Window::onUpdate();
	GraphicsEngine::get()->getImmediateDeviceContext()->clearRenderTargetColor(this->m_swap_chain,
		0, 0.3f, 0.4f, 1);
	RECT rc = this->getClientWindowRect();
	int width = rc.right - rc.left;
	int height = rc.bottom - rc.top;
	//Set default shader in the graphics pipelinee to be able to draw
	GraphicsEngine::get()->getImmediateDeviceContext()->setViewportSize(width, height);

	//quad1->update(EngineTime::getDeltaTime());
	//quad1->draw(width, height);
	for (int i = 0; i < cubeList.size(); i++) {
		cubeList[i]->update(EngineTime::getDeltaTime());
		cubeList[i]->draw(width, height);
	}
	m_swap_chain->present(true);
}

void AppWindow::onDestroy()
{
	Window::onDestroy();
	m_swap_chain->release();
	GraphicsEngine::get()->release();
}

void AppWindow::onMouseClick(POINT new_pos)
{
	//RECT rc = this->getClientWindowRect();
	//float width, height;
	//width = rc.right - rc.left;
	//height = rc.bottom - rc.top;
	//width /= 2;
	//height /= 2;

	//if (new_pos.x >= 502) {
	//	new_pos.x *= 1;
	//}
	//else {
	//	new_pos.x *= -1;
	//}
	//if (new_pos.y >= 362.5) {
	//	new_pos.y *= -1;
	//}
	//else {
	//	new_pos.y *= 1;
	//}
	//float x, y;
	//x = new_pos.x / width;
	//y = new_pos.y / height;
	//float x_decimal, y_decimal;
	//x = std::modf(x, &x_decimal);
	//y = std::modf(y, &y_decimal);
	//std::cout << x << " " << y << "\n";
	//quad1 = new Quad(Vector3(x, y,0), rc);

	std::cout << "click\n";
}
