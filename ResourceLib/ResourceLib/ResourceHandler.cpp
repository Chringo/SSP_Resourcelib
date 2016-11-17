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

Resources::Model * Resources::ResourceHandler::GetModel(unsigned int id) const
{
	return nullptr;
}
