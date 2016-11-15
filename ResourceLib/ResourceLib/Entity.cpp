#include "Entity.h"






Resources::Entity::Entity(Resource::RawResourceData resData, RawEntityData entityData)
	: Resource(resData)
{
	m_EntityData = entityData;
}

Resources::Entity::~Entity()
{
}

const bool Resources::Entity::IsEntityType(EntityType type) const
{
	return m_EntityData.m_entityType == type ? true : false;
}

const Resources::EntityType Resources::Entity::GetEntityType() const
{
	return m_EntityData.m_entityType;
}

std::shared_ptr<char> Resources::Entity::GetDataAsBinary(size_t * size, bool * result)
{
	bool res;

	std::shared_ptr<char> toReturn = std::shared_ptr<char> (new char[sizeof(RawEntityData) + sizeof(RawResourceData)]);
	
	std::shared_ptr<char> parentData = Resources::Resource::GetDataAsBinary(size,&res);

	if (res = true)
	{
	
		try {
			memcpy(toReturn.get(), parentData.get(), *size);
			memcpy(toReturn.get() + *size, &m_EntityData, sizeof(RawEntityData));
		}
		catch (...)
		{
			if (result != nullptr)
				*result = false;
			std::cout << "Error converting to binary :" << m_resourceData.m_name << std::endl;
			return nullptr;
		}
	
		*size += sizeof(RawEntityData);
	
		if (result != nullptr)
			*result = true;

		return toReturn;
	}

	return nullptr;
}
