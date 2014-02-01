#pragma once

#include "StringId.h"
#include <map>

namespace sf
{
	class Texture;
}

namespace Client
{

	class RessourceManager
	{
	public:
		RessourceManager();
		~RessourceManager();

		void LoadTexture(const char* name);

		sf::Texture* GetTexture(const char* name);
		sf::Texture* GetTexture(unsigned long id);

	protected:

		typedef std::map<unsigned long, sf::Texture*> textures_t;
		textures_t m_textures;


	};



}