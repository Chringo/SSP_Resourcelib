#include "Texture.h"



Resources::Texture::Texture() : Resource()
{
	m_resourceData.m_resType = ResourceType::RES_TEXTURE;
	m_filePath[0] = '\0';
}


Resources::Texture::~Texture()
{
	Destroy();
}

Resources::Texture::Texture(Resource::RawResourceData resData): Resource(resData)
{
	m_resourceData.m_resType = ResourceType::RES_TEXTURE;
}

Resources::Status Resources::Texture::Create(Resource::RawResourceData * resData)
{
	return Resources::Status();
}

Resources::Status Resources::Texture::Destroy()
{
	if (!Resources::SAFE_RELEASE(this->textureView))
		return Resources::Status::ST_BUFFER_ERROR;
	if (!Resources::SAFE_RELEASE(this->textureResource))
		return Resources::Status::ST_BUFFER_ERROR;

	m_filePath[0] = '\0';
	return Resources::Status::ST_OK;
}

Resources::Status Resources::Texture::SetTexture(ID3D11ShaderResourceView * view, ID3D11Resource * texture)
{
	Status st = Destroy();
	if (st == ST_OK)
	{

	}
	return Status::ST_OK;
}

std::shared_ptr<char> Resources::Texture::GetDataAsBinary(size_t * size, bool * result)
{
	return std::shared_ptr<char>();
}
