#pragma once

#include "Example.h"
#include "MultiLightShader.h"

class MultiLightExample : public Example
{
public:
	MultiLightExample();
	~MultiLightExample();

	void init(D3D * renderer, HWND hwnd);
	void initShader(D3D * renderer, HWND hwnd);
	void initLight();
	void render(D3D* renderer, Camera* camera, BaseMesh* mesh, TextureManager* textureMgr);

	// shader handler
	MultiLightShader* shader;

	MESH mesh_choice = MESH::SPHERE;
	bool mesh_check_box;
	
	Light *light0_, *light1_, *light2_, *light3_;
	ImVec4 light0_col, light1_col, light2_col, light3_col;
	XMFLOAT3 light0_pos, light1_pos, light2_pos, light3_pos;
	XMFLOAT3 ml_scale;
	//SphereMesh *lightSphere0_, *lightSphere1_, *lightSphere2_, *lightSphere3_;
};

