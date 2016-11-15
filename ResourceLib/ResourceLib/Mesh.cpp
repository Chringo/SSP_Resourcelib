#include "Mesh.h"


Resources::Mesh::Mesh(Resource::RawResourceData resData, RawMeshData meshData) :
	Resource(resData)
{
	this->m_resourceData.m_resType = ResourceType::RES_MESH;
	m_meshData = meshData;
}

Resources::Mesh::Mesh(Resource::RawResourceData resData)
	:Resource(resData)
{
	this->m_resourceData.m_resType = ResourceType::RES_MESH;
}

Resources::Mesh::~Mesh()
{
	Resources::SAFE_RELEASE(m_AnimVertBuffer);
	Resources::SAFE_RELEASE(m_vertBuffer);
	Resources::SAFE_RELEASE(m_indexBuffer);
}

bool Resources::Mesh::SetVertices(Vertex * data, unsigned int numVerts)
{
	if (m_meshData.m_vertices != nullptr)
	{
		delete[] m_meshData.m_vertices;
		m_meshData.m_vertices = nullptr;
		Resources::SAFE_RELEASE(m_vertBuffer);
	}
	if (m_meshData.m_animVertices != nullptr)
	{
		delete[] m_meshData.m_animVertices;
		m_meshData.m_animVertices = nullptr;
		Resources::SAFE_RELEASE(m_AnimVertBuffer);
	}
	
	
	
	return true;
}

bool Resources::Mesh::SetVertices(VertexAnim * data, unsigned int numVerts)
{
	return false;
}

bool Resources::Mesh::SetIndices(unsigned int * indices, unsigned int numIndices)
{
	HRESULT hr;
	Resources::SAFE_RELEASE(m_indexBuffer);

	D3D11_BUFFER_DESC ibd;

	ibd.Usage = D3D11_USAGE_IMMUTABLE;
	ibd.ByteWidth = sizeof(unsigned int) * numIndices;
	ibd.BindFlags = D3D11_BIND_INDEX_BUFFER;
	ibd.CPUAccessFlags = 0;
	ibd.MiscFlags = 0;
	ibd.StructureByteStride = 0;

	D3D11_SUBRESOURCE_DATA ibdData;
	ibdData.pSysMem = indices;


	// how to get the gDevice in here? Hmmmmm
	//hr = gDevice->CreateBuffer(&ibd, &ibdData, &indexBuffer);

	if (FAILED(hr))
		return false;

	return true;
}
