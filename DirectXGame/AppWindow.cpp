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
	
	camera = new Camera("Camera");
	//FOR 50 CUBES
	//for (int i = 0; i < 50; i++) {
	//	float min = -0.75f;
	//	float max = 0.75f;
	//	float x = ((((float)rand() / (float)RAND_MAX) * (max - min)) + min);
	//	float y = ((((float)rand() / (float)RAND_MAX) * (max - min)) + min);
	//	Cube* cubeObj = new Cube("Cube");
	//	cubeObj->setPosition(Vector3D(x, y, 0.0f));
	//	cubeObj->setScale(Vector3D(.25, .25, .25));
	//	gameObj.push_back(cubeObj);
	//}

	/*FOR ITEM 7*/
	//float negativeRot = -.2;
	//float positiveRot = .2;
	//for (int i = 0; i < 12; i++) {
	//	Cube* cubeObj = new Cube("Cube");
	//	cubeObj->setPosition(Vector3D(1, 1, 1));
	//	cubeObj->setScale(Vector3D(0, 2, 1));
	//	//alternates the rotation value per number
	//	if(i%2 == 0)
	//		cubeObj->setRotation(Vector3D(0, 0, negativeRot));
	//	else
	//		cubeObj->setRotation(Vector3D(0, 0, positiveRot));
	//	gameObj.push_back(cubeObj);
	//}
	//for (int i = 0; i < 3; i++) {
	//	Plane* planeObj = new Plane("Plane");
	//	planeObj->setPosition(Vector3D(.2, 1, 0.0f));
	//	planeObj->setScale(Vector3D(1.5, 0, 1));
	//	planeList.push_back(planeObj);
	//}


	for (int i = 0; i < 3; i++) {
		Cube* cubeObj = new Cube("Cube");
		cubeObj->setPosition(Vector3D(0, 0, 0));
		cubeObj->setScale(Vector3D(1, 1, 1));
		gameObj.push_back(cubeObj);
	}

	Plane* planeObj = new Plane("Plane");
	planeObj->setPosition(Vector3D(0, 0, 0.0f));
	planeObj->setScale(Vector3D(10, 0, 10));
	gameObj.push_back(planeObj);
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

	/*Item 7*/
	//Setting the positions of the diagonal cards
	//gameObj[0]->setPosition(Vector3D(0.0f, 0.0f, 0.0f));
	//gameObj[1]->setPosition(Vector3D(0.4f, 0.0f, 0.0f));
	//gameObj[2]->setPosition(Vector3D(0.8f, 0.0f, 0.0f));
	//gameObj[3]->setPosition(Vector3D(1.2, 0.0f, 0.0f));
	//gameObj[4]->setPosition(Vector3D(1.6f, 0.0f, 0.0f));
	//gameObj[5]->setPosition(Vector3D(2, 0.0f, 0.0f));
	//gameObj[6]->setPosition(Vector3D(0.4f, 2, 0.0f));
	//gameObj[7]->setPosition(Vector3D(0.8f, 2, 0.0f));
	//gameObj[8]->setPosition(Vector3D(1.2f, 2, 0.0f));
	//gameObj[9]->setPosition(Vector3D(1.6f, 2, 0.0f));
	//gameObj[10]->setPosition(Vector3D(0.8f, 4, 0.0f));
	//gameObj[11]->setPosition(Vector3D(1.2, 4, 0.0f));
	//Setting the positions of the plane
	//planeList[0]->setPosition(Vector3D(.2, 1, 0.0f));
	//planeList[1]->setPosition(Vector3D(1.6, 1, 0.0f));
	//planeList[2]->setPosition(Vector3D(1, 3, 0.0f));
	gameObj[0]->setPosition(Vector3D(0.0, 0.9, 0.0));
	gameObj[1]->setPosition(Vector3D(-1.5, 2.0, 0.0));
	gameObj[2]->setPosition(Vector3D(-1.5, 3.0, -2.0));
	for (int i = 0; i < gameObj.size(); i++) {
		gameObj[i]->setView(camera->GetCamera());
		gameObj[i]->update(EngineTime::getDeltaTime());
		gameObj[i]->draw(width, height);
	}
	//for (int i = 0; i < planeList.size(); i++) {
	//	planeList[i]->setView(camera->GetCamera());
	//	planeList[i]->update(EngineTime::getDeltaTime());
	//	planeList[i]->draw(width, height);
	//}
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
	RECT rc = this->getClientWindowRect();
	int width = rc.right - rc.left;
	int height = rc.bottom - rc.top;

	rotX += (delta_mouse.m_y - (height / 2.0f)) * EngineTime::getDeltaTime() * 0.1f;
	rotY += (delta_mouse.m_x - (width / 2.0f)) * EngineTime::getDeltaTime() * 0.1f;

	InputSystem::get()->setCursorPosition(Point((int)(width / 2.0f), (int)(height / 2.0f)));
	
	camera->setRotation(Vector3D(rotX, rotY, 0));
}

void AppWindow::onLeftMouseDown(const Point& mouse_pos)
{
	//gameObj[0]->setScale(Vector3D(0.5, 0.5, 0.5));
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
