#include "StdAfx.h"
#include "SoundManager.h"

SoundManager* s_SoundManager = NULL;
sf::SoundBuffer* s_SoundBufferNotFound = NULL;

SoundManager::SoundManager(void)
{
}


SoundManager::~SoundManager(void)
{
	clearSoundBuffers();
}

SoundManager& SoundManager::getInstance(void)
{
	if(s_SoundManager == NULL)
	{
		s_SoundManager = new SoundManager();
		if(s_SoundBufferNotFound == NULL)
		{
			s_SoundBufferNotFound = new sf::SoundBuffer();
			sf::Int16 sample[1] = {0};
			s_SoundBufferNotFound->loadFromSamples(sample, 1, 1, 1);
		}
	}
	return *s_SoundManager;
}

sf::SoundBuffer& SoundManager::getSoundBuffer(const std::string& soundBufferID)
{
	std::map<std::string, sf::SoundBuffer*>::iterator soundBufferIt(m_soundBuffers.find(soundBufferID));
	if(soundBufferIt == m_soundBuffers.end())
	{
		printf("SOUND \"%s\" NOT FOUND\n", soundBufferID.c_str());
		return *s_SoundBufferNotFound;
	}
		else
			return *(soundBufferIt->second);
}

bool SoundManager::addSoundBuffer(sf::SoundBuffer* soundBuffer, const std::string& soundBufferID)
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
	sf::SoundBuffer* soundBuffer = new sf::SoundBuffer();
	if(soundBuffer->loadFromFile(fileName))
	{
		if(!addSoundBuffer(soundBuffer, soundBufferID))
		{
			printf("Failed to add \"%s\" to manager\n", fileName);
			delete soundBuffer;
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
	for(std::map<std::string, sf::SoundBuffer*>::iterator soundBufferIt(m_soundBuffers.begin()); 
		soundBufferIt != m_soundBuffers.end(); soundBufferIt++)
	{
		delete soundBufferIt->second;
	}
	m_soundBuffers.clear();
}

void SoundManager::cleanup(void)
{
	if(s_SoundManager != NULL)
	{
		delete s_SoundManager;
		s_SoundManager = NULL;
	}
	if(s_SoundBufferNotFound != NULL)
	{
		delete s_SoundBufferNotFound;
		s_SoundBufferNotFound = NULL;
	}
}