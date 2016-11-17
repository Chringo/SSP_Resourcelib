#include "Mesh.h"


Resources::Mesh::Mesh(Resource::RawResourceData resData, RawMeshData meshData) :
	Resource(resData)
{
	this->m_resourceData.m_resType = ResourceType::RES_MESH;
	m_meshData = meshData;

	switch (meshData.hasAnimation)
	{
	case true:
		this->SetVertices(meshData.m_animVertices, meshData.m_numVerts);
		break;
	case false:
		this->SetVertices(meshData.m_vertices, meshData.m_numVerts);
		break;
	}

	SetIndices(meshData.m_indices, meshData.m_numIndices);
}

Resources::Mesh::Mesh(Resource::RawResourceData resData)
	:Resource(resData)
{
	this->m_resourceData.m_resType = ResourceType::RES_MESH;
}

Resources::Mesh::~Mesh()
{
	EraseMeshData();
}

bool Resources::Mesh::SetVertices(Vertex * data, unsigned int numVerts)
{
	if (m_meshData.m_vertices != nullptr)
	{
		delete[] m_meshData.m_vertices;
		m_meshData.m_vertices = nullptr;
	}
	if (m_meshData.m_animVertices != nullptr)
	{
		delete[] m_meshData.m_animVertices;
		m_meshData.m_animVertices = nullptr;
	}
	Resources::SAFE_RELEASE(m_vertBuffer);
	Resources::SAFE_RELEASE(m_AnimVertBuffer);
	
	m_meshData.m_vertices = data;


	D3D11_BUFFER_DESC bufferDesc;
	memset(&bufferDesc, 0, sizeof(bufferDesc));
	bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bufferDesc.Usage = D3D11_USAGE_DEFAULT;
	bufferDesc.ByteWidth = sizeof(Vertex)* numVerts;


	D3D11_SUBRESOURCE_DATA b_data;
	b_data.pSysMem = m_meshData.m_vertices;
	HRESULT hr;
	//hr = gDevice->CreateBuffer(&bufferDesc, &b_data, &m_vertBuffer);

	if (FAILED(hr))
		return false;


	
	
	return true;
}

bool Resources::Mesh::SetVertices(VertexAnim * data, unsigned int numVerts)
{
	if (numVerts = 0) return false;

	if (m_meshData.m_vertices != nullptr)
	{
		delete[] m_meshData.m_vertices;
		m_meshData.m_vertices = nullptr;
	}
	if (m_meshData.m_animVertices != nullptr)
	{
		delete[] m_meshData.m_animVertices;
		m_meshData.m_animVertices = nullptr;
	}
	Resources::SAFE_RELEASE(m_vertBuffer);
	Resources::SAFE_RELEASE(m_AnimVertBuffer);

	m_meshData.m_animVertices = data;


	D3D11_BUFFER_DESC bufferDesc;
	memset(&bufferDesc, 0, sizeof(bufferDesc));
	bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bufferDesc.Usage = D3D11_USAGE_DEFAULT;
	bufferDesc.ByteWidth = sizeof(VertexAnim)* numVerts;


	D3D11_SUBRESOURCE_DATA b_data;
	b_data.pSysMem = m_meshData.m_animVertices;
	HRESULT hr;
	//hr = gDevice->CreateBuffer(&bufferDesc, &b_data, &m_AnimVertBuffer);

	if (FAILED(hr))
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

bool Resources::Mesh::EraseMeshData()
{
	delete[] m_meshData.m_animVertices;
	delete[] m_meshData.m_vertices;
	delete[] m_meshData.m_indices;

	if (!Resources::SAFE_RELEASE(m_AnimVertBuffer)) return false;
	if (!Resources::SAFE_RELEASE(m_vertBuffer))		return false;
	if (!Resources::SAFE_RELEASE(m_indexBuffer))	return false;
	
	return true;
}

bool Resources::Mesh::SetMeshData(RawMeshData* newMeshData)
{
	if (!EraseMeshData())
		return false;

	memcpy(&m_meshData, newMeshData, sizeof(RawMeshData));


	switch (m_meshData.hasAnimation)
	{
	case true:
		if(!SetVertices(m_meshData.m_animVertices, m_meshData.m_numVerts)) return false;
		break;
	case false:
		if(!SetVertices(m_meshData.m_vertices, m_meshData.m_numVerts)) return false;
		break;
	}

	return SetIndices(m_meshData.m_indices, m_meshData.m_numIndices);
}
