#ifndef RESOURCELIB_FILELOADER_FILELOADER_H
#define RESOURCELIB_FILELOADER_FILELOADER_H
#include <fstream>
#include "Mesh.h"
#include "MemoryManager.h"
namespace Resources
{

	class FileLoader
	{
	private:
		static const size_t LEVEL_MEMORY	= 128; //kb
		static const size_t RESOURCE_MEMORY = 128; //kb
		MemoryManager mem_manager;
		FileLoader();
	public:
		static FileLoader* GetInstance();
		virtual ~FileLoader();
	
		Resources::Status LoadResource(const unsigned int& id, char*& data, size_t* size);
	};

}

#endif
