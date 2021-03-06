// Light shader.h
// Basic single light shader setup
#pragma once

#include "../DXFramework/BaseShader.h"
#include "../DXFramework/Light.h"
#include "../DXFramework/Camera.h"
#include <vector>

using namespace std;
using namespace DirectX;

const unsigned NUM_LIGHTS = 16;

class MultiLightShader : public BaseShader
{
private:
	struct CameraBufferType
	{
		XMFLOAT3 cameraPosition;
		float padding;
	};

	struct LightColourBufferType
	{
		XMFLOAT4 diffuseColor[NUM_LIGHTS];
	};

	struct LightPositionBufferType
	{
		XMFLOAT4 lightPosition[NUM_LIGHTS];
	};

public:
	// When resources are being created and interfaced with,
	// the 'device' interface is used.
	MultiLightShader(ID3D11Device* device, HWND hwnd);
	~MultiLightShader();

	// When the pipeline or a resource is being manipulated,
	// the 'device context' is used.
	void setShaderParameters(ID3D11DeviceContext* deviceContext, const XMMATRIX &world, const XMMATRIX &view, const XMMATRIX &projection, 
		ID3D11ShaderResourceView* texture, 
		const std::vector<XMFLOAT4*>& lightColour,
		const std::vector<XMFLOAT4*>& lightPosition);
	void render(ID3D11DeviceContext* deviceContext, int vertexCount);

	const unsigned number_of_lights_ = NUM_LIGHTS;

private:
	void initShader(WCHAR*, WCHAR*);


private:
	ID3D11SamplerState* sampleState_;
	ID3D11Buffer* matrixBuffer_;
	ID3D11Buffer* cameraBuffer_;
	ID3D11Buffer* lightColorBuffer_;
	ID3D11Buffer* lightPositionBuffer_;
};