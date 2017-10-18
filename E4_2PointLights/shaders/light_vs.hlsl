// Light vertex shader
// Standard issue vertex shader, apply matrices, pass info to pixel shader

// Defines - HLSL allows the use of defines. 
#define NUM_LIGHTS 4;

cbuffer MatrixBuffer : register(cb0)
{
    matrix worldMatrix;
    matrix viewMatrix;
    matrix projectionMatrix;
};

cbuffer CameraBuffer : register(cb1)
{
	float3 cameraPosition;
	float padding;
};

cbuffer LightBuffer : register(cb2)
{
    float4 ambientColor;
    float4 diffuseColor[4];
    float3 lightDirection;
    float specularPower;
    float4 specularColor;
    float4 lightPosition[4];
};

struct InputType
{
    float4 position : POSITION;
    float2 tex : TEXCOORD0;
    float3 normal : NORMAL;
};

struct OutputType
{
    float4 position : SV_POSITION; // SV - system value
    float2 tex : TEXCOORD0;
    float3 normal : NORMAL;
    float3 lightPos1 : TEXCOORD1;
    float3 lightPos2 : TEXCOORD2;
    float3 lightPos3 : TEXCOORD3;
    float3 lightPos4 : TEXCOORD4;
};

OutputType main(InputType input)
{
    OutputType output;
	float4 worldPosition;
    
	//// Change the position vector to be 4 units for proper matrix calculations.
     input.position.w = 1.0f;

    // Calculate the position of the vertex against the world, view, and projection matrices.
    output.position = mul(input.position, worldMatrix);
    output.position = mul(output.position, viewMatrix);
    output.position = mul(output.position, projectionMatrix);
    
    // Store the texture coordinates for the pixel shader.
    output.tex = input.tex;

	 // Calculate the normal vector against the world matrix only.
    output.normal = mul(input.normal, (float3x3) worldMatrix);
	
    // Normalize the normal vector.
    output.normal = normalize(output.normal);

	//// world position of vertex 
 //   //output.position3D = mul(input.position, worldMatrix);

    return output;
}