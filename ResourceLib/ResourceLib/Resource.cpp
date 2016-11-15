#include "Resource.h"



Resources::Resource::Resource()
{


}

Resources::Resource::Resource(RawResourceData data)
{
	this->m_resourceData = data;
}


Resources::Resource::~Resource()
{
}

const bool Resources::Resource::IsType(ResourceType type) const
{
	return m_resourceData.m_resType == type ? true : false;
}

const bool Resources::Resource::SetName(std::string name) 
{
	try {

		memcpy(m_resourceData.m_name, name.c_str(), size_t(256));
	}
	catch (...)
	{
		std::cout << "Could change name " << m_resourceData.m_name << std::endl;
		return false;
	}
	return true;
}

const std::string Resources::Resource::GetName() const
{
	return std::string(m_resourceData.m_name);
}

const unsigned int Resources::Resource::GetId() const
{
	return m_resourceData.m_id;
}

std::shared_ptr<char> Resources::Resource::GetDataAsBinary(size_t* size, bool* result)
{
	*size = sizeof(RawResourceData);
	
	if (result != nullptr)
		*result = true;

	return std::shared_ptr<char>((char*)&m_resourceData);

}


