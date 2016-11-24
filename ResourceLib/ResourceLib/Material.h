#ifndef RESOURCELIB_MATERIAL_MATERIAL_H
#define RESOURCELIB_MATERIAL_MATERIAL_H
#include "Resource.h"

namespace Resources {
	
	class DLL_OPERATION Material :
		public Resource
	{

	private:
		/*Texture* m_Textures[5]*/
		float m_Metallic;
		float m_Roughness;
		float m_EmissiveValue;
	public:
		
		Material();
		virtual ~Material();
	};
}

#endif

