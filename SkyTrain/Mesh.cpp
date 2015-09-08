#include "Mesh.h"

using namespace DirectX;

void Mesh::InitGeometry(ID3D11Device* device)
{
	XMFLOAT4 red = XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f);
	XMFLOAT4 green = XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f);
	XMFLOAT4 blue = XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f);

	Vertex triangleVertices[] =
	{
		{ XMFLOAT3(+1.0f, -1.0f, +0.0f), red },
		{ XMFLOAT3(+2.0f, +0.0f, +0.0f), blue },
		{ XMFLOAT3(+1.5f, -1.5f, +0.0f), green },
	};

	Vertex squareVertices[] =
	{
		{ XMFLOAT3(-6.0f, -4.0f, +10.0f), green },
		{ XMFLOAT3(-4.0f, -4.0f, +10.0f), blue },
		{ XMFLOAT3(-4.0f, -6.0f, +10.0f), green },
		{ XMFLOAT3(-6.0f, -6.0f, +10.0f), blue }
	};

	Vertex pentagonVertices[] =
	{
		{ XMFLOAT3(+0.0f, +1.0f, +0.0f), red },
		{ XMFLOAT3(+0.0f, +0.0f, +0.0f), blue },
		{ XMFLOAT3(-0.951057f, +0.309017f, +0.0f), red },
		{ XMFLOAT3(-0.587785f, -0.809017f, +0.0f), red },
		{ XMFLOAT3(+0.587785f, -0.809017f, +0.0f), red },
		{ XMFLOAT3(+0.951057f, +0.309017f, +0.0f), red }
	};

	unsigned int indices[] = { 0, 1, 2 };
	unsigned int squareIndices[] = { 0, 1, 2, 0, 2, 3 };
	unsigned int pentagonIndices[] = { 0, 1, 2, 2, 1, 3, 1, 4, 3, 1, 5, 4, 0, 5, 1 };

	TRIANGLE = new Mesh(triangleVertices, 3, indices, 3, device);
	QUAD = new Mesh(squareVertices, 4, squareIndices, 6, device);
	PENTAGON = new Mesh(pentagonVertices, 6, pentagonIndices, 15, device);
}

Mesh::Mesh(Vertex * vertices, int vertexCount, unsigned int * indices, int indexCount, ID3D11Device * device)
{
	D3D11_BUFFER_DESC vbd;
	vbd.Usage = D3D11_USAGE_IMMUTABLE;
	vbd.ByteWidth = sizeof(Vertex) * vertexCount;
	vbd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vbd.CPUAccessFlags = 0;
	vbd.MiscFlags = 0;
	vbd.StructureByteStride = 0;

	D3D11_SUBRESOURCE_DATA initialVertexData;
	initialVertexData.pSysMem = vertices;

	HR(device->CreateBuffer(&vbd, &initialVertexData, &vBuffer));

	D3D11_BUFFER_DESC ibd;
	ibd.Usage = D3D11_USAGE_IMMUTABLE;
	ibd.ByteWidth = sizeof(int) * indexCount;
	ibd.BindFlags = D3D11_BIND_INDEX_BUFFER;
	ibd.CPUAccessFlags = 0;
	ibd.MiscFlags = 0;
	ibd.StructureByteStride = 0;

	D3D11_SUBRESOURCE_DATA initialIndexData;
	initialIndexData.pSysMem = indices;

	this->indexCount = indexCount;

	HR(device->CreateBuffer(&ibd, &initialIndexData, &iBuffer));
}

Mesh::~Mesh()
{
	ReleaseMacro(vBuffer);
	ReleaseMacro(iBuffer);
}

ID3D11Buffer* Mesh::GetVertexBuffer()
{
	return vBuffer;
}

ID3D11Buffer* Mesh::GetIndexBuffer()
{
	return iBuffer;
}

int Mesh::GetIndexCount()
{
	return indexCount;
}

void Mesh::Draw(ID3D11DeviceContext * context)
{
	// Set buffers in the input assembler
	//  - Do this ONCE PER OBJECT you're drawing, since each object might
	//    have different geometry.
	UINT stride = sizeof(Vertex);
	UINT offset = 0;
	context->IASetVertexBuffers(0, 1, &vBuffer, &stride, &offset);
	context->IASetIndexBuffer(iBuffer, DXGI_FORMAT_R32_UINT, 0);
	context->DrawIndexed(indexCount, 0, 0);

	// Finally do the actual drawing
	//  - Do this ONCE PER OBJECT you intend to draw
	//  - This will use all of the currently set DirectX "stuff" (shaders, buffers, etc)
	//  - DrawIndexed() uses the currently set INDEX BUFFER to look up corresponding
	//     vertices in the currently set VERTEX BUFFER
	context->DrawIndexed(
		indexCount,     // The number of indices to use (we could draw a subset if we wanted)
		0,     // Offset to the first index we want to use
		0);    // Offset to add to each index when looking up vertices
}
