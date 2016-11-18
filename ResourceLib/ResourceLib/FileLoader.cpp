#include "FileLoader.h"
#include "FileHeaders.h"


Resources::FileLoader::FileLoader()
{
}


Resources::FileLoader * Resources::FileLoader::GetInstance()
{
	static FileLoader instance;
	return &instance;
}

Resources::FileLoader::~FileLoader()
{
}

Resources::Status Resources::FileLoader::LoadResource(unsigned int id, char * data, size_t * size)
{
	std::string path = std::string("pillar.BBF");
	std::ifstream infile;
	infile.open(path.c_str(), std::fstream::binary);

	MainHeader mainHeader;
	infile.read((char*)&mainHeader, sizeof(MainHeader));

	//size_t sizetoRead = sizeof(MeshHeader) + (sizeof(Mesh::Vertex) * meshHeader->vertices) + (sizeof(UINT) * meshHeader.indexLength);
	//data = new char[sizetoRead];
	infile.read(data, sizetoRead);

	return Resources::Status();
}
