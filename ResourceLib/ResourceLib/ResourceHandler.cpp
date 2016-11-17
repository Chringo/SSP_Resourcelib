#include "ResourceHandler.h"



Resources::ResourceHandler::ResourceHandler()
{
}


Resources::ResourceHandler::~ResourceHandler()
{
}

bool Resources::ResourceHandler::LoadLevel(unsigned int id)
{
	return false;
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

Resources::Resource * Resources::ResourceHandler::GetResource(unsigned int id) const
{
	return nullptr;
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
		/*LOAD THE MODEL*/
	}
	return  Resources::Status::ST_OK;
}
