#include "Quad.h"
#include <iostream>

Quad::Quad(void* shader_byte_code, size_t shader_size, int index)
{
	m_vb = GraphicsEngine::get()->createVertexBuffer();
	Load(index);
	size_list = ARRAYSIZE(dataList);
	m_shader_byte_code = shader_byte_code;
	m_shader_size = shader_size;
	m_vb->load(dataList, sizeof(vertex), size_list, m_shader_byte_code, m_shader_size);
}

Quad::~Quad()
{
}

void Quad::Update(float deltaTime)
{

}
/*
	Same as AppWindow onCreate theoretically
*/
void Quad::Draw(VertexShader* vertexShader, PixelShader* pixelShader)
{
	GraphicsEngine::get()->getImmediateDeviceContext()->setVertexShader(vertexShader);
	GraphicsEngine::get()->getImmediateDeviceContext()->setPixelShader(pixelShader);
	GraphicsEngine::get()->getImmediateDeviceContext()->setVertexBuffer(m_vb);
	GraphicsEngine::get()->getImmediateDeviceContext()->drawTriangleStrip(m_vb->getSizeVertexList(), 0);
}

void Quad::Load(int index)
{

	vertex list[] =
	{
		{-0.90f,-0.25f, 0.0f,	-0.90f,-0.25f, 0.0f,	0,0,0,	0,1,0},
		{-0.90f, 0.25f, 0.0f,	-0.90f, 0.25f, 0.0f,	1,1,0,	0,1,1},
		{-0.45f,-0.25f, 0.0f,	-0.45f,-0.25f, 0.0f,	0,0,1,	1,0,0},
		{-0.45f, 0.25f, 0.0f,	-0.45f, 0.25f, 0.0f,	1,1,1,	0,0,1}
	};
	vertex list_2[] =
	{
		{0.45f, -0.25f, 0.0f,	0.45f, -0.25f, 0.0f,	0,0,0,	1,1,1},
		{0.45f,  0.25f, 0.0f,	0.45f,  0.25f, 0.0f,	0,0,0,	1,1,1},
		{0.90f, -0.25f, 0.0f,	0.90f, -0.25f, 0.0f,	0,0,0,	1,1,1},
		{0.90f,  0.25f, 0.0f,	0.90f,  0.25f, 0.0f, 	0,0,0,  1,1,1}
	};
	vertex list_3[] = 
	{
		{-0.25f,  0.25f, 0.0f,	-0.25f,  0.25f, 0.0f,	1,0,1,	0,1,0},
		{-0.25f,  0.90f, 0.0f,	-0.25f,  0.90f, 0.0f,	1,1,0,	0,0,1},
		{ 0.25f,  0.25f, 0.0f,	0.25f,  0.25f, 0.0f,	1,0,1,	0,1,0},
		{ 0.25f,  0.90f, 0.0f,	0.25f,  0.90f, 0.0f, 	0,1,1,  1,0,0}
	};
	
	switch (index) {
	case 0:
		for (int i = 0; i < 4; i++) {
			dataList[i] = list[i];
		}; break;
	case 1:
		for (int i = 0; i < 4; i++) {
			dataList[i] = list_2[i];
		}; break;
	case 2:
		for (int i = 0; i < 4; i++) {
			dataList[i] = list_3[i];
		}; break;
	default:
		std::cout << "Wrong Index\n";
	}

	//vertex master_list[] = {
//	{-0.90f,-0.25f, 0.0f,	-0.90f,-0.25f, 0.0f,	0,0,0,	0,1,0},
//	{-0.90f, 0.25f, 0.0f,	-0.90f, 0.25f, 0.0f,	1,1,0,	0,1,1},
//	{-0.45f,-0.25f, 0.0f,	-0.45f,-0.25f, 0.0f,	0,0,1,	1,0,0},
//	{-0.45f, 0.25f, 0.0f,	-0.45f, 0.25f, 0.0f,	1,1,1,	0,0,1},

	//	{0.45f, -0.25f, 0.0f,	0.45f, -0.25f, 0.0f,	0,0,0,	1,1,1},
//	{0.45f,  0.25f, 0.0f,	0.45f,  0.25f, 0.0f,	0,0,0,	1,1,1},
//	{0.90f, -0.25f, 0.0f,	0.90f, -0.25f, 0.0f,	0,0,0,	1,1,1},
//	{0.90f,  0.25f, 0.0f,	0.90f,  0.25f, 0.0f, 	0,0,0,  1,1,1},

	//	{-0.25f,  0.25f, 0.0f,	-0.25f,  0.25f, 0.0f,	1,0,1,	0,1,0},
//	{-0.25f,  0.90f, 0.0f,	-0.25f,  0.90f, 0.0f,	1,1,0,	0,0,1},
//	{ 0.25f,  0.25f, 0.0f,	0.25f,  0.25f, 0.0f,	1,0,1,	0,1,0},
//	{ 0.25f,  0.90f, 0.0f,	0.25f,  0.90f, 0.0f, 	0,1,1,  1,0,0}
//};
}

