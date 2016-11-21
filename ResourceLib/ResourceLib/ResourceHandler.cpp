#include "ResourceHandler.h"



Resources::ResourceHandler::ResourceHandler()
{
	this->m_resources.reserve(30);

	this->m_modelHandler = new ModelHandler(20);
	
}


Resources::ResourceHandler::~ResourceHandler()
{

	delete m_modelHandler;
}

Resources::Status Resources::ResourceHandler::LoadLevel(unsigned int id)
{

	/*
		- Load level information,
		- Load all models that are in the level.
		- Construct the models, load resources if needed and add a reference counter to all the resources used in the model

		- Unload the last level, decrement the reference counterof all the resources.
		- if a reference counter hits 0, unload the resource
	

		Alternative, 
		- Unload last level first.
		- Then load the level
		- Then loop through the resources and check ref counting
	*/

	if (loadedLevel == id)
		return Resources::ST_LEVEL_ALREADY_LOADED;

	/* T e s t */

	// for each model in level
	{
		//Get id of the model from the level Instructions
		unsigned int id = 1337;
		
		ResourceContainer* modelPtr = nullptr;
		Status st;

		st = m_modelHandler->GetModel(id, modelPtr);
		switch (st)
		{
			case Resources::Status::ST_RES_MISSING:
			{
				//Load the model
				Status modelSt = m_modelHandler->LoadModel(id, modelPtr);
				if (modelSt != Status::ST_OK)
					return modelSt;
				break;

			}
			case Resources::Status::ST_OK:
				modelPtr->refCount += 1; //Add the reference count
				break;
		}

	}
	loadedLevel = id;
	return Resources::Status::ST_OK;
}


Resources::Status Resources::ResourceHandler::LoadMesh(unsigned int id, Mesh * meshPtr)
{
	char* meshData = nullptr;
	size_t dataSize;
	Status st = LoadResource(id, meshData, &dataSize);

	return Resources::Status();
}
void Resources::ResourceHandler::SetDeviceAndContext(ID3D11Device * device, ID3D11DeviceContext * context)
{
	this->m_device = device;
	this->m_context = context;
}

void Resources::ResourceHandler::SetDevice(ID3D11Device * device)
{
	this->m_device = device;
}

void Resources::ResourceHandler::SetContext(ID3D11DeviceContext * context)
{
	this->m_context = context;
}

Resources::Status Resources::ResourceHandler::GetResource(unsigned int id, Resource* resPtr) const
{
	std::unordered_map<unsigned int, ResourceContainer*>::const_iterator got = m_resources.find(id);
	if (got != m_resources.end())
	{
		resPtr = got->second->resource;
		return Resources::Status::ST_OK;
	}
	else
		return Resources::Status::ST_RES_MISSING;

}

Resources::Status Resources::ResourceHandler::GetModel(unsigned int id, Model* modelPtr) const
{

	std::unordered_map<unsigned int, ResourceContainer*>::const_iterator got = m_resources.find(id);
	if (got != m_resources.end())
	{
		if (got->second->resource->IsType(Resources::ResourceType::RES_MODEL))
			modelPtr = (Model*)got->second->resource;
		else
			return Resources::Status::ST_WRONG_RESTYPE;
	}
	else
	{
		return Resources::Status::ST_RES_MISSING;
		/*LOAD THE MODEL | Or return placeholder MODEL*/
	}
	return  Resources::Status::ST_OK;
}


Resources::Status Resources::ResourceHandler::LoadResource(unsigned int id, char * data, size_t * size)
{
	return Resources::Status();
}
