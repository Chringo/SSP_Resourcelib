#ifndef RESOURCELIB_MESHHANDLER_MESHHANDLER_H
#define RESOURCELIB_MESHHANDLER_MESHHANDLER_H
#include "Mesh.h"
namespace Resources
{

	class MeshHandler
	{

	private:
		std::unordered_map<unsigned int, ResourceContainer> m_meshes;
		std::deque<Mesh*> m_emptyContainers;
		std::vector<Mesh> m_containers;
	public:
		MeshHandler();
		MeshHandler(size_t meshAmount);
		virtual ~MeshHandler();

		Resources::Status GetMesh(const unsigned int& id, ResourceContainer* modelPtr);
		Resources::Status LoadMesh(char* data, size_t dataSize);
	};
}

#endif

