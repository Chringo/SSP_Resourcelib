#include "ModelHandler.h"



Resources::Status Resources::ModelHandler::GetModel(const unsigned int & id, ResourceContainer * modelPtr)
{


	std::unordered_map<unsigned int, ResourceContainer*>::const_iterator got = m_models.find(id);
	if (got == m_models.end()) // if the model does not exists in memory
	{
		return Resources::Status::ST_RES_MISSING;
	}
	else
	{
		modelPtr->resource = got->second;
	}

	return Resources::Status();
}

Resources::ModelHandler::ModelHandler(size_t modelAmount)
{
	this->m_emptyContainers.resize(modelAmount);
	
	this->m_models.reserve(modelAmount);
	this->m_instances.reserve(modelAmount);
	this->m_instances.insert(m_instances.begin(), modelAmount, Model());
}

Resources::ModelHandler::ModelHandler()
{
}


Resources::ModelHandler::~ModelHandler()
{
}
