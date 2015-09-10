#include "Mesh.h"

using namespace DirectX;

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
	UINT stride = sizeof(Vertex);
	UINT offset = 0;
	context->IASetVertexBuffers(0, 1, &vBuffer, &stride, &offset);
	context->IASetIndexBuffer(iBuffer, DXGI_FORMAT_R32_UINT, 0);
	context->DrawIndexed(indexCount, 0, 0);
}
