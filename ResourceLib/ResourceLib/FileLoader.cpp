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

Resources::Status Resources::FileLoader::LoadResource(const unsigned int& id, char*& data, size_t * size)
{
	std::string path = std::string("pillar.BBF");
	std::ifstream infile;
	
	infile.open(path.c_str(), std::fstream::binary);
	if (!infile)
		return Status::ST_ERROR_OPENING_FILE;

	MainHeader mainHeader;
	infile.read((char*)&mainHeader, sizeof(MainHeader));

	MeshHeader meshHeader;
	
	infile.read((char*)&meshHeader, sizeof(MeshHeader));
	size_t sizetoRead = sizeof(Resource::RawResourceData)+ sizeof(MeshHeader) + (sizeof(Mesh::Vertex) * meshHeader.numVerts) + (sizeof(UINT) * meshHeader.indexLength);
	Resource::RawResourceData tempRes;
	tempRes.m_id = id;
	tempRes.m_name[0] = 'M';
	tempRes.m_resType = Resources::ResourceType::RES_MESH;
	
	data = new char[sizetoRead];

	memcpy((char*)data, (char*)&tempRes, sizeof(Resource::RawResourceData));
	memcpy((char*)data + sizeof(Resource::RawResourceData), (char*)&meshHeader, sizeof(MeshHeader));

	UINT offset = sizeof(Resource::RawResourceData) + sizeof(MeshHeader);
	infile.read(data + offset, sizetoRead);

	return Resources::Status::ST_OK;
}
