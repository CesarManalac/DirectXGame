#include "AppWindow.h"
#include "InputSystem.h"
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
	InputSystem::get()->addListener(this);
	GraphicsEngine::get()->init();
	m_swap_chain = GraphicsEngine::get()->createSwapChain();
	//InputSystem::get()->showCursor(false);
	RECT rc = this->getClientWindowRect();
	m_swap_chain->init(this->m_hwnd, rc.right - rc.left, rc.bottom - rc.top);
	
	camera = new Camera("Camera");
	mngr->initialize(this->m_hwnd);

	//Cube* cubeObj = new Cube("Cube");
	//cubeObj->setPosition(Vector3D(0, 0, 0));
	//cubeObj->setScale(Vector3D(1, 1, 1));
	//gameObj.push_back(cubeObj);

	//Plane* planeObj = new Plane("Plane");
	//planeObj->setPosition(Vector3D(0, 0, 0.0f));
	//planeObj->setScale(Vector3D(5, 0, 5));
	//gameObj.push_back(planeObj);
}



void AppWindow::onUpdate()
{
	Window::onUpdate();
	InputSystem::get()->update();
	GraphicsEngine::get()->getImmediateDeviceContext()->clearRenderTargetColor(this->m_swap_chain,
		0, 0.3f, 0.4f, 1);
	RECT rc = this->getClientWindowRect();
	int width = rc.right - rc.left;
	int height = rc.bottom - rc.top;
	//Set default shader in the graphics pipelinee to be able to draw
	GraphicsEngine::get()->getImmediateDeviceContext()->setViewportSize(width, height);

	camera->update(EngineTime::getDeltaTime());
	if (!gameObj.empty()) {
		for (int i = 0; i < gameObj.size(); i++) {
			gameObj[i]->setView(camera->GetCamera());
			gameObj[i]->update(EngineTime::getDeltaTime());
			gameObj[i]->draw(width, height);
		}
	}

	mngr->getInstance()->drawAllUI();

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
	std::cout << "click\n";
}
/*
	To replace with camera
*/
void AppWindow::onKeyDown(int key)
{
	if (key == 'W') {
		camera->SetForwardValue(1.0f);
	}
	else if (key == 'S') {
		camera->SetForwardValue(-1.0f);
	}
	else if (key == 'A') {
		camera->setRightValue(-1.0f);
	}
	else if (key == 'D') {
		camera->setRightValue(1.0f);
	}
}

void AppWindow::onKeyUp(int key)
{
	camera->SetForwardValue(0.0f);
	camera->setRightValue(0.0f);
}

void AppWindow::onMouseMove(const Point& delta_mouse)
{



}

void AppWindow::onLeftMouseDown(const Point& mouse_pos)
{
	//gameObj[0]->setScale(Vector3D(0.5, 0.5, 0.5));
	RECT rc = this->getClientWindowRect();
	int width = rc.right - rc.left;
	int height = rc.bottom - rc.top;

	rotX += (mouse_pos.m_y - (height / 2.0f)) * EngineTime::getDeltaTime() * 0.1f;
	rotY += (mouse_pos.m_x - (width / 2.0f)) * EngineTime::getDeltaTime() * 0.1f;

	//InputSystem::get()->setCursorPosition(Point((int)(width / 2.0f), (int)(height / 2.0f)));

	camera->setRotation(Vector3D(rotX, rotY, 0));
}

void AppWindow::onLeftMouseUp(const Point& mouse_pos)
{
	//gameObj[0]->setScale(Vector3D(1, 1, 1));
}

void AppWindow::onRightMouseDown(const Point& mouse_pos)
{
	//gameObj[0]->setScale(Vector3D(2, 2, 2));
}

void AppWindow::onRightMouseUp(const Point& mouse_pos)
{
	//gameObj[0]->setScale(Vector3D(1, 1, 1));
}

void AppWindow::onFocus()
{
	InputSystem::get()->addListener(this);
}

void AppWindow::onKillFocus()
{
	InputSystem::get()->removeListener(this);
}
