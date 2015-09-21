#pragma once
#include "Mesh.h"
class Triangle :
	public Mesh
{
public:
	Triangle(ID3D11Device* device);
	~Triangle();
};

