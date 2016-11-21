#include "ModelHandler.h"



Resources::Status Resources::ModelHandler::GetModel( unsigned int & id, ResourceContainer *& modelPtr)
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
		m_emptyContainers.at(i) = &m_containers.at(i);
	}
	
	this->m_meshHandler =  new MeshHandler(modelAmount);
}

Resources::ModelHandler::ModelHandler()
{
}

Resources::Status Resources::ModelHandler::LoadModel(unsigned int& id, ResourceContainer*& modelPtr)
{

	char* data	= nullptr;
	size_t size = 0;
	//FileLoader::GetInstance()->LoadResource(id, data, size);



	//additional headers could be added here,
	Model* newModel = m_emptyContainers.front();		//Get an empty container
	//newModel->Create((Resource::RawResourceData*)data); //Initialize it with data
	

	/*T E M P*/ 
	Resource::RawResourceData temp;
	temp.m_resType = RES_MODEL;
	temp.m_name[0] = 'p';
	temp.m_name[1] = '\0';
	temp.m_id = 1337;
	newModel->Create(&temp); //Initialize it with data
	/***************/

	m_models[1337/*((Resource::RawResourceData*)data)->m_id*/] = ResourceContainer(newModel,1); // put it into the map
 	m_emptyContainers.pop_front(); //remove from empty container queue

	unsigned int meshID = 124354234; // ((Model::RawModelData*)data)->meshId;
	Resources::ResourceContainer* meshPtr = nullptr;

	Resources::Status st = Status::ST_OK;

	st = m_meshHandler->GetMesh(meshID, meshPtr); //Get the mesh

	switch (st)
	{

		case Status::ST_RES_MISSING: //if it doesent exist
		{		
		 Status mSt= m_meshHandler->LoadMesh(meshID,meshPtr); //load the mesh
		 if (mSt != ST_OK)
			 return mSt;
			break;
		}
		case Status::ST_OK:
		{
			meshPtr->refCount += 1;
			
			break;
		}
	}
	newModel->SetMesh((Mesh*)meshPtr->resource);
	
	return Resources::Status::ST_OK;
}


Resources::Status Resources::ModelHandler::UnloadModel(unsigned int & id)
{
	ResourceContainer* modelRes;
	Status st = GetModel(id, modelRes);
	switch (st)
		case ST_OK:
		{
			modelRes->refCount -= 1;
			if (modelRes->refCount <= 0)
			{
				Model* mod = (Model*)modelRes->resource;
				Mesh* bla = mod->GetMesh();
				m_meshHandler->UnloadMesh(bla->GetId());
				//unload Material
				//unload skeleton
				mod->Destroy();
				m_models.erase(id);
				m_emptyContainers.push_back(mod);


			}
			break;
		}
	return Resources::Status();
}

Resources::ModelHandler::~ModelHandler()
{
	delete m_meshHandler;
}
