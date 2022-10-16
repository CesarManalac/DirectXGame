#pragma once
#include "VertexShader.h"
#include "PixelShader.h"
#include "VertexBuffer.h"
#include "ConstantBuffer.h"
#include "GraphicsEngine.h"
#include "DeviceContext.h"
#include "EngineTime.h"
#include "Vector3D.h"
#include "Matrix4x4.h"
#include "IndexBuffer.h"
#include "AGameObject.h"


class Quad : public AGameObject
{
public:
	Quad(string name);
	~Quad();

	void UpdateQuadPosition();
	void update(float deltaTime) override;
	void draw(int width, int height)override;
	void Release();

private:
	ConstantBuffer* m_cb;
	VertexBuffer* m_vb;
	VertexShader* m_vs;
	PixelShader* m_ps;
	IndexBuffer* m_ib;

	RECT window;
	Vector3D tempPosition;

	int m_width, m_height;
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

