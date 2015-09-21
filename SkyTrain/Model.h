#pragma once
#include <vector>
#include <fstream>
#include "Mesh.h"
class Model :
	public Mesh
{
public:
	Model(std::string objName, ID3D11Device* device);
	~Model();
	void LoadModel(std::string objName, ID3D11Device * device);
};

