#include "Model.h"



Resources::Model::Model(Resource::RawResourceData resData)
	:Resource(resData)
{
	m_resourceData.m_resType = RES_MODEL;
}


Resources::Model::~Model()
{
}
