#include "AppWindow.h"
#include <Windows.h>

//struct vec3
//{
//	float x, y, z;
//};
//
//struct vertex
//{
//	vec3 position;
//	vec3 position1;
//	vec3 color;
//	vec3 color1;
//};

__declspec(align(16))
struct constant 
{
	float m_angle;
};

AppWindow::AppWindow()
{
}

AppWindow::~AppWindow()
{
}

void AppWindow::onCreate()
{
	Window::onCreate();
	GraphicsEngine::get()->init();
	m_swap_chain = GraphicsEngine::get()->createSwapChain();
	RECT rc = this->getClientWindowRect();
	m_swap_chain->init(this->m_hwnd, rc.right - rc.left, rc.bottom - rc.top);

	//vertex list[] =
	//{
	//	/*{-0.25f, -0.25f, 0.0f, 1,0,0},
	//	{ 0.0f, 0.25f, 0.0f, 0,1,0},
	//	{ 0.25f, -0.25f, 0.0f, 0,0,1}*/
	//	/*{-0.5f,-0.5f, 0.0f,	-0.32f,-0.11f,0.0f,	0,0,0,	0,1,0},
	//	{-0.5f, 0.5f, 0.0f,	-0.11f, 0.78f,0.0f,	1,1,0,	0,1,1},
	//	{ 0.5f,-0.5f, 0.0f,	 0.75f,-0.73f,0.0f,	0,0,1,	1,0,0},
	//	{ 0.5f, 0.5f, 0.0f,	 0.88f, 0.77f,0.0f,	1,1,1,	0,0,1}*/
	//	{-0.5f,-0.5f, 0.0f,	-0.5f,-0.5f, 0.0f,	0,0,0,	0,1,0},
	//	{-0.5f, 0.5f, 0.0f,	-0.5f, 0.5f, 0.0f,	1,1,0,	0,1,1},
	//	{ 0.5f,-0.5f, 0.0f,	 0.5f,-0.5f, 0.0f,	0,0,1,	1,0,0},
	//	{ 0.5f, 0.5f, 0.0f,	 0.5f, 0.5f, 0.0f,	1,1,1,	0,0,1}
	//};
	//vertex rect_list[] =
	//{
	//	/*{0.45f, -0.25f, 0.0f,		0,1,0},
	//	{0.45f, 0.25f, 0.0f,		0,1,0},
	//	{0.90f, -0.25f, 0.0f,		0,1,0},
	//	{0.90f, 0.25f, 0.0f,		0,1,0}*/

	//	{-0.5f,-0.5f, 0.0f,		-0.32f,-0.11f,0.0f,		0,1,0},
	//	{-0.5f, 0.5f, 0.0f,		-0.11f, 0.78f,0.0f,		0,1,0},
	//	{ 0.5f,-0.5f, 0.0f,		 0.75f,-0.73f,0.0f,		0,1,0},
	//	{ 0.5f, 0.5f, 0.0f,		 0.88f, 0.77f,0.0f,		0,1,0}
	//};
	//vertex rect_list2[] =
	//{
	//	{-0.90f, -0.25f, 0.0f, 1,0,0},
	//	{ -0.90f, 0.25f, 0.0f, 0,1,0},
	//	{ -.45f, -0.25f, 0.0f, 0,1,0},
	//	{ -.45f, 0.25f, 0.0f, 0,0,1}
	//};
	m_vb = GraphicsEngine::get()->createVertexBuffer();
	//m_vb_rect = GraphicsEngine::get()->createVertexBuffer();
	//m_vb_rect2 = GraphicsEngine::get()->createVertexBuffer();
	//UINT size_list = ARRAYSIZE(list);
	//UINT size_list_rect = ARRAYSIZE(rect_list);
	//UINT size_list_rect2 = ARRAYSIZE(rect_list2);

	void* shader_byte_code = nullptr;
	size_t size_shader = 0;
	Quad one = Quad(&shader_byte_code, size_shader);
	
	/*VERTEX SHADER*/
	GraphicsEngine::get()->compileVertexShader(L"VertexShader.hlsl", "vsmain", &shader_byte_code, &size_shader);

	m_vs = GraphicsEngine::get()->createVertexShader(shader_byte_code, size_shader);
	//m_vb->load(list, sizeof(vertex), size_list, shader_byte_code, size_shader);
	//m_vb_rect->load(rect_list, sizeof(vertex), size_list_rect, shader_byte_code, size_shader);
	//m_vb_rect2->load(rect_list2, sizeof(vertex), size_list_rect2, shader_byte_code, size_shader);

	GraphicsEngine::get()->releaseCompiledShader();

	/*PIXEL SHADER*/
	GraphicsEngine::get()->compilePixelShader(L"PixelShader.hlsl", "psmain", &shader_byte_code, &size_shader);
	m_ps = GraphicsEngine::get()->createPixelShader(shader_byte_code, size_shader);
	GraphicsEngine::get()->releaseCompiledShader();

	constant cc;
	cc.m_angle = 0;

	m_cb = GraphicsEngine::get()->createConstantBuffer();
	m_cb->load(&cc, sizeof(constant));

}

void AppWindow::onUpdate()
{
	Window::onUpdate();
	GraphicsEngine::get()->getImmediateDeviceContext()->clearRenderTargetColor(this->m_swap_chain,
		0, 0.3f, 0.4f, 1);
	RECT rc = this->getClientWindowRect();
	//Set default shader in the graphics pipelinee to be able to draw
	GraphicsEngine::get()->getImmediateDeviceContext()->setViewportSize(rc.right - rc.left, rc.bottom - rc.top);

	unsigned long new_time = 0;
	if (m_old_time) {
		new_time = ::GetTickCount() - m_old_time;
	}
	m_delta_time = new_time / 1000.0f;
	m_old_time = ::GetTickCount();
	m_angle += 1.57f * m_delta_time;
	constant cc;
	cc.m_angle = m_angle;
	

	m_cb->update(GraphicsEngine::get()->getImmediateDeviceContext(), &cc);

	GraphicsEngine::get()->getImmediateDeviceContext()->setConstantBuffer(m_vs, m_cb);
	GraphicsEngine::get()->getImmediateDeviceContext()->setConstantBuffer(m_ps, m_cb);

	GraphicsEngine::get()->getImmediateDeviceContext()->setVertexShader(m_vs);
	GraphicsEngine::get()->getImmediateDeviceContext()->setPixelShader(m_ps);

	GraphicsEngine::get()->getImmediateDeviceContext()->setVertexBuffer(m_vb);
	GraphicsEngine::get()->getImmediateDeviceContext()->drawTriangleStrip(m_vb->getSizeVertexList(), 0);
	/*Right Rectangle*/
	//GraphicsEngine::get()->getImmediateDeviceContext()->setVertexBuffer(m_vb_rect);
	//GraphicsEngine::get()->getImmediateDeviceContext()->drawTriangleStrip(m_vb_rect->getSizeVertexList(), 0);
	///*Left Rectangle*/
	//GraphicsEngine::get()->getImmediateDeviceContext()->setVertexBuffer(m_vb_rect2);
	//GraphicsEngine::get()->getImmediateDeviceContext()->drawTriangleStrip(m_vb_rect2->getSizeVertexList(), 0);
	m_swap_chain->present(true);
}

void AppWindow::onDestroy()
{
	Window::onDestroy();
	m_vb->release();
	//m_vb_rect->release();
	m_swap_chain->release();
	m_vs->release();
	m_ps->release();
	GraphicsEngine::get()->release();
}
