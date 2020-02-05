#include "Sound.h"

Sound* Sound::soundInstance;

//Creates the sound engine instance
Sound::Sound()
{
	soundEngine = irrklang::createIrrKlangDevice();
}

//tells irrklang to clean up
Sound::~Sound()
{
	soundEngine->drop();
}

//if there's no other instance, creates a new one
Sound * Sound::CreateInstance()
{
	if (!soundInstance) {
		soundInstance = new Sound();
	}
	return soundInstance;
}

//returns the current instance
Sound * Sound::GetInstance()
{
	return soundInstance;
}

void Sound::Delete()
{
	delete soundInstance;
}

//finds the sound to play
void Sound::PlaySound(const char * sound)
{
	auto Iterator = sounds.find(sound);
	if (Iterator != sounds.end()) {
		soundEngine->play2D(Iterator->second);
	}
	else {
		irrklang::ISoundSource* source = soundEngine->addSoundSourceFromFile(sound);
		sounds.insert(std::pair<const char*, irrklang::ISoundSource*>(sound, source));
		soundEngine->play2D(source);
	}
}

//loads sounds
void Sound::LoadSound(const char * sound)
{
	auto Iterator = sounds.find(sound);
	if (Iterator != sounds.end()) {
		irrklang::ISoundSource* source = soundEngine->addSoundSourceFromFile(sound);
		sounds.insert(std::pair<const char*, irrklang::ISoundSource*>(sound, source));
	}
}
