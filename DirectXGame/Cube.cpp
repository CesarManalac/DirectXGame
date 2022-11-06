#include "Cube.h"

Cube::Cube(string name):AGameObject(name)
{
	float zNear = 0.1f;
	float zFar = 100.0f;

	float FOV = 1.57f;

	float fovRadians = FOV / 180 * 3.14;

	float nearHeight = 2 * tan(fovRadians / 2) * zNear;
	float farHeight = 2 * tan(fovRadians / 2) * (zFar - zNear);
	float nearWidth = nearHeight * m_width / m_height;
	float farWidth = farHeight * m_width / m_height;

	//vertex vertex_list[] =
	//{
	//	//FRONT FACE
	//	{Vector3D(-(nearWidth * 0.5), (-nearHeight * 0.5), zNear / 2),    Vector3D(1,0,0),  Vector3D(1,0,0) },
	//	{Vector3D((nearWidth * 0.5), (-nearHeight * 0.5), zNear / 2),    Vector3D(1,1,0), Vector3D(1,1,0) },
	//	{Vector3D((-nearWidth * 0.5), (nearHeight * 0.5), zNear / 2),   Vector3D(1,1,0),  Vector3D(1,1,0) },
	//	{Vector3D((nearWidth * 0.5), (nearHeight * 0.5), zNear / 2),     Vector3D(1,0,0), Vector3D(1,0,0) },

	//	//BACK FACE
	//	{Vector3D(-(farWidth * 0.5), (-farHeight * 0.5), (zFar - zNear)),    Vector3D(0,1,0), Vector3D(0,1,0) },
	//	{Vector3D((farWidth * 0.5), (-farHeight * 0.5), (zFar - zNear)),    Vector3D(0,1,1), Vector3D(0,1,1) },
	//	{Vector3D((-farWidth * 0.5), (farHeight * 0.5), (zFar - zNear)),   Vector3D(0,1,1),  Vector3D(0,1,1) },
	//	{Vector3D((farWidth * 0.5), (farHeight * 0.5), (zFar - zNear)), Vector3D(0,1,0) },
	//};

	vertex vertex_list[] = {
		//X, Y, Z
		//FRONT FACE
		{Vector3D(-0.5f,-0.5f,-0.5f),    Vector3D(1,0,.5), Vector3D(0.2f,0,0) },
		{Vector3D(-0.5f,0.5f,-0.5f),     Vector3D(1,.5,1), Vector3D(0.2f,0.2f,0) },
		{Vector3D(0.5f,0.5f,-0.5f),      Vector3D(1,.5,.5), Vector3D(0.2f,0.2f,0) },
		{Vector3D(0.5f,-0.5f,-0.5f),     Vector3D(1,0,.5), Vector3D(0.2f,0,0) },

		//BACK FACE
		{Vector3D(0.5f,-0.5f,0.5f),      Vector3D(1,0,1), Vector3D(0,0.2f,0) },
		{Vector3D(0.5f,0.5f,0.5f),       Vector3D(1,.5,.5), Vector3D(0,0.2f,0.2f) },
		{Vector3D(-0.5f,0.5f,0.5f),      Vector3D(1,0,.5), Vector3D(0,0.2f,0.2f) },
		{Vector3D(-0.5f,-0.5f,0.5f),     Vector3D(1,.5,1), Vector3D(0,0.2f,0) },
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
	cc.m_time = 0;

	m_cb = GraphicsEngine::get()->createConstantBuffer();
	m_cb->load(&cc, sizeof(constant));
}

Cube::~Cube()
{
}

void Cube::UpdateCubePosition()
{
	constant cc;
	cc.m_time = m_delta_time * this->m_speed;
	Matrix4x4 temp;

	Matrix4x4 projTrans;

	/*projTrans.setIdentity();
	projTrans.setTranslation();*/

	Matrix4x4 trans;
	trans.setIdentity();
	trans.setTranslation(this->getLocalPosition());

	cc.m_world.setIdentity();
	cc.m_world.setScale(this->getLocalScale());


	temp.setIdentity();
	temp.setRotationZ(getLocalRotation().z);
	cc.m_world *= temp;
	
	temp.setIdentity();
	temp.setRotationY(this->getLocalRotation().y);
	cc.m_world *= temp;
	
	temp.setIdentity();
	temp.setRotationX(this->getLocalRotation().x);
	cc.m_world *= temp;

	/*cc.m_world.setPerspectiveFovLH(1.57f, m_width / m_height, 0.1f, 100.0f);
	cc.m_world.inverse();*/

	cc.m_world *= trans;

	cc.m_view = m_world_cam;
	
	cc.m_projection.setIdentity();
	cc.m_projection.setPerspectiveFovLH(1.57f, m_width/m_height, 0.1f, 100.0f);
	//cc.m_projection.setOrtho((m_width) / 400.0f, (m_height) / 400.0f, -4.0f, 4.0f);

	m_cb->update(GraphicsEngine::get()->getImmediateDeviceContext(), &cc);
}

void Cube::update(float deltaTime)
{
	m_delta_time = deltaTime;
}

void Cube::draw(int width, int height)
{
	m_width = width;
	m_height = height;
	UpdateCubePosition();

	GraphicsEngine::get()->getImmediateDeviceContext()->setConstantBuffer(m_vs, m_cb);
	GraphicsEngine::get()->getImmediateDeviceContext()->setConstantBuffer(m_ps, m_cb);

	GraphicsEngine::get()->getImmediateDeviceContext()->setVertexShader(m_vs);
	GraphicsEngine::get()->getImmediateDeviceContext()->setPixelShader(m_ps);
	GraphicsEngine::get()->getImmediateDeviceContext()->setVertexBuffer(m_vb);
	GraphicsEngine::get()->getImmediateDeviceContext()->setIndexBuffer(m_ib);

	GraphicsEngine::get()->getImmediateDeviceContext()->drawIndexedTriangleList(m_ib->getSizeIndexList(), 0, 0);
}

void Cube::setView(Matrix4x4 viewMatrix)
{
	m_world_cam = viewMatrix;
}

void Cube::setSpeed(float speed)
{
	this->m_speed = speed;
}

void Cube::Release()
{
	m_vb->release();
	m_ib->release();
	m_cb->release();
	m_vs->release();
	m_ps->release();
}
