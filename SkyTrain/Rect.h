#pragma once
#include "Mesh.h"
class Rect :
	public Mesh
{
public:
	Mesh CreateMesh(ID3D11Device* device);
	Rect(ID3D11Device* device);
	~Rect();
};

