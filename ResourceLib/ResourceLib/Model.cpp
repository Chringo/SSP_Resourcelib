#include "Model.h"



Resources::Model::Model(Resource::RawResourceData resData)
	:Resource(resData)
{
	m_resourceData.m_resType = RES_MODEL;
}

Resources::Model::Model() : Resource()
{
	m_resourceData.m_resType = RES_MODEL;
}


Resources::Model::~Model()
{
	delete m_rawData;
}

Resources::Status Resources::Model::Create(Resource::RawResourceData* resData, RawModelData* modelData , bool keepRawData)
{
	m_resourceData = *resData;
	m_resourceData.m_resType = RES_MODEL;
	if (keepRawData && modelData != nullptr)
		delete m_rawData; m_rawData = new RawModelData; *m_rawData = *modelData;
	return Resources::Status();
}

std::shared_ptr<char> Resources::Model::GetDataAsBinary(size_t * size, bool * result)
{
	return std::shared_ptr<char>();
}
