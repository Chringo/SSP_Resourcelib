#ifndef RESOURCELIB_MODEL_MODEL_H
#define RESOURCELIB_MODEL_MODEL_H
#include "Entity.h"

namespace Resources {

	class Model :
		public Resources::Entity
	{
	public:
		Model();
		virtual ~Model();
	};
}

#endif
