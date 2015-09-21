#pragma once
#include "DirectXGameCore.h"
#include "Vertex.h"

class Mesh
{
public:
	Mesh();
	~Mesh();
	void Init(Vertex* vertices, int vertexCount, unsigned int* indices, int indexCount, ID3D11Device* device);
	ID3D11Buffer* GetVertexBuffer();
	ID3D11Buffer* GetIndexBuffer();
	int GetIndexCount();
	void Draw(ID3D11DeviceContext* context);
private:
	ID3D11Buffer* vBuffer;
	ID3D11Buffer* iBuffer;
	int indexCount;
};

