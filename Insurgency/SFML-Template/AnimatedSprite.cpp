#include "StdAfx.h"
#include "AnimatedSprite.h"


AnimatedSprite::AnimatedSprite(void)
	:sf::Drawable(), sf::Transformable(),
	m_numFrames(0), m_frameLength(1.0f/24.0f), m_totalLength(0),
	m_loop(false), m_playing(false), m_resetOnPlay(false),
	m_timer(), m_pauseTimer(), m_totalTimePaused(), m_frameTimeOffset(),
	m_color(sf::Color::White), m_spriteBlendMode(sf::BlendMultiply)
{
}

AnimatedSprite::AnimatedSprite(sf::Sprite initialFrame)
	:sf::Drawable(), sf::Transformable(),
	m_numFrames(0), m_frameLength(1.0f/24.0f), m_totalLength(0),
	m_loop(false), m_playing(false), m_resetOnPlay(false),
	m_timer(), m_pauseTimer(), m_totalTimePaused(), m_frameTimeOffset(),
	m_color(sf::Color::White), m_spriteBlendMode(sf::BlendMultiply)
{
	pushFrame(initialFrame);
	GotoFrame(0);
}

AnimatedSprite::~AnimatedSprite(void)
{
	clearFrames();
}

//drawing
void AnimatedSprite::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	if(m_sprites.size() == 0)
		return;
	states.transform *= getTransform();
	int currentFrame = getCurrentFrame();
	sf::Sprite& currentSprite = const_cast<sf::Sprite&>(getFrameSprite(currentFrame)); //this should always work
	//set the color
	//you're going to be using multiply 99% of the time
	switch(m_spriteBlendMode)
	{
	case sf::BlendAlpha:
		currentSprite.setColor(sf::Color(
			m_color.r*m_color.a + getFrameColor(currentFrame).r*(1-m_color.a), //red
			m_color.g*m_color.a + getFrameColor(currentFrame).r*(1-m_color.a), //green
			m_color.b*m_color.a + getFrameColor(currentFrame).r*(1-m_color.a), //blue
			m_color.a + getFrameColor(currentFrame).a)); //alpha
		break;
	case sf::BlendAdd:
		currentSprite.setColor(m_color + getFrameColor(currentFrame));
		break;
	case sf::BlendMultiply:
		currentSprite.setColor(m_color * getFrameColor(currentFrame));
		break;
	case sf::BlendNone:
		currentSprite.setColor(getFrameColor(currentFrame));
		break;
	}
	target.draw(currentSprite, states);
}

void AnimatedSprite::setColor(const sf::Color color)
{
	m_color = color;
}

const sf::Color AnimatedSprite::getColor(void) const
{
	return m_color;
}

void AnimatedSprite::setFrameColor(unsigned int frame, const sf::Color color)
{
	if(frame < m_numFrames)
	{
		m_spriteColors[frame] = color;
	}
}

const sf::Color AnimatedSprite::getFrameColor(unsigned int frame) const
{
	if(frame < m_numFrames)
	{
		return m_spriteColors.at(frame);
	}
	return sf::Color::White;
}

void AnimatedSprite::setSpriteBlendMode(const sf::BlendMode blendMode)
{
	m_spriteBlendMode = blendMode;
}

const sf::BlendMode AnimatedSprite::getSpriteBlendMode(void) const
{
	return m_spriteBlendMode;
}

sf::FloatRect AnimatedSprite::getLocalBounds(void) const
{
	if(m_numFrames > 0)
		return getCurrentSprite().getLocalBounds();
	else
		return sf::FloatRect();
}

sf::FloatRect AnimatedSprite::getGlobalBounds(void) const
{
	if(m_numFrames > 0)
		return getTransform().transformRect(getCurrentSprite().getGlobalBounds());
	else
		return sf::FloatRect();
}

void AnimatedSprite::Play(void)
{
	if(m_resetOnPlay)
	{
		Reset();
	}
	m_playing = true;
	//resume
	m_totalTimePaused += m_pauseTimer.getElapsedTime();
}

void AnimatedSprite::Pause(void)
{
	if(m_playing)
	{
	m_playing = false;
	m_resetOnPlay = false;
	
	m_pauseTimer.restart();
	}
}

void AnimatedSprite::Stop(void)
{
	
	if(m_playing)
	{
		m_playing = false;
		m_resetOnPlay = true;
		m_pauseTimer.restart();
	}
}

void AnimatedSprite::Reset(void)
{
	
	m_timer.restart();
	m_pauseTimer.restart();
	m_resetOnPlay = false;
	m_playing = false;
	m_totalTimePaused = sf::seconds(0);
	m_frameTimeOffset = sf::seconds(0);
	GotoFrame(0);
}

void AnimatedSprite::GotoFrame(unsigned int frame)
{
	int currentFrame;
	if(frame < m_numFrames)
		currentFrame = frame;
	else
		currentFrame = 0;
	//get cur frame without offset
	float timeElapsed = m_timer.getElapsedTime().asSeconds();
	float pauseElapsed = 0;
	if(!m_playing)
		pauseElapsed = m_pauseTimer.getElapsedTime().asSeconds();
	float adjustedTimeElapsed = timeElapsed - (m_totalTimePaused.asSeconds() + pauseElapsed) + m_frameTimeOffset.asSeconds();
	int lastFrame = int(adjustedTimeElapsed / m_frameLength) % m_numFrames; //note: last frame, not previous
	m_frameTimeOffset -= sf::seconds((lastFrame - currentFrame) * m_frameLength); //raw offset, won't start at beginning of next frame
}

void AnimatedSprite::NextFrame(void)
{
	m_frameTimeOffset += sf::seconds(m_frameLength); //raw offset
	/*
	float timeElapsed = m_timer.GetElapsedTime();
	float pauseElapsed = 0;
	if(!m_playing)
		pauseElapsed = m_pauseTimer.GetElapsedTime();
	float adjustedTimeElapsed = timeElapsed - (m_totalTimePaused + pauseElapsed);
	unsigned int lastFrame = int(adjustedTimeElapsed / m_frameLength) % m_numFrames; //note: last frame, not previous
	*/
}

void AnimatedSprite::PreviousFrame(void)
{
	m_frameTimeOffset -= sf::seconds(m_frameLength); //raw offset
	/*
	float timeElapsed = m_timer.GetElapsedTime();
	float pauseElapsed = 0;
	if(!m_playing)
		pauseElapsed = m_pauseTimer.GetElapsedTime();
	float adjustedTimeElapsed = timeElapsed - (m_totalTimePaused + pauseElapsed);
	unsigned int lastFrame = int(adjustedTimeElapsed / m_frameLength) % m_numFrames; //note: last frame, not previous
	*/
}

int AnimatedSprite::getCurrentFrame(void) const
{
	float timeElapsed = m_timer.getElapsedTime().asSeconds();
	float pauseElapsed = 0;
	if(!m_playing)
		pauseElapsed = m_pauseTimer.getElapsedTime().asSeconds();
	float adjustedTimeElapsed = timeElapsed - (m_totalTimePaused.asSeconds() + pauseElapsed) + m_frameTimeOffset.asSeconds();
	return int(adjustedTimeElapsed / m_frameLength) % m_numFrames;
}

void AnimatedSprite::pushFrame(sf::Sprite sprite)
{
	m_sprites.push_back(sprite);
	m_spriteColors.push_back(sprite.getColor());
	m_numFrames++;
}

void AnimatedSprite::insertFrame(sf::Sprite sprite, unsigned int frame)
{
	if(frame <= m_numFrames)
	{
		m_sprites.insert(m_sprites.begin() + frame, sprite);
		m_spriteColors.insert(m_spriteColors.begin() + frame, sprite.getColor());
		m_numFrames++;
	}
}

void AnimatedSprite::replaceFrame(sf::Sprite sprite, unsigned int frame)
{
	if(frame < m_numFrames)
	{
		m_sprites[frame] = sprite;
		m_spriteColors[frame] = sprite.getColor();
	}
}

void AnimatedSprite::removeFrame(unsigned int frame)
{
	if(frame < m_numFrames)
	{
		m_sprites.erase(m_sprites.begin() + frame);
		m_spriteColors.erase(m_spriteColors.begin() + frame);
		m_numFrames--;
	}
}

void AnimatedSprite::clearFrames(void)
{
	m_sprites.clear();
	m_spriteColors.clear();
	m_numFrames = 0;
}

const sf::Sprite& AnimatedSprite::getFrameSprite(unsigned int frame) const
{
	return m_sprites.at(frame);
}

const sf::Sprite& AnimatedSprite::getCurrentSprite(void) const
{
	return m_sprites.at(getCurrentFrame());
}

sf::Sprite& AnimatedSprite::getFrameSprite(unsigned int frame)
{
	return m_sprites.at(frame);
}

sf::Sprite& AnimatedSprite::getCurrentSprite(void)
{
	return m_sprites.at(getCurrentFrame());
}

void AnimatedSprite::setFramesPerSecond(int frameRate)
{
	m_frameLength = 1.0f/frameRate;
}

void AnimatedSprite::setFrameLength(float frameLength)
{
	m_frameLength = frameLength;
}

int AnimatedSprite::getFramesPerSecond(void) const
{
	return int(1.0f/m_frameLength);
}

float AnimatedSprite::getFrameLength(void) const
{
	return m_frameLength;
}

void AnimatedSprite::setLoop(bool b)
{
	m_loop = b;
}

bool AnimatedSprite::getLoop(void) const
{
	return m_loop;
}