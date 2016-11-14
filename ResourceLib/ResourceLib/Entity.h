#ifndef RESOURCELIB_ENTITY_ENTITY_H
#define RESOURCELIB_ENTITY_ENTITY_H
#include "Resource.h"

namespace Resources
{
	enum EntityType
	{
		ENTITY_UNKNOWN  = -1,
		ENTITY_MESH		= 0,
		ENTITY_LIGHT,
		ENTITY_CAMERA
	};

	class Entity : public Resource
	{

	protected:
		struct RawEntityData
		{
			EntityType m_entityType = ENTITY_UNKNOWN;
			//Change this struct in the UML (when it works) and remove this comment
		};
		RawEntityData m_EntityData;


	public:
		Entity(Resource::RawResourceData resData, RawEntityData entityData );
		virtual ~Entity();

		const bool IsEntityType(EntityType type) const;
		const EntityType GetEntityType() const;

		virtual char* GetDataAsBinary(size_t* size, bool* result = nullptr);

	};
}

#endif

