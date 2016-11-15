#pragma once
#ifndef RESOURCELIB_MESH_MESH_H
#define RESOURCELIB_MESH_MESH_H

#include "Resource.h"

namespace Resources
{
	


	class Mesh :public Resources::Resource
	{
	
	public:

		struct Vertex
		{
			float position[3];
			float normal[3];
			float tangent[3];
			float uv[2];

		};
		struct VertexAnim
		{
			float position[3];
			float normal[3];
			float tangent[3];
			float uv[2];
			float weights[4];
			int influence[4];
		};
		struct RawMeshData {

			unsigned int  m_numVerts      = 0;
			unsigned int  m_numIndices    = 0;
			Vertex*       m_vertices	  = nullptr;
			VertexAnim*   m_animVertices  = nullptr;
			unsigned int* m_indices		  = nullptr;
			bool hasAnimation = false;

		};

		/*
		TODO: T�nk om detta.

		�ndra get vertices och indices till get buffers ist�llet? Raw data kan endast f�s genom binary. och raw datan h�lls i applikatoinen d�r det beh�vs ist�llet.
		*/

	protected:
		std::shared_ptr<RawMeshData>   m_meshData; // t�nk igenom detta!
		ID3D11Buffer* m_vertBuffer		= nullptr;
		ID3D11Buffer* m_AnimVertBuffer	= nullptr;
		ID3D11Buffer* m_indexBuffer		= nullptr;
	public:
		Mesh(Resource::RawResourceData resData, RawMeshData meshData);
		Mesh(Resource::RawResourceData resData);
		virtual ~Mesh();

		bool SetVertices(Vertex* data , unsigned int numVerts = 0);
		bool SetVertices(VertexAnim* data, unsigned int numVerts = 0);
		const Vertex* GetVertices() const { return m_meshData->m_vertices; };
		const VertexAnim* GetAnimVertices() const { return m_meshData->m_animVertices; };


		bool SetIndices(unsigned int* indices, unsigned int numIndices);
		const unsigned int* GetIndices() const    { return m_meshData.m_indices; };
		const unsigned int  GetNumIndices() const { return m_meshData.m_numIndices; };

		bool HasAnimation() { return m_meshData.hasAnimation; };

	};

}
#endif

