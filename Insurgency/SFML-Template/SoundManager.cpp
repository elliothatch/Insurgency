#include "StdAfx.h"
#include "SoundManager.h"

SoundManager* s_SoundManager = NULL;

SoundManager::SoundManager(void)
{
}


SoundManager::~SoundManager(void)
{
}

SoundManager& SoundManager::getInstance(void)
{
	if(s_SoundManager == NULL)
	{
		s_SoundManager = new SoundManager();
		sf::SoundBuffer soundBufferNotFound;
		sf::Int16 sample[1] = {0};
		soundBufferNotFound.loadFromSamples(sample, 1, 1, 1);
		s_SoundManager->addSoundBuffer(soundBufferNotFound, "SOUNDBUFFERNOTFOUND");
	}
	return *s_SoundManager;
}

sf::SoundBuffer& SoundManager::getSoundBuffer(const std::string& soundBufferID)
{
	std::map<std::string, sf::SoundBuffer>::iterator soundBufferIt(m_soundBuffers.find(soundBufferID));
	if(soundBufferIt == m_soundBuffers.end())
	{
		printf("SOUND \"%s\" NOT FOUND\n", soundBufferID.c_str());
		return m_soundBuffers.at("SOUNDBUFFERNOTFOUND");
	}
		else
			return soundBufferIt->second;
}

const sf::SoundBuffer& SoundManager::getSoundBuffer(const std::string& soundBufferID) const
{
	std::map<std::string, sf::SoundBuffer>::const_iterator soundBufferIt(m_soundBuffers.find(soundBufferID));
	if(soundBufferIt == m_soundBuffers.end())
	{
		printf("SOUND \"%s\" NOT FOUND\n", soundBufferID.c_str());
		return m_soundBuffers.at("SOUNDBUFFERNOTFOUND");
	}
		else
			return soundBufferIt->second;
}

bool SoundManager::addSoundBuffer(const sf::SoundBuffer& soundBuffer, const std::string& soundBufferID)
{
	if(m_soundBuffers.size() > 0 && m_soundBuffers.find(soundBufferID) != m_soundBuffers.end())
	{
		printf("SOUND \"%s\" ALREADY REGISTERED\n", soundBufferID);
		return false;
	}
	m_soundBuffers[soundBufferID] = soundBuffer;
	return true;
}

bool SoundManager::addSoundBufferFromFile(const std::string& fileName, const std::string& soundBufferID)
{
	sf::SoundBuffer soundBuffer;
	if(soundBuffer.loadFromFile(fileName))
	{
		if(!addSoundBuffer(soundBuffer, soundBufferID))
		{
			printf("Failed to add \"%s\" to manager\n", fileName);
			return false;
		}
	}
	return true;
}

void SoundManager::removeSoundBuffer(const std::string& soundBufferID)
{
	m_soundBuffers.erase(soundBufferID);
}

void SoundManager::clearSoundBuffers(void)
{
	m_soundBuffers.clear();
}

void SoundManager::cleanup(void)
{
	if(s_SoundManager != NULL)
	{
		delete s_SoundManager;
		s_SoundManager = NULL;
	}
}