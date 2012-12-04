#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
class AnimatedSprite
	:public sf::Drawable, public sf::Transformable
{
public:
	AnimatedSprite(void);
	AnimatedSprite(sf::Sprite initialFrame);
	virtual ~AnimatedSprite(void);

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	//drawing
	void setColor(const sf::Color color);
	const sf::Color getColor(void) const;
	void setFrameColor(unsigned int frame, const sf::Color color);
	const sf::Color getFrameColor(unsigned int frame) const;
	void setSpriteBlendMode(const sf::BlendMode blendMode);
	const sf::BlendMode getSpriteBlendMode(void) const;
	sf::FloatRect getLocalBounds(void) const;
	sf::FloatRect getGlobalBounds(void) const;

	//animation
	void Play(void);
	void Pause(void);
	void Stop(void);
	void Reset(void);
	void GotoFrame(unsigned int frame);
	void NextFrame(void);
	void PreviousFrame(void);
	int getCurrentFrame(void) const;
	
	void setFramesPerSecond(int frameRate);
	void setFrameLength(float frameLength);
	int getFramesPerSecond(void) const;
	float getFrameLength(void) const;

	void pushFrame(sf::Sprite sprite);
	void insertFrame(sf::Sprite sprite, unsigned int frame);
	void replaceFrame(sf::Sprite sprite, unsigned int frame);
	void removeFrame(unsigned int frame);
	void clearFrames(void);
	const sf::Sprite& getFrameSprite(unsigned int frame) const;
	const sf::Sprite& getCurrentSprite(void) const;
	sf::Sprite& getFrameSprite(unsigned int frame);
	sf::Sprite& getCurrentSprite(void);

	void setLoop(bool b);
	bool getLoop(void) const;

protected:
	unsigned int m_numFrames;
	float m_frameLength;
	float m_totalLength;
	bool m_loop;
	bool m_playing;
	bool m_resetOnPlay;
	std::vector<sf::Sprite> m_sprites;
	sf::Clock m_timer;
	sf::Clock m_pauseTimer;
	sf::Time m_totalTimePaused;
	sf::Time m_frameTimeOffset;
	std::vector<sf::Color> m_spriteColors;
	sf::Color m_color;
	sf::BlendMode m_spriteBlendMode;

};
