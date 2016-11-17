#ifndef RESOURCELIB_RESOURCEHANDLER_RESOURCEHANDLER_H
#define RESOURCELIB_RESOURCEHANDLER_RESOURCEHANDLER_H

#include "Resource.h"

namespace Resources
{

	class ResourceHandler
	{
		struct ResourceContainer
		{
			unsigned int refCount = 0; // when this hits 0 unload from memory
			Resource* resource;
		};

	private:
		std::unordered_map<unsigned int, ResourceContainer*> m_resources;
		//Resources::Fileloader* m_fileLoader
		ID3D11Device* m_device		 = nullptr;
		ID3D11DeviceContext* m_context = nullptr;

	public:
		ResourceHandler();
		virtual ~ResourceHandler();
		/* Set */
		void SetDeviceAndContext(ID3D11Device* device, ID3D11DeviceContext* context);
		void SetDevice(ID3D11Device* device);
		void SetContext(ID3D11DeviceContext* context);
		/* Get */
		ID3D11Device* GetDevice() { return this->m_device; };
		ID3D11DeviceContext* GetContext() { return this->m_context; };


	};
}

#endif