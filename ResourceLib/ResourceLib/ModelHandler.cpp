#include "ModelHandler.h"



Resources::Status Resources::ModelHandler::GetModel( unsigned int & id, ResourceContainer * modelPtr)
{


	std::unordered_map<unsigned int, ResourceContainer>::iterator got = m_models.find(id);
	if (got == m_models.end()) // if the model does not exists in memory
	{
		return Resources::Status::ST_RES_MISSING;
	}
	else
	{
		
		modelPtr = &got->second;
	}

	return Resources::Status::ST_OK;
}

Resources::ModelHandler::ModelHandler(size_t modelAmount)
{
	this->m_emptyContainers.resize(modelAmount);
	
	this->m_models.reserve(modelAmount);
	this->m_containers.reserve(modelAmount);
	this->m_containers.insert(m_containers.begin(), modelAmount, Model());

	for (size_t i = 0; i < modelAmount; i++)
	{
		m_emptyContainers.push_back(&m_containers.at(i));

	}
}

Resources::ModelHandler::ModelHandler()
{
}

Resources::Status Resources::ModelHandler::LoadModel(char * data, size_t dataSize)
{
	//additional headers could be added here,
	Model* newModel = m_emptyContainers.front();		//Get an empty container
	newModel->Create((Resource::RawResourceData*)data); //Initialize it with data
	
	m_models[((Resource::RawResourceData*)data)->m_id] = ResourceContainer(newModel,1); // put it into the map
 	m_emptyContainers.pop_front(); //remove from empty container queue

	unsigned int meshID = ((Model::RawModelData*)data)->meshId;


	Resources::Status st = Status::ST_OK;
	// st = MeshHandler->getMesh()

	//if it doesent exist
	switch(st)
		case Status::ST_RES_MISSING:
	{

		Mesh* meshPtr;
		st = LoadMesh(meshID, meshPtr); //load the mesh
		break;
	}
	
	return Resources::Status::ST_OK;
}


Resources::ModelHandler::~ModelHandler()
{
}
