#include "animator.h"


#include "StringId.h"
#include "engine.h"
#include "world.h"
#include "ressourcemanager.h"

#include <cassert>

namespace Client
{
	Animator::Animator()
		: m_currentFrame(nullptr)
		, m_currentAnimationID(0)
		, m_currentIndex(0)
	{
	}

	Animator::~Animator()
	{
		Reset();
	}

	void Animator::Reset()
	{
		m_animation.clear();

		m_currentFrame = nullptr;
		m_currentAnimationID = 0;
		m_currentIndex = 0;
	}

	void Animator::Play(const char* action)
	{
		unsigned long uniqueID = Shared::StringId(action).GetId();
		Play(uniqueID);
	}

	void Animator::Play(unsigned long action)
	{
		animations_t::iterator it = m_animation.find(action);

		if(it != m_animation.end())
		{
			frames_t& frames = it->second;

			m_currentAnimationID = action;
			m_currentIndex = 0;

			assert(frames.size() > 0);
			m_currentFrame = &frames[0];

			m_deltaClock.restart();
		}
	}

	void Animator::AddFrame(const char* action, const char* texture, float time)
	{
		unsigned long uniqueAction = Shared::StringId(action).GetId();
		unsigned long uniqueTexture = Shared::StringId(texture).GetId();

		AddFrame(uniqueAction, uniqueTexture, time);
	}

	void Animator::AddFrame(unsigned long action, unsigned long texture, float time)
	{
		RessourceManager* ressource = Engine::GetInstance()->GetRessourceManager();
		assert(ressource);

		sf::Texture* textureRessource = ressource->GetTexture(texture);
		assert(textureRessource);

		animations_t::iterator it = m_animation.find(action);
		if(it != m_animation.end())
		{

		}
		else
		{
			m_animation[action];
			it = m_animation.find(action);
		}

		frames_t& frames = it->second;

		struct Frame frame;
		frame.sprite.setTexture(*textureRessource, true);
		frame.time = time;

		frames.push_back(frame);
	}

	void Animator::AddFrame(const char* action, const char* texture, sf::Color& color, float time)
	{
		unsigned long uniqueAction = Shared::StringId(action).GetId();
		unsigned long uniqueTexture = Shared::StringId(texture).GetId();

		AddFrame(uniqueAction, uniqueTexture, color, time);
	}

	void Animator::AddFrame(unsigned long action, unsigned long texture, sf::Color& color, float time)
	{
		RessourceManager* ressource = Engine::GetInstance()->GetRessourceManager();
		assert(ressource);

		sf::Texture* textureRessource = ressource->GetTexture(texture);
		assert(textureRessource);

		animations_t::iterator it = m_animation.find(action);
		if(it != m_animation.end())
		{

		}
		else
		{
			m_animation[action];
			it = m_animation.find(action);
		}

		frames_t& frames = it->second;

		struct Frame frame;
		frame.sprite.setTexture(*textureRessource, true);
		frame.sprite.setColor(color);
		frame.time = time;

		frames.push_back(frame);
	}

	sf::Sprite*	Animator::GetCurrent()
	{
		return &m_currentFrame->sprite;
	}

	void Animator::ComputeScale()
	{
		sf::Vector2u screenSize = Engine::GetInstance()->GetWindow()->getSize();

		size_t world_x, world_y;
		Engine::GetInstance()->GetWorld()->GetSize(world_x, world_y);

		unsigned int base_x = screenSize.x / world_x;
		unsigned int base_y = screenSize.y / world_y;

		for(animations_t::iterator it = m_animation.begin(); it != m_animation.end(); ++it)
		{
			frames_t& frames = it->second;

			for(frames_t::iterator it_frame = frames.begin(); it_frame != frames.end(); ++it_frame)
			{
				struct Frame &frame = (*it_frame);
				sf::Vector2u textureSize = frame.sprite.getTexture()->getSize();
				float ratio_x = (float)base_x / textureSize.x;
				float ratio_y = (float)base_y / textureSize.y;

				frame.sprite.setScale(ratio_x, ratio_y);
				frame.sprite.setOrigin( (textureSize.x) / 2.f, (textureSize.x) / 2.f);
			}
		}
	}

	void Animator::Tick()
	{
		if(m_currentAnimationID != 0)
		{
			// get current frame
			//animations_t::iterator it = m_animation.find(m_currentAnimationID);

			if(m_deltaClock.getElapsedTime().asSeconds() > m_currentFrame->time)
			{
				// switch animation
				animations_t::iterator it = m_animation.find(m_currentAnimationID);

				if(it != m_animation.end())
				{
					frames_t& frames = it->second;

					if(m_currentIndex+1 < frames.size())
					{
						++m_currentIndex;
					}
					else
					{
						m_currentIndex = 0;
					}

					assert(frames.size() > 0);
					m_currentFrame = &frames[m_currentIndex];

					m_deltaClock.restart();
				}
			}
		}
	}


}