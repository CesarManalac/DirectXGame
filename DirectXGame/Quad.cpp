#include "Quad.h"
#include <iostream>

Quad::Quad(void* shader_byte_code, size_t shader_size)
{
	std::cout << "Loaded\n";
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

void Quad::Load()
{

}

