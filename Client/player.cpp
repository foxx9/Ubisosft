#include "player.h"

#include "engine.h"
#include "world.h"

#include "bomb.h"

#include <cassert>

namespace Client
{
	const float k_time_to_explode = 2.0f;

	Player::Player()
		: m_x(0.f)
		, m_y(0.f)
		, m_blockTarget_x(0)
		, m_blockTarget_y(0)
		, m_speed(10.0f)
		, m_direction_x(0.f)
		, m_direction_y(0.f)
		, m_bombDistance(3)
	{
		m_color = sf::Color::Magenta;
	}

	Player::~Player()
	{

	}

	void Player::Init()
	{
		m_maxBomb = 1;
		m_currentBomb = 0;
		m_bombDistance = 3;

		m_animator.Reset();

		// build animation

		m_animator.AddFrame("idle", "data/player-idle0.png", m_color, 0.4f);
		m_animator.AddFrame("idle", "data/player-idle1.png", m_color, 0.4f);


		m_animator.ComputeScale();
		m_animator.Play("idle");

		m_deltaClock.restart();
	}

	
	void Player::ComputeScale()
	{
		m_animator.ComputeScale();
	}

	void Player::SetTarget(float x, float y)
	{
		// move only if 
		// -opposite direction
		// -aligned on square

		float direction_x, direction_y = 0.f;

		if(x - m_x > 0)
		{
			direction_x = 1.0f;
		}
		else if(x - m_x < 0)
		{
			direction_x = -1.0f;
		}
		else
		{
			direction_x = 0.0f;
		}

		if(y - m_y > 0)
		{
			direction_y = 1.0f;
		}
		else if(y - m_y < 0)
		{
			direction_y = -1.0f;
		}
		else
		{
			direction_y = 0.0f;
		}

		if((m_blockTarget_x == m_x && m_blockTarget_y == m_y ) || (m_direction_y == -1*direction_y) || (m_direction_x == -1 * direction_x) )
		{
			m_direction_x = direction_x;
			m_direction_y = direction_y;

			m_blockTarget_x = x;
			m_blockTarget_y = y;
		}

	}

	void Player::GetPosition(float& x, float& y)
	{
		x = m_x;
		y = m_y;
	}

	void Player::SetPosition(float x, float y)
	{
		m_x = x;
		m_y = y;

		SetTarget(m_x, m_y);
	}

	void Player::SetColor(sf::Color color)
	{
		m_color = color;
		Init();
	}

	void Player::Tick()
	{
		m_animator.Tick();

		m_x = m_x + m_speed * m_deltaClock.getElapsedTime().asSeconds() * m_direction_x * m_speed;
		m_y = m_y + m_speed * m_deltaClock.getElapsedTime().asSeconds() * m_direction_y * m_speed;

		// check borne
		if(m_direction_x > 0 && m_x > m_blockTarget_x)
		{
			m_x = m_blockTarget_x;
		}
		else if(m_direction_x < 0 && m_x < m_blockTarget_x)
		{
			m_x = m_blockTarget_x;
		}

		if(m_direction_y > 0 && m_y > m_blockTarget_y)
		{
			m_y = m_blockTarget_y;
		}
		else if(m_direction_y < 0 && m_y < m_blockTarget_y)
		{
			m_y = m_blockTarget_y;
		}

		m_deltaClock.restart();
	}

	void Player::Term()
	{

	}

	bool Player::CanDestroy()
	{
		return false;
	}

	void Player::SpawnBomb()
	{
		if(m_currentBomb < m_maxBomb)
		{
			World* world = Engine::GetInstance()->GetWorld();
			assert(world);

			size_t block_x, block_y = 0;
			float spawn_x, spawn_y = 0.f;

			world->GetPixelToBlock(m_x, m_y, block_x, block_y);
			world->GetBlockToPixel(block_x, block_y, spawn_x, spawn_y);

			Bomb* bomb = new Bomb();
			bomb->SetPosition(spawn_x, spawn_y);
			bomb->SetDistance(m_bombDistance);
			bomb->SetTimeToExplode(k_time_to_explode);
			bomb->SetOwner(this);

			bomb->Init();
			Engine::GetInstance()->AddEntity(bomb);
			IncBomb();
		}
	}

	void Player::Draw(sf::RenderWindow* window)
	{
		sf::Sprite* sprite = m_animator.GetCurrent();

		if(sprite)
		{
			sprite->setPosition(m_x, m_y);
			window->draw(*sprite);
		}
	}

	void Player::IncMaxBomb()
	{
		++m_maxBomb;
	}

	void Player::IncBomb()
	{
		++m_currentBomb;
		assert(m_currentBomb <= m_maxBomb);
	}

	void Player::DecBomb()
	{
		assert(m_currentBomb > 0);
		--m_currentBomb;
	}

}