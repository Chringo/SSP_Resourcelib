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

Resources::Status Resources::MeshHandler::LoadMesh(const unsigned int & id, ResourceContainer * meshPtr)
{

	char* data;
	size_t dataSize;
	FileLoader::GetInstance()->LoadResource(id, data, &dataSize);
	
	//additional headers could be added here,
	Resource::RawResourceData* resData  = (Resource::RawResourceData*)data;
	MeshHeader* meshData = (MeshHeader*)(data + sizeof(Resource::RawResourceData));
	
	unsigned int*			   indices  = nullptr;
	
#ifdef _DEBUG
	std::cout << "Loading new Mesh | ID : " << resData->m_id << std::endl;
#endif // DEBUG


	Mesh* newMesh = m_emptyContainers.front();		//Get an empty container
	newMesh->Create((Resource::RawResourceData*)data); //Initialize it with data

	if (meshData->skeleton)
	{
		Mesh::VertexAnim* vertices = (Mesh::VertexAnim*)((char*)meshData + sizeof(MeshHeader));
		newMesh->SetVertices(vertices, meshData->numVerts);
		indices = (unsigned int*) ((char*)vertices + (sizeof(Mesh::VertexAnim)* meshData->numVerts));
	}
	else
	{
		Mesh::Vertex *vertices = (Mesh::Vertex*)((char*)meshData + sizeof(MeshHeader));
		newMesh->SetVertices(vertices, meshData->numVerts);
		indices = (unsigned int*)((char*)vertices + (sizeof(Mesh::Vertex)* meshData->numVerts));
	}

	if( !newMesh->SetIndices(indices, meshData->indexLength) ) return Status::ST_BUFFER_ERROR;

	m_meshes[id] = ResourceContainer(newMesh, 1); // put it into the map
	m_emptyContainers.pop_front(); //remove from empty container queue;

	meshPtr = &m_meshes[id];
	

	return Resources::Status::ST_OK;
}
