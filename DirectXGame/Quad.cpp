#include "Quad.h"
#include <iostream>
#include "Window.h"

Quad::Quad(RECT rc)
{
	void* shader_byte_code = nullptr;
	size_t size_shader = 0;
	window = rc;
	vertex list[] =
	{
		{Vector3(-0.25f,-0.25f, 0.0f), Vector3(-0.90f,-0.25f, 0.0f),	Vector3(0,0,0),	Vector3(0,1,0)},
		{Vector3(-0.25f, 0.25f, 0.0f),	Vector3(-0.90f, 0.25f, 0.0f), Vector3(1,1,0), Vector3(0,1,1)},
		{Vector3( 0.25f,-0.25f, 0.0f), Vector3(-0.45f,-0.25f, 0.0f), Vector3(0,0,1),	Vector3(1,0,0)},
		{Vector3( 0.25f, 0.25f, 0.0f),	Vector3(-0.45f, 0.25f, 0.0f),	Vector3(1,1,1),	Vector3(0,0,1)}
	};
	m_vb = GraphicsEngine::get()->createVertexBuffer();
	size_list = ARRAYSIZE(list);

	/*VERTEX SHADER*/
	GraphicsEngine::get()->compileVertexShader(L"VertexShader.hlsl", "vsmain", &shader_byte_code, &size_shader);
	m_vs = GraphicsEngine::get()->createVertexShader(shader_byte_code, size_shader);
	
	m_vb->load(list, sizeof(vertex), size_list, shader_byte_code, size_shader);
	
	GraphicsEngine::get()->releaseCompiledShader();

	/*PIXEL SHADER*/
	GraphicsEngine::get()->compilePixelShader(L"PixelShader.hlsl", "psmain", &shader_byte_code, &size_shader);
	m_ps = GraphicsEngine::get()->createPixelShader(shader_byte_code, size_shader);
	GraphicsEngine::get()->releaseCompiledShader();

	tempPosition = Vector3(0, 0, 0);
	constant cc;
	cc.m_angle = 0;

	m_cb = GraphicsEngine::get()->createConstantBuffer();
	m_cb->load(&cc, sizeof(constant));
}

Quad::Quad(Vector3 offset, RECT rc)
{
	void* shader_byte_code = nullptr;
	size_t size_shader = 0;
	window = rc;
	tempPosition = offset;
	vertex list[] =
	{
		{Vector3(-0.5f,-0.5f, 0.0f), Vector3(-0.5f,-0.5f, 0.0f) + offset,	Vector3(0,0,0),	Vector3(0,1,0)},
		{Vector3(-0.5f, 0.5f, 0.0f), Vector3(-0.5f, 0.5f, 0.0f) + offset,  Vector3(1,1,0), Vector3(0,1,1)},
		{Vector3( 0.5f,-0.5f, 0.0f), Vector3( 0.5f,-0.5f, 0.0f) + offset,  Vector3(0,0,1),	Vector3(1,0,0)},
		{Vector3( 0.5f, 0.5f, 0.0f), Vector3( 0.5f, 0.5f, 0.0f) + offset,	Vector3(1,1,1),	Vector3(0,0,1)}
	};
	m_vb = GraphicsEngine::get()->createVertexBuffer();
	size_list = ARRAYSIZE(list);

	/*VERTEX SHADER*/
	GraphicsEngine::get()->compileVertexShader(L"VertexShader.hlsl", "vsmain", &shader_byte_code, &size_shader);
	m_vs = GraphicsEngine::get()->createVertexShader(shader_byte_code, size_shader);

	m_vb->load(list, sizeof(vertex), size_list, shader_byte_code, size_shader);

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

Quad::~Quad()
{
}

void Quad::UpdateQuadPosition()
{
	time += EngineTime::getDeltaTime() * m_speed;
	constant cc;
	cc.m_angle = time;

	Matrix4x4 temp;

	cc.m_world.setTranslation(Vector3(0, 0, 0));
	temp.setTranslation(tempPosition);

	cc.m_world.setScale(Vector3(.5,.5,.5));
	cc.m_world *= temp;

	cc.m_view.setIdentity();
	cc.m_projection.setOrtho((window.right - window.left) / 400.0f, (window.bottom - window.top) / 400.0f, -4.0f, 4.0f);


	m_cb->update(GraphicsEngine::get()->getImmediateDeviceContext(), &cc);
}

void Quad::Update()
{

	UpdateQuadPosition();

	GraphicsEngine::get()->getImmediateDeviceContext()->setConstantBuffer(m_vs, m_cb);
	GraphicsEngine::get()->getImmediateDeviceContext()->setConstantBuffer(m_ps, m_cb);

	GraphicsEngine::get()->getImmediateDeviceContext()->setVertexShader(m_vs);
	GraphicsEngine::get()->getImmediateDeviceContext()->setPixelShader(m_ps);
	GraphicsEngine::get()->getImmediateDeviceContext()->setVertexBuffer(m_vb);
	GraphicsEngine::get()->getImmediateDeviceContext()->drawTriangleStrip(m_vb->getSizeVertexList(), 0);
}


void Quad::Release()
{
	m_vb->release();
	m_vs->release();
	m_ps->release();
}

