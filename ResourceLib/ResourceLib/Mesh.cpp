#include "Mesh.h"


Resources::Mesh::Mesh(Resource::RawResourceData resData, RawMeshData meshData, bool keepRawData) :
	Resource(resData)
{
	this->m_resourceData.m_resType = ResourceType::RES_MESH;
	m_meshData = meshData;

	if(meshData.hasAnimation)
		this->SetVertices(meshData.m_animVertices, meshData.m_numVerts,keepRawData);
	else
		this->SetVertices(meshData.m_vertices, meshData.m_numVerts,keepRawData);

	SetIndices(meshData.m_indices, meshData.m_numIndices,keepRawData);
}

Resources::Mesh::Mesh(Resource::RawResourceData resData)
	:Resource(resData)
{
	this->m_resourceData.m_resType = ResourceType::RES_MESH;
}

Resources::Mesh::Mesh() : Resource()
{
	m_resourceData.m_resType = ResourceType::RES_MESH;
}

Resources::Status Resources::Mesh::Create(Resource::RawResourceData * resData, RawMeshData * meshData, bool keepRawData)
{

	m_resourceData = *resData;
	m_resourceData.m_resType = RES_MESH;
	if (meshData != nullptr)
	{
		if(!this->SetIndices(meshData->m_indices, meshData->m_numIndices, keepRawData))	   return Status::ST_BUFFER_ERROR;
		if (meshData->hasAnimation){
			if (!SetVertices(meshData->m_animVertices, meshData->m_numVerts, keepRawData)) return Status::ST_BUFFER_ERROR;
		}
		else{
			if (!SetVertices(meshData->m_vertices, meshData->m_numVerts, keepRawData)) return Status::ST_BUFFER_ERROR;
		}
	}

	return Resources::Status::ST_OK;
}

Resources::Mesh::~Mesh()
{
	EraseMeshData();
}

bool Resources::Mesh::SetVertices(Vertex * data, unsigned int numVerts, bool keepRawData)
{
	
	delete[] m_meshData.m_vertices;			m_meshData.m_vertices     = nullptr;
	delete[] m_meshData.m_animVertices; 	m_meshData.m_animVertices = nullptr;
	

	if (!Resources::SAFE_RELEASE(m_AnimVertBuffer))  Resources::OutputErrorString(this, std::string("could not release animBuffer")); return false;
	if (!Resources::SAFE_RELEASE(m_vertBuffer))		 Resources::OutputErrorString(this, std::string("could not release vertbuffer")); return false;


	D3D11_BUFFER_DESC bufferDesc;
	memset(&bufferDesc, 0, sizeof(bufferDesc));
	bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bufferDesc.Usage = D3D11_USAGE_DEFAULT;
	bufferDesc.ByteWidth = sizeof(Vertex)* numVerts;


	D3D11_SUBRESOURCE_DATA b_data;
	b_data.pSysMem = data;
	HRESULT hr;
	//hr = gDevice->CreateBuffer(&bufferDesc, &b_data, &m_vertBuffer);

	if (FAILED(hr))
		return false;

	if (keepRawData) m_meshData.m_vertices = data;
	else delete[] data; data = nullptr;
	
	
	return true;
}

bool Resources::Mesh::SetVertices(VertexAnim * data, unsigned int numVerts, bool keepRawData)
{
	if (numVerts = 0) return false;

	
	delete[] m_meshData.m_vertices;
	delete[] m_meshData.m_animVertices;
	m_meshData.m_vertices = nullptr;
	m_meshData.m_animVertices = nullptr;
	

	if (!Resources::SAFE_RELEASE(m_AnimVertBuffer))  Resources::OutputErrorString(this, std::string("could not release animBuffer")); return false;
	if (!Resources::SAFE_RELEASE(m_vertBuffer))		 Resources::OutputErrorString(this, std::string("could not release vertbuffer")); return false;

	D3D11_BUFFER_DESC bufferDesc;
	memset(&bufferDesc, 0, sizeof(bufferDesc));
	bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bufferDesc.Usage = D3D11_USAGE_DEFAULT;
	bufferDesc.ByteWidth = sizeof(VertexAnim)* numVerts;


	D3D11_SUBRESOURCE_DATA b_data;
	b_data.pSysMem = data;
	HRESULT hr;
	//hr = gDevice->CreateBuffer(&bufferDesc, &b_data, &m_AnimVertBuffer);



	if (FAILED(hr))
		return false;

	if (keepRawData) m_meshData.m_animVertices = data;
	else delete[] data; data = nullptr;

	m_meshData.hasAnimation = true;
	return true;

}

bool Resources::Mesh::SetIndices(unsigned int * indices, unsigned int numIndices, bool keepRawData)
{
	HRESULT hr;
	Resources::SAFE_RELEASE(m_indexBuffer);

	delete[] m_meshData.m_indices; m_meshData.m_indices = nullptr;

	
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

	if (keepRawData) m_meshData.m_indices = indices;
	else delete[] indices; indices = nullptr;

	return true;
}

std::shared_ptr<char> Resources::Mesh::GetDataAsBinary(size_t * size, bool * result)
{
	return std::shared_ptr<char>();
}

bool Resources::Mesh::EraseMeshData()
{
	delete[] m_meshData.m_animVertices;	 m_meshData.m_animVertices = nullptr;
	delete[] m_meshData.m_vertices;		 m_meshData.m_vertices	   = nullptr;
	delete[] m_meshData.m_indices;		 m_meshData.m_indices	   = nullptr;

	if (!Resources::SAFE_RELEASE(m_AnimVertBuffer))  Resources::OutputErrorString(this, std::string("could not release animBuffer")  ); return false;
	if (!Resources::SAFE_RELEASE(m_vertBuffer))		 Resources::OutputErrorString(this, std::string("could not release vertbuffer")  ); return false;
	if (!Resources::SAFE_RELEASE(m_indexBuffer))	 Resources::OutputErrorString(this, std::string("could not release Mindexbuffer")); return false;
	
	return true;
}

bool Resources::Mesh::SetMeshData(RawMeshData* newMeshData, bool keepRawData)
{
	if (!EraseMeshData()) Resources::OutputErrorString(this, std::string("could not erase MeshData"));
		return false;

		m_meshData.hasAnimation = newMeshData->hasAnimation;
		m_meshData.m_numIndices = newMeshData->m_numIndices;
		m_meshData.m_numVerts   = newMeshData->m_numVerts;

	if (newMeshData->hasAnimation)
		if (!SetVertices(newMeshData->m_animVertices, newMeshData->m_numVerts, keepRawData)) return false;
	else
		if (!SetVertices(newMeshData->m_vertices, newMeshData->m_numVerts,keepRawData)) return false;


	if (!SetIndices(m_meshData.m_indices, m_meshData.m_numIndices, keepRawData)) return false;


	return true;
}
