#include "MeshHandler.h"



Resources::MeshHandler::MeshHandler()
{

}

Resources::MeshHandler::MeshHandler(size_t meshAmount)
{
	this->m_emptyContainers.resize(meshAmount);
	this->m_meshes.reserve(meshAmount);
	this->m_containers.reserve(meshAmount);
	this->m_containers.insert(m_containers.begin(), meshAmount, Mesh());
	for (size_t i = 0; i < meshAmount; i++)
	{
		m_emptyContainers.push_back(&m_containers.at(i));
	}

}


Resources::MeshHandler::~MeshHandler()
{
}

Resources::Status Resources::MeshHandler::GetMesh(const unsigned int & id, ResourceContainer * meshPtr)
{


	std::unordered_map<unsigned int, ResourceContainer>::iterator got = m_meshes.find(id);
	if (got == m_meshes.end()) // if the model does not exists in memory
	{
		return Resources::Status::ST_RES_MISSING;
	}
	else
	{
		meshPtr = &got->second;
	}

	return Resources::Status::ST_OK;
}

Resources::Status Resources::MeshHandler::LoadMesh(char * data, size_t dataSize)
{


	//additional headers could be added here,
	Resource::RawResourceData* resData  = (Resource::RawResourceData*)data;
	Mesh::RawMeshData*		   meshData = (/*REPLACE with mesh header*/Mesh::RawMeshData*)(data + sizeof(Resource::RawResourceData));
	unsigned int*			   indices  = nullptr;
	
#ifdef DEBUG

	std::cout << "Loading new Mesh | ID : " << resData->m_id << std::endl;
#endif // DEBUG


	Mesh* newMesh = m_emptyContainers.front();		//Get an empty container
	newMesh->Create((Resource::RawResourceData*)data); //Initialize it with data

	if (meshData->hasAnimation)
	{
		Mesh::VertexAnim* vertices = (Mesh::VertexAnim*)((char*)meshData + sizeof(/*Replace with mesh header*/Mesh::RawMeshData));
		newMesh->SetVertices(vertices, meshData->m_numVerts);
		indices = (unsigned int*) ((char*)vertices + (sizeof(Mesh::VertexAnim)* meshData->m_numVerts));
	}
	else
	{
		Mesh::Vertex *vertices = (Mesh::Vertex*)((char*)meshData + sizeof(/*Replace with mesh header*/Mesh::RawMeshData));
		newMesh->SetVertices(vertices, meshData->m_numVerts);
		indices = (unsigned int*)((char*)vertices + (sizeof(Mesh::Vertex)* meshData->m_numVerts));
	}

	newMesh->SetIndices(indices, meshData->m_numIndices);

	m_meshes[resData->m_id] = ResourceContainer(newMesh, 1); // put it into the map
	m_emptyContainers.pop_front(); //remove from empty container queue;

	

	return Resources::Status::ST_OK;
}
