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

char * Resources::Entity::GetDataAsBinary(size_t * size, bool * result = nullptr)
{
	bool res;

	char* toReturn = new char[sizeof(RawEntityData) + sizeof(RawResourceData)];
	
	char* parentData = Resources::Resource::GetDataAsBinary(size,&res);
	if (res = true)
	{
	
		try {
			memcpy(toReturn, parentData, *size);
			memcpy(toReturn + *size, &m_EntityData, sizeof(RawEntityData));
		}
		catch (...)
		{
			delete toReturn;
			if (result != nullptr)
				*result = false;
		}
	
		*size += sizeof(RawEntityData);
	
		if (result != nullptr)
			*result = true;
		return toReturn;
	}
}
