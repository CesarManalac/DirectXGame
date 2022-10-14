#include "Quad.h"
#include <iostream>
#include "Window.h"

Quad::Quad(RECT rc)
{
	window = rc;
	vertex vertex_list[] =
	{		
		{Vector3(-0.5f,-0.5f,-0.5f),  Vector3(0,0,0), Vector3(0,1,0) },
		{Vector3(-0.5f,0.5f,-0.5f),   Vector3(1,1,0), Vector3(0,1,1) },
		{ Vector3(0.5f,0.5f,-0.5f),   Vector3(0,0,1), Vector3(1,0,0) },
		{ Vector3(0.5f,-0.5f,-0.5f),  Vector3(1,1,1), Vector3(0,0,1) },

		//BACK FACE
		{ Vector3(0.5f,-0.5f,0.5f),   Vector3(1,0,1), Vector3(0,1,0) },
		{ Vector3(0.5f,0.5f,0.5f),    Vector3(1,1,0), Vector3(0,0,1) },
		{ Vector3(-0.5f,0.5f,0.5f),   Vector3(1,0,1), Vector3(0,1,0) },
		{ Vector3(-0.5f,-0.5f,0.5f),  Vector3(0,1,1), Vector3(0,0,1) }
	};
	m_vb = GraphicsEngine::get()->createVertexBuffer();
	UINT size_list = ARRAYSIZE(vertex_list);
	
	unsigned int index_list[] =
	{
		//FRONT SIDE
		0,1,2,  //FIRST TRIANGLE
		2,3,0,  //SECOND TRIANGLE
		//BACK SIDE
		4,5,6,
		6,7,4,
		//TOP SIDE
		1,6,5,
		5,2,1,
		//BOTTOM SIDE
		7,0,3,
		3,4,7,
		//RIGHT SIDE
		3,2,5,
		5,4,3,
		//LEFT SIDE
		7,6,1,
		1,0,7
	};

	m_ib = GraphicsEngine::get()->createIndexBuffer();
	UINT size_index_list = ARRAYSIZE(index_list);

	m_ib->load(index_list, size_index_list);

	void* shader_byte_code = nullptr;
	size_t size_shader = 0;
	/*VERTEX SHADER*/
	GraphicsEngine::get()->compileVertexShader(L"VertexShader.hlsl", "vsmain", &shader_byte_code, &size_shader);
	m_vs = GraphicsEngine::get()->createVertexShader(shader_byte_code, size_shader);
	
	m_vb->load(vertex_list, sizeof(vertex), size_list, shader_byte_code, size_shader);
	
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

Quad::Quad(Vector3 offset, RECT rc)
{
	//void* shader_byte_code = nullptr;
	//size_t size_shader = 0;
	//window = rc;
	//tempPosition = offset;
	//vertex list[] =
	//{
	//	{Vector3(-0.5f,-0.5f, 0.0f), 	Vector3(0,0,0),	Vector3(0,1,0)},
	//	{Vector3(-0.5f, 0.5f, 0.0f),  Vector3(1,1,0), Vector3(0,1,1)},
	//	{Vector3( 0.5f,-0.5f, 0.0f),  Vector3(0,0,1),	Vector3(1,0,0)},
	//	{Vector3( 0.5f, 0.5f, 0.0f), 	Vector3(1,1,1),	Vector3(0,0,1)}
	//};
	//m_vb = GraphicsEngine::get()->createVertexBuffer();
	//size_list = ARRAYSIZE(list);

	///*VERTEX SHADER*/
	//GraphicsEngine::get()->compileVertexShader(L"VertexShader.hlsl", "vsmain", &shader_byte_code, &size_shader);
	//m_vs = GraphicsEngine::get()->createVertexShader(shader_byte_code, size_shader);

	//m_vb->load(list, sizeof(vertex), size_list, shader_byte_code, size_shader);

	//GraphicsEngine::get()->releaseCompiledShader();

	///*PIXEL SHADER*/
	//GraphicsEngine::get()->compilePixelShader(L"PixelShader.hlsl", "psmain", &shader_byte_code, &size_shader);
	//m_ps = GraphicsEngine::get()->createPixelShader(shader_byte_code, size_shader);
	//GraphicsEngine::get()->releaseCompiledShader();

	//constant cc;
	//cc.m_angle = 0;

	//m_cb = GraphicsEngine::get()->createConstantBuffer();
	//m_cb->load(&cc, sizeof(constant));
}

Quad::~Quad()
{
}

void Quad::UpdateQuadPosition()
{
	constant cc;
	cc.m_angle = EngineTime::getDeltaTime();

	m_delta_pos += time / 10.0f;
	Matrix4x4 temp;

	if (m_delta_pos > 1.0f) {
		m_delta_pos = 0;
	}

	m_delta_scale += time / 0.55f;

	//cc.m_world.setTranslation(Vector3(1, 1, 1));
	//cc.m_world.setScale(Vector3::lerp(Vector3(.5, .5, 0), Vector3(1, 1, 0), (sin(m_delta_scale) + 1.0f) / 2.0f));
	//temp.setTranslation(Vector3::lerp(Vector3(-.5, -.5, 0), Vector3(.5, .5, 0), m_delta_pos));
	
	//cc.m_world *= temp;
	cc.m_world.setScale(Vector3(1, 1, 1));

	temp.setIdentity();
	temp.setRotationZ(m_delta_scale);
	cc.m_world *= temp;
	
	temp.setIdentity();
	temp.setRotationY(m_delta_scale);
	cc.m_world *= temp;

	temp.setIdentity();
	temp.setRotationX(m_delta_scale);
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
	GraphicsEngine::get()->getImmediateDeviceContext()->setIndexBuffer(m_ib);

	GraphicsEngine::get()->getImmediateDeviceContext()->drawIndexedTriangleList(m_ib->getSizeIndexList(), 0, 0);
	m_old_delta = time;
	time = EngineTime::getDeltaTime();
	m_delta_time = (m_old_delta) ? ((time - m_old_delta) / 1000.0f):0;
}


void Quad::Release()
{
	m_vb->release();
	m_ib->release();
	m_cb->release();
	m_vs->release();
	m_ps->release();

}

