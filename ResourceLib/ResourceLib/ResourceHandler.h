#ifndef RESOURCELIB_RESOURCEHANDLER_RESOURCEHANDLER_H
#define RESOURCELIB_RESOURCEHANDLER_RESOURCEHANDLER_H
#include "DefineHeader.h"
#include "ModelHandler.h"
#include "MemoryManager.h"

namespace Resources
{

	class DLL_OPERATION ResourceHandler
	{
		

	private:
		std::unordered_map<unsigned int, ResourceContainer*> m_resources;
		//Resources::Fileloader* m_fileLoader
		ModelHandler* m_modelHandler   = nullptr;

		ID3D11Device* m_device		   = nullptr;
		ID3D11DeviceContext* m_context = nullptr;

		unsigned int loadedLevel = 0;
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
		Resources::Status LoadMesh(unsigned int id,  Mesh* meshPtr);
		Resources::Status LoadResource(unsigned int id, char* data, size_t* size); //this should be in file loader later!
	};
}

#endif