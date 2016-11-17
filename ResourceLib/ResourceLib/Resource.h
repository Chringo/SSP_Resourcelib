#ifndef RESOURCELIB_RESOURCE_RESOURCE_H
#define RESOURCELIB_RESOURCE_RESOURCE_H
#include "DefineHeader.h"
#include <memory>
#include <unordered_map>
#include <d3d11.h>

namespace Resources
{
	static bool SAFE_RELEASE(IUnknown * dxBuffer)
	{

		if (dxBuffer != nullptr)
		{
			try {
				dxBuffer->Release();
			}
			catch (...)
			{
				return false;
			}

			dxBuffer = nullptr;
		}
		return true;
	
	}
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
	

}

#endif

