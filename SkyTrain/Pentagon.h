#pragma once
#include "Mesh.h"
class Pentagon :
	public Mesh
{
public:
	Mesh CreateMesh(ID3D11Device* device);
	Pentagon(ID3D11Device* device);
	~Pentagon();
};

