#pragma once
#include <irrKlang.h>
#include <map>

class Sound
{
protected:
	Sound();
	~Sound();
public:
	static Sound* CreateInstance();
	static Sound* GetInstance();
	static void Delete();
	void PlaySound(const char* sound);
	void LoadSound(const char* sound);
private:
	static Sound* soundInstance;
	irrklang::ISoundEngine* soundEngine = nullptr;
	std::map<const char*, irrklang::ISoundSource*> sounds;
};

