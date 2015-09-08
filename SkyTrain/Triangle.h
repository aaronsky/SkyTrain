#pragma once
#include "Mesh.h"
class Triangle :
	public Mesh
{
public:
	Mesh CreateMesh(ID3D11Device* device);
	Triangle(ID3D11Device* device);
	~Triangle();
};

