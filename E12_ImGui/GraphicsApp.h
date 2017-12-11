// Application.h
#ifndef _APP1_H
#define _APP1_H

// Includes
#include "../DXFramework/DXF.h"
#include "ColourShader.h"
#include "App9.h"

class GraphicsApp : public BaseApplication
{
public:

	GraphicsApp();
	~GraphicsApp();
	void init(HINSTANCE hinstance, HWND hwnd, int screenWidth, int screenHeight, Input*);

	bool frame();

protected:
	bool render();
	void gui();

private:
	ColourShader* colourShader;
	TriangleMesh* mesh;
	ImVec4 clear_col;
	bool isWireframe;

	bool triangle_colour_shader;
	void triangleColourShader();
};

#endif

