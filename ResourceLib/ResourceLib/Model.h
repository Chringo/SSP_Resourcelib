#ifndef RESOURCELIB_MODEL_MODEL_H
#define RESOURCELIB_MODEL_MODEL_H
#include "Resource.h"

namespace Resources {

	class Model :
		public Resource
	{
	public:
		Model(Resource::RawResourceData resData);
	
		virtual ~Model();
	};
}

#endif
