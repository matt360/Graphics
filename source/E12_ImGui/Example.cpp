#include "Example.h"

Example::Example()
{
}

Example::~Example()
{
}

// not passing through the reference because we're not modifying the passed value
void Example::set_mesh_choice(const MESH_CHOICE msh_ch)
{
	switch (msh_ch)
	{
	case MESH_CHOICE::TRIANGLE:
		mesh_choice_ = MESH_CHOICE::TRIANGLE;
		triangle_mesh_ = true;
		sphere_mesh_ = false;
		cube_mesh_ = false;
		quad_mesh_ = false;
		plane_mesh_ = false;
		break;

	case MESH_CHOICE::SPHERE:
		mesh_choice_ = MESH_CHOICE::SPHERE;
		triangle_mesh_ = false;
		sphere_mesh_ = true;
		cube_mesh_ = false;
		quad_mesh_ = false;
		plane_mesh_ = false;
		break;

	case MESH_CHOICE::CUBE:
		mesh_choice_ = MESH_CHOICE::CUBE;
		triangle_mesh_ = false;
		sphere_mesh_ = false;
		cube_mesh_ = true;
		quad_mesh_ = false;
		plane_mesh_ = false;
		break;

	case MESH_CHOICE::QUAD:
		mesh_choice_ = MESH_CHOICE::QUAD;
		triangle_mesh_ = false;
		sphere_mesh_ = false;
		cube_mesh_ = false;
		quad_mesh_ = true;
		plane_mesh_ = false;
		break;

	case MESH_CHOICE::PLANE:
		mesh_choice_ = MESH_CHOICE::PLANE;
		triangle_mesh_ = false;
		sphere_mesh_ = false;
		cube_mesh_ = false;
		quad_mesh_ = false;
		plane_mesh_ = true;
		break;

	// triangle mesh_choice by default
	default:
		mesh_choice_ = MESH_CHOICE::TRIANGLE;
		triangle_mesh_ = true;
		sphere_mesh_ = false;
		cube_mesh_ = false;
		quad_mesh_ = false;
		plane_mesh_ = false;
		break;
	}
}
