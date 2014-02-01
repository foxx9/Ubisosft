#include "bomb.h"

#include "player.h"
#include "engine.h"
#include "world.h"
#include "explosion.h"

namespace Client
{
	Bomb::Bomb()
		: m_timeToExplode(0.0f)
		, m_distance(0)
		, m_isOver(false)
		, m_x(0.f)
		, m_y(0.f)
	{

	}

	Bomb::~Bomb()
	{

	}

	void Bomb::Init()
	{
		m_animator.AddFrame("idle", "data/bomb0.png", m_timeToExplode / 3.f);
		m_animator.AddFrame("idle", "data/bomb1.png", m_timeToExplode / 3.f);
		m_animator.AddFrame("idle", "data/bomb2.png", m_timeToExplode / 3.f);

		m_animator.ComputeScale();
		m_animator.Play("idle");

		m_deltaClock.restart();
	}

	void Bomb::Tick()
	{
		m_animator.Tick();

		if(m_deltaClock.getElapsedTime().asSeconds() >= m_timeToExplode)
		{
			// do the explosion effect
			Explode(m_x, m_y, m_distance, 0);

			m_isOver = true;
		}
	}

	void Bomb::Explode(float center_x, float center_y, size_t distance, int direction)
	{
		if(distance != 0)
		{
			World* world = Engine::GetInstance()->GetWorld();

			// current block
			size_t currentBlock_x, currentBlock_y = 0;
			world->GetPixelToBlock(center_x, center_y, currentBlock_x, currentBlock_y);

			// check if explode

			if(world->IsBlockWalkable(currentBlock_x, currentBlock_y))
			{
				// spawn an entity
				Explosion* explosion = new Explosion();
				explosion->SetPosition(center_x, center_y);
				explosion->SetOwner(nullptr);
				explosion->Init();

				Engine::GetInstance()->AddEntity(explosion);

				// propagate
				size_t nextBlock_x, nextBlock_y = 0;
				float next_x, next_y = 0.f;

				if(direction == 0 || direction == 1)
				{
					world->GetDownBlock(currentBlock_x, currentBlock_y, nextBlock_x, nextBlock_y);
					world->GetBlockToPixel(nextBlock_x, nextBlock_y, next_x, next_y);
					Explode(next_x, next_y, distance - 1, 1);
				}

				if(direction == 0 || direction == 2)
				{
					world->GetUpBlock(currentBlock_x, currentBlock_y, nextBlock_x, nextBlock_y);
					world->GetBlockToPixel(nextBlock_x, nextBlock_y, next_x, next_y);
					Explode(next_x, next_y, distance - 1, 2);
				}

				if(direction == 0 || direction == 3)
				{
					world->GetRightBlock(currentBlock_x, currentBlock_y, nextBlock_x, nextBlock_y);
					world->GetBlockToPixel(nextBlock_x, nextBlock_y, next_x, next_y);
					Explode(next_x, next_y, distance - 1, 3);
				}

				if(direction == 0 || direction == 4)
				{
					world->GetLeftBlock(currentBlock_x, currentBlock_y, nextBlock_x, nextBlock_y);
					world->GetBlockToPixel(nextBlock_x, nextBlock_y, next_x, next_y);
					Explode(next_x, next_y, distance - 1, 4);
				}
			}
			else if(world->IsBlockDestroyable(currentBlock_x, currentBlock_y))
			{
				// TODO : destruct block
			}
		}
	}

	void Bomb::Term()
	{

	}

	bool Bomb::CanDestroy()
	{
		return m_isOver;
	}

	Player*	Bomb::GetOwner()
	{
		return m_owner;
	}

	void Bomb::SetOwner(Player* player)
	{
		 m_owner = player;
	}

	void Bomb::SetTimeToExplode(float timeToExplode)
	{
		m_timeToExplode = timeToExplode;
	}

	void Bomb::SetDistance(size_t distance)
	{
		m_distance = distance;
	}

	void Bomb::SetPosition(float x, float y)
	{
		m_x = x;
		m_y = y;
	}

	void Bomb::GetPosition(float& x, float& y)
	{
		x = m_x;
		y = m_y;
	}

	void Bomb::Draw(sf::RenderWindow* window)
	{
		sf::Sprite* sprite = m_animator.GetCurrent();

		if(sprite)
		{
			sprite->setPosition(m_x, m_y);
			window->draw(*sprite);
		}		
	}


}