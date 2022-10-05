#include "Quad.h"
#include <iostream>

Quad::Quad(void* shader_byte_code, size_t shader_size)
{
	std::cout << "Loaded\n";
	m_vb = GraphicsEngine::get()->createVertexBuffer();
	size_list = ARRAYSIZE(list);
	m_shader_byte_code = shader_byte_code;
	m_shader_size = shader_size;
}

Quad::~Quad()
{
}

void Quad::Update(float deltaTime)
{

}
/*
	Same as AppWindow onCreate
*/
void Quad::Draw(VertexShader* vertexShader, PixelShader* pixelShader)
{

}

void Quad::Load(int index)
{
	m_vb->load(&list[index], sizeof(vertex), size_list, m_shader_byte_code, m_shader_size);

}

