#ifndef RESOURCELIB_MODEL_MODEL_H
#define RESOURCELIB_MODEL_MODEL_H
#include "Resource.h"
#include "Mesh.h"

namespace Resources {

	class Model :
		public Resource
	{
	public:
		struct RawModelData
		{
			unsigned int meshId;
			unsigned int materialId;
			
		};

	private:
		RawModelData* m_rawData = nullptr;
		Mesh* m_modelMesh;
		//Material* m_material;
		//Skeleton* m_skeleton;
	public:
		Model(Resource::RawResourceData resData);
		Model();
		virtual ~Model();
		Resources::Status Create(Resource::RawResourceData* resData, RawModelData* = nullptr,bool keepRawData = false);
		void SetMesh(Mesh* modelMesh) { this->m_modelMesh;};
		Mesh* GetMesh() const { return this->m_modelMesh; };

		virtual std::shared_ptr<char> GetDataAsBinary(size_t* size, bool* result = nullptr);

	};
}

#endif
