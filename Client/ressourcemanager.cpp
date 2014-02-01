#include "ressourcemanager.h"

#include "SFML/Graphics.hpp"

namespace Client
{

	RessourceManager::RessourceManager()
	{

	}

	RessourceManager::~RessourceManager()
	{

	}

	void RessourceManager::LoadTexture(const char* name)
	{
		unsigned long uniqueID = Shared::StringId(name).GetId();
		textures_t::iterator it = m_textures.find(uniqueID);

		if(it == m_textures.end())
		{
			sf::Texture *texture = new sf::Texture();
			texture->loadFromFile(name);

			m_textures[uniqueID] = texture;
		}
	}

	sf::Texture* RessourceManager::GetTexture(const char* name)
	{
		unsigned long uniqueID = Shared::StringId(name).GetId();
		return GetTexture(uniqueID);
	}

	sf::Texture* RessourceManager::GetTexture(unsigned long id)
	{
		sf::Texture* ret = nullptr;
		textures_t::iterator it = m_textures.find(id);

		if(it != m_textures.end())
		{
			ret = it->second;
		}

		return ret;
	}
	
}