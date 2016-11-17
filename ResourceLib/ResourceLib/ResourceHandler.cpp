#include "ResourceHandler.h"



Resources::ResourceHandler::ResourceHandler()
{
	this->m_resources.reserve(30);
	this->m_models.reserve(30);
}


Resources::ResourceHandler::~ResourceHandler()
{
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



	/* Test */

	//Get id of the model from the level Instructions
	unsigned int id = 1337;
	//Make dataPtr variable
	char* data;
	//make a dataSize variable
	size_t size;

	// for each model in level

	std::unordered_map<unsigned int, ResourceContainer*>::const_iterator got = m_resources.find(id);
	if (got == m_resources.end()) // if the model does not exists in memory
	{
		//Load the model data from the file
		Status st = FakeLoadModel(id, data, &size);

		switch(st)
			case ST_OK:
		{

			unsigned int meshID = ((Model::RawModelData*)data)->meshId;
			std::unordered_map<unsigned int, ResourceContainer*>::const_iterator got = m_resources.find(meshID);
			if (got == m_resources.end()) // if the mesh does not exists in memory
			{
				char* meshData;
				size_t meshMsgSize;
				st = LoadResource(meshID, meshData, &meshMsgSize); //load the mesh


				break;
			}
		}
	}
	else
	{
		got->second->refCount += 1; //Add the reference count
	}


	return Resources::Status::ST_OK;
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

Resources::Status Resources::ResourceHandler::FakeLoadModel(unsigned int id, char * data, size_t* size)
{



	return Resources::Status();
}

Resources::Status Resources::ResourceHandler::LoadResource(unsigned int id, char * data, size_t * size)
{
	return Resources::Status();
}
