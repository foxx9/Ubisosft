#include "world.h"
#include "engine.h"
#include "ressourcemanager.h"

#include <cassert>

namespace Client
{
	World::World(size_t x, size_t y)
		: m_x(x)
		, m_y(y)
	{

	}

	World::~World()
	{

	}

	void World::Init()
	{
		RessourceManager* ressource = Engine::GetInstance()->GetRessourceManager();

		sf::Texture* emptyCase = ressource->GetTexture("data/emptycase.png");
		sf::Texture* block = ressource->GetTexture("data/block.png");

		assert(emptyCase);

		// generate world
		for(size_t i = 0; i < (m_x*m_y); ++i)
		{
			struct Cell cell;
			GetCoordinatesFromVector(i, cell.x, cell.y);

			if(cell.x == 0 || cell.x == m_x-1 || cell.y == 0 || cell.y == m_y-1 || (cell.x % 2 == 0 && cell.y % 2 == 0))
			{
				cell.sprite.setTexture(*block, true);
				cell.isWalkable = false;
				cell.isDestroyable = false;
			}
			else
			{
				cell.sprite.setTexture(*emptyCase, true);
				cell.isWalkable = true;
				cell.isDestroyable = false;
			}
			
			cell.sprite.setPosition((float)(cell.x*emptyCase->getSize().x), (float)(cell.y*emptyCase->getSize().y));
			
			m_cells.push_back(cell);
		}

		ComputeScale();
	}

	void World::Tick()
	{

	}

	void World::Term()
	{
		m_cells.clear();
	}

	void World::ComputeScale()
	{
		sf::Vector2u screenSize = Engine::GetInstance()->GetWindow()->getSize();

		unsigned int base_x = screenSize.x / m_x;
		unsigned int base_y = screenSize.y / m_y;

		for(size_t i = 0; i < (m_x*m_y); ++i)
		{
			struct Cell& cell = m_cells[i];

			sf::Vector2u textureSize = cell.sprite.getTexture()->getSize();

			// ratio
			float ratio_x = (float)base_x / textureSize.x;
			float ratio_y = (float)base_y / textureSize.y;

			cell.sprite.setScale(ratio_x, ratio_y);
			//cell.sprite.setOrigin(textureSize.x * ratio_x / 2.f, textureSize.y * ratio_y / 2.f);
			cell.sprite.setPosition((float)(cell.x*textureSize.x * ratio_x), (float)(cell.y*textureSize.y * ratio_y));
		}
	}

	void World::GetCoordinatesFromVector(size_t i, size_t& x, size_t& y)
	{
		y = i / m_x;
		x = i % m_x;
	}

	void World::Draw(sf::RenderWindow* window)
	{
		for(size_t i = 0; i < (m_x*m_y); ++i)
		{
			struct Cell& cell = m_cells[i];

			window->draw(cell.sprite);
		}
	}

	void World::GetSize(size_t& x, size_t& y)
	{
		x = m_x;
		y = m_y;
	}

	void World::GetPixelToBlock(float x, float y, size_t& x_out, size_t& y_out)
	{
		sf::Vector2u screenSize = Engine::GetInstance()->GetWindow()->getSize();

		unsigned int base_x = screenSize.x / m_x;
		unsigned int base_y = screenSize.y / m_y;

		float delta_x = x / base_x;
		float delta_y = y / base_y;

		x_out = (size_t)delta_x;
		y_out = (size_t)delta_y;
	}

	void World::GetBlockToPixel(size_t x, size_t y, float& x_out, float& y_out)
	{
		sf::Vector2u screenSize = Engine::GetInstance()->GetWindow()->getSize();

		unsigned int base_x = screenSize.x / m_x;
		unsigned int base_y = screenSize.y / m_y;

		x_out = (float)(x * base_x) + base_x / 2.0f;
		y_out = (float)(y * base_y) + base_y / 2.0f;
	}

	bool World::IsBlockWalkable(float x, float y)
	{
		size_t x_block, y_block;
		GetPixelToBlock(x, y, x_block, y_block);

		return IsBlockWalkable(x_block, y_block);
	}

	bool World::IsBlockWalkable(size_t x, size_t y)
	{
		assert(x * y < m_cells.size());
		struct Cell& cell = m_cells[m_x * y + x];
		return cell.isWalkable;
	}

	bool World::IsBlockDestroyable(size_t x, size_t y)
	{
		assert(x * y < m_cells.size());
		struct Cell& cell = m_cells[m_x * y + x];
		return cell.isDestroyable;
	}

	bool World::IsBlockDestroyable(float x, float y)
	{
		size_t x_block, y_block;
		GetPixelToBlock(x, y, x_block, y_block);

		return IsBlockDestroyable(x_block, y_block);
	}

	void World::GetUpBlock(size_t x, size_t y, size_t& x_out, size_t& y_out)
	{
		x_out = x;

		if(y >= 1)
		{
			y_out = y - 1;
		}
		else
		{
			y_out = y;
		}
	}

	void World::GetDownBlock(size_t x, size_t y, size_t& x_out, size_t& y_out)
	{
		x_out = x;

		if(y + 1 < m_y)
		{
			y_out = y + 1;
		}
		else
		{
			y_out = y;
		}
	}

	void World::GetLeftBlock(size_t x, size_t y, size_t& x_out, size_t& y_out)
	{
		y_out = y;

		if(x >= 1)
		{
			x_out = x - 1;
		}
		else
		{
			x_out = x;
		}
	}

	void World::GetRightBlock(size_t x, size_t y, size_t& x_out, size_t& y_out)
	{
		y_out = y;

		if(x + 1 < m_x)
		{
			x_out = x + 1;
		}
		else
		{
			x_out = x;
		}
	}
}