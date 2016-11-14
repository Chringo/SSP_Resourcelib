#ifndef RESOURCELIB_RESOURCE_RESOURCE_H
#define RESOURCELIB_RESOURCE_RESOURCE_H
#include "DefineHeader.h"
#include <unordered_map>


namespace Resources
{

	enum ResourceType
	{
		RES_UNKOWN  = - 1,
		RES_TEXTURE = 0,
		RES_MATERIAL,
		RES_MESH,
		RES_SKELETON,
		RES_SOUND,
		RES_LIGHT,
		RES_ANIMATION,
		RES_UI
	};

	class Resource
	{
	protected:
		struct RawResourceData
		{
			char m_name[256]; //change this variable in UML (when it works again) then delete this comment
			unsigned int m_id;
			ResourceType m_resType = RES_UNKOWN;
			// remove function in UML
		};
	
	private:
		Resource(); 
	protected:
		std::unordered_map<std::string, Resource*> m_connections;
		RawResourceData m_resourceData;

	public:
		Resource(RawResourceData data);
		virtual ~Resource();

		const bool IsType(ResourceType type) const;
		const ResourceType GetResourceType() const { return m_resourceData.m_resType; };

		const bool SetName(std::string name) ;
		const std::string GetName() const;

		const unsigned int GetId() const;
		
	
		virtual char * GetDataAsBinary(size_t* size, bool* result = nullptr) = 0;

		
		
	};
	

}

#endif

