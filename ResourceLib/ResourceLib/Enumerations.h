#ifndef RESOURCELIB_ENUM_ENUM_H
#define RESOURCELIB_ENUM_ENUM_H

#include <d3d11.h>

namespace Resources
{

	enum ResourceType
	{
		RES_UNKOWN = -1,
		RES_TEXTURE = 0,
		RES_MATERIAL,
		RES_MESH,
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
		ST_MEM_FULL
	};

	static bool SAFE_RELEASE(IUnknown * dxBuffer)
	{

		if (dxBuffer != nullptr)
		{
			try {
				dxBuffer->Release();
			}
			catch (...)
			{
				return false;
			}
			dxBuffer = nullptr;
		}
		return true;

	}





}
#endif