// Light shader.h
// Basic single light shader setup
#pragma once

#include "../DXFramework/BaseShader.h"
#include "../DXFramework/Light.h"
#include "../DXFramework/Camera.h"

using namespace std;
using namespace DirectX;


class TerrainShader : public BaseShader
{
private:
	struct LightBufferType
	{
		XMFLOAT4 ambient;
		XMFLOAT4 diffuse;
		XMFLOAT3 direction;
		float specularPower;
		XMFLOAT4 specular;
		XMFLOAT3 position;
		float padding;
	};

	struct CameraBufferType
	{
		XMFLOAT3 cameraPosition;
		float padding;
	};

	struct TimeBufferType
	{
		float time;
		float height;
		float frequency;
		float choice;
	};

public:
	// When resources are being created and interfaced with,
	// the 'device' interface is used.
	TerrainShader(ID3D11Device* device, HWND hwnd);
	~TerrainShader();

	// When the pipeline or a resource is being manipulated,
	// the 'device context' is used.
	void setShaderParameters(
		ID3D11DeviceContext* deviceContext,
		const XMMATRIX &world,
		const XMMATRIX &view,
		const XMMATRIX &projection,
		ID3D11ShaderResourceView* height_texture,
		ID3D11ShaderResourceView* mapping_texture_1,
		ID3D11ShaderResourceView* mapping_texture_2,
		Light* light,
		float time,
		float height,
		float frequency,
		float choice_number);
	void render(ID3D11DeviceContext* deviceContext, int vertexCount);

private:
	void initShader(WCHAR*, WCHAR*);


private:
	ID3D11Buffer* matrixBuffer_;
	ID3D11SamplerState* sampleState_;
	ID3D11Buffer* lightBuffer_;
	ID3D11Buffer* timeBuffer_;
	ID3D11Buffer* cameraBuffer_;
};