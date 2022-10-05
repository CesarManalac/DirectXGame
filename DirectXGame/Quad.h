#pragma once
#include "VertexShader.h"
#include "PixelShader.h"
#include "VertexBuffer.h"
#include "ConstantBuffer.h"
#include "GraphicsEngine.h"
#include "DeviceContext.h"

struct vec3
{
	float x, y, z;
};

struct vertex
{
	vec3 position;
	vec3 position1;
	vec3 color;
	vec3 color1;
};


class Quad
{
public:
	Quad(void* shader_byte_code, size_t shader_size);
	~Quad();

	void Update(float deltaTime);
	void Draw(VertexShader* vertexShader, PixelShader* pixelShader);
	void Load(int index);

private:
	ConstantBuffer* constantBuffer;
	VertexBuffer* m_vb;
	VertexShader* m_vs;
	PixelShader* m_ps;

	vertex list[4];
	UINT size_list;

	void* m_shader_byte_code;
	size_t m_shader_size;

	float ticks = 0.0f;
	float deltaPos = 0.0f;
	float deltaTime = 0.0f;
	//float speed = 10.0f;
};

