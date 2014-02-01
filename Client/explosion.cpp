#include "explosion.h"


namespace Client
{
	Explosion::Explosion()
		: m_x(0.f)
		, m_y(0.f)
		, m_owner(nullptr)
		, m_timeToExplode(0.5f)
		, m_isOver(false)
	{

	}

	Explosion::~Explosion()
	{

	}

	void Explosion::Init()
	{
		m_animator.AddFrame("idle", "data/explosion0.png", m_timeToExplode / 3.f);
		m_animator.AddFrame("idle", "data/explosion1.png", m_timeToExplode / 3.f);
		m_animator.AddFrame("idle", "data/explosion2.png", m_timeToExplode / 3.f);

		m_animator.ComputeScale();
		m_animator.Play("idle");

		m_deltaClock.restart();
	}

	void Explosion::Tick()
	{
		m_animator.Tick();

		if(m_deltaClock.getElapsedTime().asSeconds() >= m_timeToExplode)
		{
			m_isOver = true;
		}
	}

	void Explosion::Term()
	{

	}

	void Explosion::Draw(sf::RenderWindow* window)
	{
		sf::Sprite* sprite = m_animator.GetCurrent();

		if(sprite)
		{
			sprite->setPosition(m_x, m_y);
			window->draw(*sprite);
		}		
	}

	Player*	Explosion::GetOwner()
	{
		return m_owner;
	}

	void Explosion::SetOwner(Player* player)
	{
		m_owner = player;
	}

	bool Explosion::CanDestroy()
	{
		return m_isOver;
	}

	void Explosion::SetPosition(float x, float y)
	{
		m_x = x;
		m_y = y;
	}

	void Explosion::GetPosition(float& x, float& y)
	{
		x = m_x;
		y = m_y;
	}


}