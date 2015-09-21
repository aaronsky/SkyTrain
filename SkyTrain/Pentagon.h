#pragma once
#include "Mesh.h"
class Pentagon :
	public Mesh
{
public:
	Pentagon(ID3D11Device* device);
	~Pentagon();
};

