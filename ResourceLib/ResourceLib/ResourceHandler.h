#ifndef RESOURCELIB_RESOURCEHANDLER_RESOURCEHANDLER_H
#define RESOURCELIB_RESOURCEHANDLER_RESOURCEHANDLER_H
#include "DefineHeader.h"
#include "Resource.h"
#include "Model.h"



namespace Resources
{

	class DLL_OPERATION ResourceHandler
	{
		struct ResourceContainer
		{
			unsigned int refCount = 0; // when this hits 0 unload from memory
			Resource* resource;
		};

	private:
		std::unordered_map<unsigned int, ResourceContainer*> m_resources;
		std::unordered_map<unsigned int, ResourceContainer*> m_models; //Second map for optimization
		//Resources::Fileloader* m_fileLoader
		ID3D11Device* m_device		   = nullptr;
		ID3D11DeviceContext* m_context = nullptr;

	public:
		ResourceHandler();
		virtual ~ResourceHandler();

		Resources::Status LoadLevel(unsigned int id);


		/* Set */
		void SetDeviceAndContext(ID3D11Device* device, ID3D11DeviceContext* context);
		void SetDevice(ID3D11Device* device);
		void SetContext(ID3D11DeviceContext* context);
		/* Get */
		ID3D11Device* GetDevice()			   const { return this->m_device; };
		ID3D11DeviceContext* GetContext()      const { return this->m_context; };
		Resources::Status  GetResource(unsigned int id, Resource* resPtr) const ;
		Resources::Status  GetModel(unsigned int id, Model* modelPtr) const;

	private:
		Resources::Status FakeLoadModel(unsigned int id, char* data, size_t* size); //For testing purposes!
		Resources::Status LoadResource(unsigned int id, char* data, size_t* size); //this should be in file loader later!
	};
}

#endif