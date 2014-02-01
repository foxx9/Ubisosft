#include "engine.h"

#include "world.h"
#include "player.h"
#include "entity.h"

#include <SFML/Window.hpp>

namespace Client
{
	Engine *Engine::ms_instance = nullptr;



	bool Engine::Init()
	{
		m_isRunning = true;

		m_window = new sf::RenderWindow(sf::VideoMode(800, 600), "Change me to win 1 pts", sf::Style::Resize | sf::Style::Titlebar | sf::Style::Close);
		m_window->setVerticalSyncEnabled(true);

		// load data before world init
		m_ressourceManager.LoadTexture("data/emptycase.png");
		m_ressourceManager.LoadTexture("data/block.png");
		m_ressourceManager.LoadTexture("data/player-idle0.png");
		m_ressourceManager.LoadTexture("data/player-idle1.png");
		m_ressourceManager.LoadTexture("data/bomb0.png");
		m_ressourceManager.LoadTexture("data/bomb1.png");
		m_ressourceManager.LoadTexture("data/bomb2.png");
		m_ressourceManager.LoadTexture("data/explosion0.png");
		m_ressourceManager.LoadTexture("data/explosion1.png");
		m_ressourceManager.LoadTexture("data/explosion2.png");

		// world init
		m_world = new World(15, 13);
		m_world->Init();

		// add local player
		Player* localPlayer = new Player();
		localPlayer->Init();
		m_players.push_back(localPlayer);

		// spawn
		float x,y = 0.f;
		m_world->GetBlockToPixel(1, 1, x, y);
		localPlayer->SetPosition(x, y);

		return m_isRunning;
	}

	void Engine::ComputeScale()
	{
		assert(m_window);

		m_scaleFactor = (float)(m_window->getSize().x / m_window->getSize().y);
		
		m_world->ComputeScale();

		for(size_t i = 0; i < m_players.size(); ++i)
		{
			Player* player = m_players[i];
			player->ComputeScale();
		}
	}

	Player* Engine::GetLocalPlayer()
	{
		assert(m_players.size() >= 1);

		return m_players[0];
	}

	bool Engine::Tick()
	{
		if(m_window->isOpen())
		{
			sf::Event event;
			while (m_window->pollEvent(event))
			{
				// 
				if (event.type == sf::Event::Closed)
				{
					m_window->close();
				}
			}
		}
		else
		{
			m_isRunning = false;
		}

		// inputs
		float pos_x, pos_y;
		size_t block_x, block_y, next_x, next_y = 0;
		Player* player = GetLocalPlayer();
		player->GetPosition(pos_x, pos_y);

		m_world->GetPixelToBlock(pos_x, pos_y, block_x, block_y);

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			m_world->GetLeftBlock(block_x, block_y, next_x, next_y);

			if(m_world->IsBlockWalkable(next_x, next_y) && IsEntityWalkable(next_x, next_y))
			{
				m_world->GetBlockToPixel(next_x, next_y, pos_x, pos_y);
				player->SetTarget(pos_x, pos_y);
			}
		}
		else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			m_world->GetRightBlock(block_x, block_y, next_x, next_y);
			if(m_world->IsBlockWalkable(next_x, next_y) && IsEntityWalkable(next_x, next_y))
			{
				m_world->GetBlockToPixel(next_x, next_y, pos_x, pos_y);
				player->SetTarget(pos_x, pos_y);
			}
		}
		else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			m_world->GetUpBlock(block_x, block_y, next_x, next_y);
			if(m_world->IsBlockWalkable(next_x, next_y) && IsEntityWalkable(next_x, next_y))
			{
				m_world->GetBlockToPixel(next_x, next_y, pos_x, pos_y);
				player->SetTarget(pos_x, pos_y);
			}
		}
		else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
			m_world->GetDownBlock(block_x, block_y, next_x, next_y);
			if(m_world->IsBlockWalkable(next_x, next_y) && IsEntityWalkable(next_x, next_y))
			{
				m_world->GetBlockToPixel(next_x, next_y, pos_x, pos_y);
				player->SetTarget(pos_x, pos_y);
			}
		}
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		{
			// shoot
			player->SpawnBomb();
		}
		

		// game loop
		m_world->Tick();

		for(size_t i = 0; i < m_players.size(); ++i)
		{
			Player* player = m_players[i];
			player->Tick();
		}

		for(entities_t::iterator it = m_entities.begin(); it != m_entities.end(); ++it)
		{
			Entity* entity = (*it);
			entity->Tick();
		}

		// loop for destroy
		entities_t::iterator it_loop = m_entities.begin(); 
		while(it_loop != m_entities.end())
		{
			Entity* entity = (*it_loop);
			if(entity->CanDestroy())
			{
				Player* owner = entity->GetOwner();

				if(owner)
				{
					owner->DecBomb();
				}

				entity->Term();
				delete entity;

				it_loop = m_entities.erase(it_loop);
			}
			else
			{
				++it_loop;
			}
		}

		// draw
		Draw();

		return m_isRunning;
	}

	void Engine::AddEntity(Entity* entity)
	{
		m_entities.push_back(entity);
	}

	bool Engine::IsEntityWalkable(size_t x, size_t y)
	{
		bool is_walkable = true;

		float center_x, center_y = 0.f;
		m_world->GetBlockToPixel(x, y, center_x, center_y);

		// found entity present
		float entity_x, entity_y = 0.f;
		for(entities_t::iterator it = m_entities.begin(); it != m_entities.end(); ++it)
		{
			Entity* entity = (*it);
			entity->GetPosition(entity_x, entity_y);

			if(entity_x == center_x && entity_y == center_y)
			{
				// found an entity in the block
				is_walkable = entity->IsWalkable();

				break;
			}
		}

		return is_walkable;
	}

	bool Engine::IsEntityWalkable(float x, float y)
	{
		// center position
		size_t block_x, block_y = 0;
		m_world->GetPixelToBlock(x, y, block_x, block_y);
		return IsEntityWalkable(block_x, block_y);
	}

	bool Engine::Term()
	{
		delete m_window;
		m_window = nullptr;

		m_world->Term();
		delete m_world;
		m_world = nullptr;

		for(players_t::iterator it = m_players.begin(); it != m_players.end(); ++it)
		{
			Player* player = (*it);
			delete player;
		}
		m_players.clear();

		for(entities_t::iterator it = m_entities.begin(); it != m_entities.end(); ++it)
		{
			Entity* entity = (*it);
			delete entity;
		}
		m_entities.clear();

		m_isRunning = false;
		return m_isRunning;
	}

	void Engine::Draw()
	{
		m_window->clear(sf::Color::Black);

		// render world
		m_world->Draw(m_window);

		// render entities
		for(entities_t::iterator it = m_entities.begin(); it != m_entities.end(); ++it)
		{
			Entity* entity = (*it);
			entity->Draw(m_window);
		}

		// render characters
		for(size_t i = 0; i < m_players.size(); ++i)
		{
			Player* player = m_players[i];
			player->Draw(m_window);
		}

		m_window->display();
	}

	sf::RenderWindow* Engine::GetWindow()
	{
		return m_window;
	}

	RessourceManager* Engine::GetRessourceManager()
	{
		return &m_ressourceManager;
	}

	World* Engine::GetWorld()
	{
		return m_world;
	}

}