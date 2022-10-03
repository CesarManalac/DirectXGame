#pragma once
#include "VertexShader.h"
#include "PixelShader.h"
#include "VertexBuffer.h"
#include "ConstantBuffer.h"
#include <iostream>
//#include "IndexBuffer.h"

class Quad
{
public:
	Quad(std::string name, void* shader_byte_code, size_t size_shader);
	~Quad();

	void update(float deltaTime);
	void draw(int width, int height, VertexShader* vertexShader, PixelShader* pixelShader);
	

private:
	VertexBuffer* vertexBuffer;
	ConstantBuffer* constantBuffer;
	//IndexBuffer* indexBuffer;
	float ticks = 0.0f;
	float deltaPos = 0.0f;
	float deltaTime = 0.0f;
	float speed = 10.0f;
};

