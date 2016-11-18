#ifndef RESOURCELIB_FILELOADER_FILELOADER_H
#define RESOURCELIB_FILELOADER_FILELOADER_H
#include <fstream>
#include "Mesh.h"
namespace Resources
{

	class FileLoader
	{
		FileLoader();
	public:
		static FileLoader* GetInstance();
		virtual ~FileLoader();
	
		Resources::Status LoadResource(unsigned int id, char* data, size_t* size);
	};

}

#endif
