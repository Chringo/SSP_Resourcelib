#ifndef RESOURCELIB_ENUM_ENUM_H
#define RESOURCELIB_ENUM_ENUM_H

#include <d3d11.h>

namespace Resources
{
	enum Memory
	{
		MEM_LEVEL,
		MEM_RES,

		MEM_CHUNKS
	};
	enum ResourceType
	{
		RES_UNKOWN = -1,
		RES_TEXTURE = 0,
		RES_MATERIAL,
		RES_MESH,
		RES_MODEL,
		RES_SKELETON,
		RES_SOUND,
		RES_LIGHT,
		RES_ANIMATION,
		RES_UI
	};

	enum Status
	{
		ST_OK,
		ST_WRONG_RESTYPE,
		ST_RES_MISSING,
		ST_MEM_FULL,
		ST_BUFFER_ERROR,
		ST_LEVEL_ALREADY_LOADED,
		ST_DEVICE_MISSING,
		ST_ERROR_OPENING_FILE,
		ST_FILE_CLOSED
	};

	static bool SAFE_RELEASE(IUnknown* dxBuffer)
	{

 		if (dxBuffer != nullptr)
		{
			try {
				while (dxBuffer->Release()>0);
			}
			catch (...)
			{
				return false;
			}
			
		}
		return true;

	}





}
#endif