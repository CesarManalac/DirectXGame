#include "Window.h"

Window* window = nullptr;

Window::Window()
{
}
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam) 
{
	switch (msg) {
	case WM_CREATE: {
		//Event fired when the window will be created
		Window* window = (Window*)((LPCREATESTRUCT)lparam)->lpCreateParams;
		//THIS SNIPPET OF CODE WILL GET THE "THIS" POINTER PASSED IN CREATEWINDOWEX

		SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR)window);
		//THIS SNIPPET OF CODE, INSTEAD, WILL SAVE THE POINTER "THIS" IN A SPECIAL STRUCTURE DATA IDENTIFIED BY HWND
		window->setHWND(hwnd);
		window->onCreate();
		break;
	}
	case WM_DESTROY: {
		//Event fired when destroying a window 
		Window* window = (Window*)GetWindowLongPtr(hwnd, GWLP_USERDATA);
		//THIS SNIPPET OF CODE WILL RECOVER THE POINTER "THIS" FROM THE SPECIAL STRUCTURE DATA IDENTIFIED BY HWND
		window->onDestroy();
		::PostQuitMessage(0);
		break;
	}
	default:
		return ::DefWindowProc(hwnd, msg, wparam, lparam);
	}

	return NULL;
}
bool Window::init()
{
	WNDCLASSEX wc;
	wc.cbClsExtra = NULL;
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.cbWndExtra = NULL;
	wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	wc.hInstance = NULL;
	wc.lpszClassName = L"MyWindowClass";
	wc.lpszMenuName = L"";
	wc.style = NULL;
	wc.lpfnWndProc = &WndProc;

	if (!::RegisterClassEx(&wc)) {
		return false;
	}
	// creates the window
	m_hwnd = ::CreateWindowEx(WS_EX_OVERLAPPEDWINDOW, L"MyWindowClass", L"DirectXApplication", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 1024, 768,
		NULL, NULL, NULL, this);

	//if creation fails, return false
	if (!m_hwnd)
		return false;

	//show the window
	::ShowWindow(m_hwnd, SW_SHOW);
	::UpdateWindow(m_hwnd);
	m_is_run = true;
	return true;
}

bool Window::broadcast()
{
	MSG msg;
	
	this->onUpdate();
	
	while (::PeekMessage(&msg, NULL, 0,0, PM_REMOVE)>0) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	

	Sleep(1);

	return true;
}

bool Window::release()
{
	if (!::DestroyWindow(m_hwnd)) {
		return false;
	}
	return true;
}

bool Window::isRun()
{
	return m_is_run;
}

RECT Window::getClientWindowRect()
{
	RECT rc;
	::GetClientRect(this->m_hwnd, &rc);

	return rc;
}

void Window::setHWND(HWND hwnd)
{
	this->m_hwnd = hwnd;
}

void Window::onCreate()
{
}

void Window::onUpdate()
{
}

void Window::onDestroy()
{
	m_is_run = false;
}

Window::~Window()
{
}
