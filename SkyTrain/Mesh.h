#pragma once
#include "DirectXGameCore.h"
#include "Vertex.h"

class Mesh
{
public:
	ID3D11Buffer* vBuffer;
	ID3D11Buffer* iBuffer;
	int indexCount;
	Mesh(Vertex* vertices, int vertexCount, unsigned int* indices, int indexCount, ID3D11Device* device);
	~Mesh();
	ID3D11Buffer* GetVertexBuffer();
	ID3D11Buffer* GetIndexBuffer();
	int GetIndexCount();
};

