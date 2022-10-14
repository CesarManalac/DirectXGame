#pragma once
#include "VertexShader.h"
#include "PixelShader.h"
#include "VertexBuffer.h"
#include "ConstantBuffer.h"
#include "GraphicsEngine.h"
#include "DeviceContext.h"
#include "EngineTime.h"
#include "Vector3.h"
#include "Matrix4x4.h"
#include "IndexBuffer.h"

struct vertex
{
	Vector3 position;
	Vector3 color;
	Vector3 color1;
};

__declspec(align(16))
struct constant
{
	Matrix4x4 m_world;
	Matrix4x4 m_view;
	Matrix4x4 m_projection;
	float m_angle;
};

class Quad
{
public:
	Quad(RECT rc);
	Quad(Vector3 offset, RECT rc);
	~Quad();

	void UpdateQuadPosition();
	void Update();
	void Release();

private:
	ConstantBuffer* m_cb;
	VertexBuffer* m_vb;
	VertexShader* m_vs;
	PixelShader* m_ps;
	IndexBuffer* m_ib;

	RECT window;
	Vector3 tempPosition;

	float width, height;
	void* m_shader_byte_code;
	size_t m_shader_size;
	float time;
	float m_speed = 1;
	bool reset = true;
private:
	float m_old_delta;
	float m_delta_time;
	float m_delta_pos = 0;
	float m_delta_scale = 0;
};

