#include "TextureHandler.h"



Resources::TextureHandler::TextureHandler()
{
}


Resources::TextureHandler::TextureHandler(size_t textureAmount, ID3D11Device * device)
{
	this->m_emptyContainers.resize(textureAmount);

	this->m_textures.reserve(textureAmount);
	this->m_containers.reserve(textureAmount);
	this->m_containers.insert(m_containers.begin(), textureAmount, Texture());
	for (size_t i = 0; i < textureAmount; i++)
	{
		m_emptyContainers.at(i) = &m_containers.at(i);
	}


	if (device != nullptr) {
		this->m_device = device;
	}

}

Resources::TextureHandler::~TextureHandler()
{
}

Resources::Status Resources::TextureHandler::GetTexture(const unsigned int & id, ResourceContainer *& texturePtr)
{
	std::unordered_map<unsigned int, ResourceContainer>::iterator got = m_textures.find(id);
	if (got == m_textures.end()) { // if the texture does not exists in memory

		return Resources::Status::ST_RES_MISSING;
	}
	else {
		texturePtr = &got->second;
	}

	return Resources::Status::ST_OK;
}

Resources::Status Resources::TextureHandler::LoadTexture(const unsigned int & id, ResourceContainer *& texturePtr)
{
	char* data = nullptr;
	size_t size = 0;
	
	Status st = FileLoader::GetInstance()->LoadResource(id, data, &size);
	if (st != ST_OK)
		return st;

	Resource::RawResourceData* resData = (Resource::RawResourceData*)data;
	if (resData->m_resType != RES_TEXTURE)
	{
#ifdef _DEBUG
		std::cout << "Wrong resource type. Wanted Texture, got type: " << resData->m_id << std::endl;
#endif // _DEBUG

		return ST_WRONG_RESTYPE;
	}
	
	TextureHeader* texData = (TextureHeader*)(data + sizeof(Resource::RawResourceData));
	Texture* newTexture = m_emptyContainers.front(); //Get an empty container


	/*
	
			LOAD DDS TEXTURE AND CREATE DIRECTX STUFF HERE THEN ADD TO TEXTURE
	*/

	st = newTexture->Create(resData);

	 if (st != ST_OK)
		 return st;

     /*T E M P*/
	Resource::RawResourceData temp;
	temp.m_resType = RES_TEXTURE;
	temp.m_name[0] = 'T';
	temp.m_name[1] = 'E';
	temp.m_name[2] = 'X';
	temp.m_name[3] = '\0';
	temp.m_id = 7869;
	newTexture->Create(&temp);   //Initialize it with data
	/***************/

	newTexture->
	m_textures[newTexture->GetId()] = ResourceContainer(newTexture, 1); //put it into the map
	m_emptyContainers.pop_front();



		return Resources::Status();
}

Resources::Status Resources::TextureHandler::UnloadTexture(const unsigned int & id)
{
	return Resources::Status();
}

Resources::Texture * Resources::TextureHandler::GetPlaceHolderTexture()
{
	if (this->placeHolder == nullptr)
	{
		CreatePlaceHolder();
	}
	return placeHolder;
}

bool Resources::TextureHandler::CreatePlaceHolder()
{
	return false;
}

void Resources::TextureHandler::SetDevice(ID3D11Device * device)
{
}
