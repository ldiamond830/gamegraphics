#include "Mesh.h"

Mesh::Mesh(Vertex* vertices, int numVertices, unsigned int* indices, int numIndices, Microsoft::WRL::ComPtr<ID3D11DeviceContext> drawCommandPtr, Microsoft::WRL::ComPtr<ID3D11Device> bufferCreator)
{
    this->drawCommandPtr = drawCommandPtr;
    this->numIndices = numIndices;
    this->numVertices = numVertices;

    D3D11_BUFFER_DESC vbd = {};
    vbd.Usage = D3D11_USAGE_IMMUTABLE;	
    vbd.ByteWidth = sizeof(Vertex) * (numVertices);       
    vbd.BindFlags = D3D11_BIND_VERTEX_BUFFER; 
    vbd.CPUAccessFlags = 0;
    vbd.MiscFlags = 0;
    vbd.StructureByteStride = 0;
    D3D11_SUBRESOURCE_DATA initialVertexData = {};
    initialVertexData.pSysMem = vertices;
    bufferCreator->CreateBuffer(&vbd, &initialVertexData, vertexBuffer.GetAddressOf());

    D3D11_BUFFER_DESC ibd = {};
    ibd.Usage = D3D11_USAGE_IMMUTABLE;	
    ibd.ByteWidth = sizeof(unsigned int) * numIndices;	
    ibd.BindFlags = D3D11_BIND_INDEX_BUFFER;	
    ibd.CPUAccessFlags = 0;	
    ibd.MiscFlags = 0;
    ibd.StructureByteStride = 0;
    D3D11_SUBRESOURCE_DATA initialIndexData = {};
    initialIndexData.pSysMem = indices;
    bufferCreator->CreateBuffer(&ibd, &initialIndexData, indexBuffer.GetAddressOf());
}

Mesh::~Mesh()
{
}

Microsoft::WRL::ComPtr<ID3D11Buffer> Mesh::GetVertexBuffer()
{
    return vertexBuffer;
}

Microsoft::WRL::ComPtr<ID3D11Buffer> Mesh::GetIndexBuffer()
{
    return indexBuffer;
}

int Mesh::GetIndexCount()
{
    return numIndices;
}

void Mesh::Draw()
{
    UINT offset = 0;
    UINT stride = sizeof(Vertex);
    drawCommandPtr->IASetVertexBuffers(0, 1, vertexBuffer.GetAddressOf(), &stride, &offset);
    drawCommandPtr->IASetIndexBuffer(indexBuffer.Get(), DXGI_FORMAT_R32_UINT, 0);
    drawCommandPtr->DrawIndexed(numIndices, 0, 0);
}
