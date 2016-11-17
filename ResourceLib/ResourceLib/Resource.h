#ifndef RESOURCELIB_RESOURCE_RESOURCE_H
#define RESOURCELIB_RESOURCE_RESOURCE_H
#include "DefineHeader.h"
#include <memory>
#include <unordered_map>
#include "Enumerations.h"
#include <string>
namespace Resources
{

	


	class Resource
	{
	protected:
		struct RawResourceData
		{
			char m_name[256]; 
			unsigned int m_id;
			ResourceType m_resType = RES_UNKOWN;
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
		
	
		virtual std::shared_ptr<char> GetDataAsBinary(size_t* size, bool* result = nullptr) = 0;

		
		
	};
	

	static void OutputErrorString(Resource* object, std::string info = "")
	{
		std::cout << "Error in object :" << object->GetName() << "| Additional info : " << info << std::endl;
	}
}

#endif

