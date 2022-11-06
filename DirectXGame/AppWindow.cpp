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
	InputSystem::get()->showCursor(false);
	RECT rc = this->getClientWindowRect();
	m_swap_chain->init(this->m_hwnd, rc.right - rc.left, rc.bottom - rc.top);
	
	camera = new Camera();

	//for (int i = 0; i < 10; i++) {
	//	float min = -2;
	//	float max = 2;
	//	float x = ((((float)rand() / (float)RAND_MAX) * (max - min)) + min);
	//	float y = ((((float)rand() / (float)RAND_MAX) * (max - min)) + min);
	//	std::cout << x << "\n";
	//	Cube* cubeObj = new Cube("Cube");
	//	cubeObj->setPosition(Vector3D(x, y, 0.0f));
	//	cubeObj->setScale(Vector3D(0.25, 0.25, .25));
	//	gameObj.push_back(cubeObj);
	//}

	Cube* cubeObj = new Cube("Cube");
	cubeObj->setPosition(Vector3D(0.0f, 0.0f, 0.0f));
	cubeObj->setScale(Vector3D(1, 1, 1));
	gameObj.push_back(cubeObj);

	Plane* planeObj = new Plane("Plane");
	planeObj->setScale(Vector3D(4, .05, 4));
	planeObj->setRotation(Vector3D(0, 0, 0));
	gameObj.push_back(planeObj);
	
	Cube* cameraRep = new Cube("CameraRep");
	cubeObj->setPosition(Vector3D(0.0f, 0.0f, 0.0f));
	cubeObj->setScale(Vector3D(1, 1, 1));
	gameObj.push_back(cameraRep);
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

	camera->Update();
	for (int i = 0; i < gameObj.size(); i++) {
		if(gameObj[i]->getName() != "CameraRep")
		{
			gameObj[i]->setView(camera->GetCamera());
			gameObj[i]->update(EngineTime::getDeltaTime());
			gameObj[i]->draw(width, height);
		}
		else if(gameObj[i]->getName() == "CameraRep")
		{
			if(isCamera == false)
			{
				gameObj[i]->setView(camera->GetCamera());
				gameObj[i]->update(EngineTime::getDeltaTime());
				gameObj[i]->draw(width, height);
			}
		}
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
	else if(key == 'C')
	{
		if(isCamera == true)
		{
			isCamera = false;

		}
	}
}

void AppWindow::onKeyUp(int key)
{
	camera->SetForwardValue(0.0f);
	camera->setRightValue(0.0f);
}

void AppWindow::onMouseMove(const Point& delta_mouse)
{
	RECT rc = this->getClientWindowRect();
	int width = rc.right - rc.left;
	int height = rc.bottom - rc.top;

	rotX += (delta_mouse.m_y - (height / 2.0f)) * EngineTime::getDeltaTime() * 0.1f;
	rotY += (delta_mouse.m_x - (width / 2.0f)) * EngineTime::getDeltaTime() * 0.1f;

	InputSystem::get()->setCursorPosition(Point((int)(width / 2.0f), (int)(height / 2.0f)));
	
	camera->SetRotationValue(Vector3D(rotX, rotY, 0));
}

void AppWindow::onLeftMouseDown(const Point& mouse_pos)
{
	gameObj[0]->setScale(Vector3D(0.5, 0.5, 0.5));
}

void AppWindow::onLeftMouseUp(const Point& mouse_pos)
{
	gameObj[0]->setScale(Vector3D(1, 1, 1));
}

void AppWindow::onRightMouseDown(const Point& mouse_pos)
{
	gameObj[0]->setScale(Vector3D(2, 2, 2));
}

void AppWindow::onRightMouseUp(const Point& mouse_pos)
{
	gameObj[0]->setScale(Vector3D(1, 1, 1));
}

void AppWindow::onFocus()
{
	InputSystem::get()->addListener(this);
}

void AppWindow::onKillFocus()
{
	InputSystem::get()->removeListener(this);
}
