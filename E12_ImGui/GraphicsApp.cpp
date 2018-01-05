// GraphicsApp.cpp
#include "GraphicsApp.h"

GraphicsApp::GraphicsApp()
{
	// geometry meshes
	triangleMesh = nullptr;
	sphereMesh = nullptr;
	cubeMesh = nullptr;
	quadMesh = nullptr;
	planeMesh = nullptr;
	terrainMesh = nullptr;

	specularLightExample = nullptr;
	tessellationExample = nullptr;
	terrainExample = nullptr;
	multiLightExample = nullptr;
	geometryExample = nullptr;
	example = nullptr;
}

// Release the Direct3D objects
GraphicsApp::~GraphicsApp()
{
	// Run base application deconstructor
	BaseApplication::~BaseApplication();
	
	// meshes
	if (triangleMesh)
	{
		delete triangleMesh;
		triangleMesh = 0;
	}

	if (sphereMesh)
	{
		delete sphereMesh;
		sphereMesh = 0;
	}

	if (cubeMesh)
	{
		delete cubeMesh;
		cubeMesh = 0;
	}

	if (quadMesh)
	{
		delete quadMesh;
		quadMesh = 0;
	}

	if (planeMesh)
	{
		delete planeMesh;
		planeMesh = 0;
	}

	if (terrainMesh)
	{
		delete terrainMesh;
		terrainMesh = 0;
	}

	// examples
	specularLightExample->~SpecularLightExample();
	tessellationExample->~TessellationExample();
	terrainExample->~TerrainExample();
	multiLightExample->~MultiLightExample();
	geometryExample->~GeometryExample();
}

void GraphicsApp::loadTextures()
{
	// load textures
	textureMgr->loadTexture("brick", L"../res/brick1.dds");
	textureMgr->loadTexture("bunny", L"../res/bunny.png");
	textureMgr->loadTexture("height", L"../res/height.png");
	textureMgr->loadTexture("checkerboard", L"../res/checkerboard.png");
}

// Create mesh objects
void GraphicsApp::initGeometry()
{
	triangleMesh = new TriangleMesh(renderer->getDevice(), renderer->getDeviceContext());
	sphereMesh = new SphereMesh(renderer->getDevice(), renderer->getDeviceContext());
	cubeMesh = new CubeMesh(renderer->getDevice(), renderer->getDeviceContext());
	quadMesh = new QuadMesh(renderer->getDevice(), renderer->getDeviceContext());
	planeMesh = new PlaneMesh(renderer->getDevice(), renderer->getDeviceContext());
	terrainMesh = new TerrainMesh(renderer->getDevice(), renderer->getDeviceContext(), 100, 200);
}

void GraphicsApp::initExamples()
{
	specularLightExample = new SpecularLightExample;
	terrainExample = new TerrainExample;
	tessellationExample = new TessellationExample;
	multiLightExample = new MultiLightExample;
	geometryExample = new GeometryExample;
}

void GraphicsApp::init(HINSTANCE hinstance, HWND hwnd, int screenWidth, int screenHeight, Input *in)
{
	// Call super init function (required!)
	BaseApplication::init(hinstance, hwnd, screenWidth, screenHeight, in);
	// set default example to render
	example_choice = EXAMPLE_CHOICE::SPECULAR_LIGHT;

	loadTextures();
	initGeometry();
	initExamples();

	specularLightExample->init(renderer, hwnd);
	terrainExample->init(renderer, hwnd);
	tessellationExample->init(renderer, hwnd);
	multiLightExample->init(renderer, hwnd);
	geometryExample->init(renderer, hwnd);
}

bool GraphicsApp::frame()
{
	bool result;

	result = BaseApplication::frame();
	if (!result)
	{
		return false;
	}

	// calculate new y position of light_terrain
	terrainExample->over_time += XM_PIDIV2 * timer->getTime();
	terrainExample->over_time = fmodf(terrainExample->over_time, XM_2PI);

	// Render the graphics.
	result = render();
	if (!result)
	{
		return false;
	}

	return true;
}

bool GraphicsApp::render()
{
	// Clear the scene. (default blue colour)
	renderer->beginScene(0.39f, 0.58f, 0.92f, 1.0f);

	// update camera
	camera->update();

	// choose example
	chooseExample();

	// render example
	example->setMesh(chooseMesh(example->mesh_choice));
	example->render(renderer, camera, textureMgr);
	
	// Render GUI
	gui();

	// Present the rendered scene to the screen.
	renderer->endScene();

	return true;
}

void GraphicsApp::gui()
{
	// Force turn off on Geometry shader and force fill rendering
	renderer->getDeviceContext()->GSSetShader(NULL, NULL, 0);
	renderer->getDeviceContext()->HSSetShader(NULL, NULL, 0);
	renderer->getDeviceContext()->DSSetShader(NULL, NULL, 0);
	renderer->setWireframeMode(false);

	// MAIN WINDOW DISPLAY INFO
	ImGui::Text("FPS: %.2f", timer->getFPS());
	ImGui::Text("Camera Position: x: %.2f y: %.2f z: %.2f", camera->getPosition().x, camera->getPosition().y, camera->getPosition().z);
	// MAIN WINDOW BUTTONS
	if (ImGui::Button("Reset camera"))
	{
		camera->resetCamera();
	}
	// CHOOSE SPECULAR LIGHT EXAMPLE
	else if (ImGui::Button("Specular Light Example"))
	{ 
		// set choice
		example_choice = EXAMPLE_CHOICE::SPECULAR_LIGHT;
		specularLightExample->example ^= 1;
		tessellationExample->example = false;
		terrainExample->example = false;
		multiLightExample->example = false;
		geometryExample->example = false;

		specularLightExample->resetExample(camera);
	}
	// CHOOSE TESSELLATION EXAMPLE
	else if (ImGui::Button("Tessellation Example"))
	{
		// set choice
		example_choice = EXAMPLE_CHOICE::TESSELLATION;
		specularLightExample->example = false;
		tessellationExample->example ^= 1;
		terrainExample->example = false;
		multiLightExample->example = false;
		geometryExample->example = false;

		tessellationExample->resetExample(camera);
	}
	// CHOOSE TERRAIN EXAMPLE 
	else if (ImGui::Button("Terrain Example"))
	{
		// set choice
		example_choice = EXAMPLE_CHOICE::TERRAIN;
		specularLightExample->example = false;
		tessellationExample->example = false;
		terrainExample->example ^= 1;
		multiLightExample->example = false;
		geometryExample->example = false;

		terrainExample->resetExample(camera);
	}
	// CHOOSE MULTI LIGHT EXAMPLE
	else if (ImGui::Button("Multi Light Example"))
	{
		// set choice
		example_choice = EXAMPLE_CHOICE::MULTILIGHT;
		specularLightExample->example = false;
		tessellationExample->example = false;
		terrainExample->example = false;
		multiLightExample->example ^= 1;
		geometryExample->example = false;

		multiLightExample->resetExample(camera);
	}
	// CHOOSE GEOMETRY SHADER EXAMPLE 
	else if (ImGui::Button("Geometry Shader Example"))
	{
		// set choice
		example_choice = EXAMPLE_CHOICE::GEOMETRY;
		specularLightExample->example = false;
		tessellationExample->example = false;
		terrainExample->example = false;
		multiLightExample->example = false;
		geometryExample->example ^= 1;

		geometryExample->resetExample(camera);
	}

	// EXAMPLES' GUI
	specularLightExample->gui(camera);
	tessellationExample->gui(camera);
	terrainExample->gui(camera);
	multiLightExample->gui(camera);
	geometryExample->gui(camera);

	// Render UI
	ImGui::Render();
}

void GraphicsApp::chooseExample()
{
	switch (example_choice)
	{
	case EXAMPLE_CHOICE::SPECULAR_LIGHT:
		example = specularLightExample;
		break;

	case EXAMPLE_CHOICE::TESSELLATION:
		example = tessellationExample;
		break;

	case EXAMPLE_CHOICE::TERRAIN:
		example = terrainExample;
		break;

	case EXAMPLE_CHOICE::MULTILIGHT:
		example = multiLightExample;
		break;

	case EXAMPLE_CHOICE::GEOMETRY:
		example = geometryExample;
		break;

	default:
		example = specularLightExample;
		break;
	}
}

BaseMesh* GraphicsApp::chooseMesh(const MESH_CHOICE& mesh_choice)
{
	BaseMesh* temp_mesh;
	switch (mesh_choice)
	{
	case MESH_CHOICE::TRIANGLE:
		temp_mesh = triangleMesh;
		break;

	case MESH_CHOICE::SPHERE:
		temp_mesh = sphereMesh;
		break;

	case MESH_CHOICE::CUBE:
		temp_mesh = cubeMesh;
		break;

	case MESH_CHOICE::QUAD:
		temp_mesh = quadMesh;
		break;

	case MESH_CHOICE::PLANE:
		temp_mesh = planeMesh;
		break;

	case MESH_CHOICE::TERRAIN:
		temp_mesh = terrainMesh;
		break;

	default:
		temp_mesh = triangleMesh;
		break;
	}

	return temp_mesh;
}

float GraphicsApp::clamp(float n, float lower, float upper)
{
	return std::fmax(lower, (std::fmin(n, upper)));
}

