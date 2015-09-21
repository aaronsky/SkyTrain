#pragma once
#include "Mesh.h"
class Rect :
	public Mesh
{
public:
	Rect(ID3D11Device* device);
	~Rect();
};

