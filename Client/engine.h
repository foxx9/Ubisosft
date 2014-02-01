#pragma once

#include "ressourcemanager.h"

#include <cassert>
#include <vector>
#include <list>


namespace sf
{
	class RenderWindow;
}

namespace Client
{
	class World;
	class Player;
	class Entity;

	class Engine
	{
	public:

		bool				Init();
		bool				Tick();
		bool				Term();
		void				Draw();

		sf::RenderWindow*	GetWindow();
		RessourceManager*	GetRessourceManager();
		World*				GetWorld();

		void				ComputeScale();

		Player*				GetLocalPlayer();

		void				AddEntity(Entity* entity);
		bool				IsEntityWalkable(size_t x, size_t y);
		bool				IsEntityWalkable(float x, float y);

		// singleton
		static void Create()
		{
			assert(ms_instance == nullptr);
			ms_instance = new Engine();
		}

		static void Destroy()
		{
			assert(ms_instance != nullptr);
			delete ms_instance;
			ms_instance = nullptr;
		}

		static Engine* GetInstance()
		{
			return ms_instance;
		}
		//

	protected:
		bool				m_isRunning;
		float				m_scaleFactor;

		sf::RenderWindow*	m_window;
		World*				m_world;
		RessourceManager	m_ressourceManager;

		typedef std::vector<Player*> players_t;
		players_t			m_players;

		typedef std::list<Entity*> entities_t;
		entities_t			m_entities;

		// singleton
		static Engine*		ms_instance;
	};


}