#pragma once
#include <SFML/Audio.hpp>
#include <map>
class SoundManager
{
protected:
	SoundManager(void);
public:
	~SoundManager(void);

	static SoundManager& getInstance(void);
	sf::SoundBuffer& getSoundBuffer(const std::string& soundBufferID);
	const sf::SoundBuffer& getSoundBuffer(const std::string& soundBufferID) const;
	bool addSoundBuffer(const sf::SoundBuffer& soundBuffer, const std::string& soundBufferID);
	bool addSoundBufferFromFile(const std::string& fileName, const std::string& soundBufferID);

	void removeSoundBuffer(const std::string& soundBufferID);
	void clearSoundBuffers(void);

	static void cleanup(void);

private:
	std::map<std::string, sf::SoundBuffer> m_soundBuffers;
};

