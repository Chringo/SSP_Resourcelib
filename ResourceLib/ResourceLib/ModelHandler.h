#ifndef RESOURCELIB_MODELHANDLER_MODELHANDLER_H
#define RESOURCELIB_MODELHANDLER_MODELHANDLER_H
#include "Resource.h"
#include "Model.h"
#include "MeshHandler.h"
namespace Resources
{

	class ModelHandler
	{
	private:
		std::unordered_map<unsigned int, ResourceContainer> m_models;
		std::deque<Model*> m_emptyContainers;
		std::vector<Model> m_containers;

		MeshHandler m_meshHandler;

	public:
		Resources::Status GetModel( unsigned int& id, ResourceContainer *modelPtr);

		ModelHandler(size_t modelAmount);
		
		ModelHandler();
		Resources::Status LoadModel(char* data, size_t dataSize);
		virtual ~ModelHandler();
	};

}

#endif

