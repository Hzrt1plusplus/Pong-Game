// ---------------------------------------------- MIXER.CPP ---------------------------------------
//                                                                                                 |
//      contains definitions of music and effect class                                             |
//                                                                                                 |
// ------------------------------------------------------------------------------------------------

// starting with including header

#include <../include/mixer.hpp>

// constructor
Music::Music(std::string filepath){
	// load music 
	music = Mix_LoadMUS(filepath.c_str());
	// if fails, then log an error message 
	if(music == NULL)
		std::cout << "Error while loading sound! " << Mix_GetError() << '\n';

}
Music::~Music(){
	// free memory 
	Mix_FreeMusic(music);
}

void Music::Play(int loop)
{
	// if you want to play it as bg music, just pass -1 
	Mix_PlayMusic(music,loop);
}

// pauses music 
void Music::Pause() {
	Mix_PauseMusic();
}

// set music volume 
// values can be between 0 and 128
void Music::SetVolume(unsigned int volume)
{
	if(volume < 0 || volume > 127)
		return;
	Mix_VolumeMusic(volume);
}


Effect::Effect(std::string filepath)
{
	// load chunk 
	effect = Mix_LoadWAV(filepath.c_str());
	// if it fails, log and error message 
	if (effect == NULL)
		std::cout << "Error while loading sound effect! " << Mix_GetError() << '\n';
}
Effect::~Effect()
{
	// free memory 
	Mix_FreeChunk(effect);
}

void Effect::Play()
{
	// -1 for playing in first available music channel 
	// and 0 means play it once
	Mix_PlayChannel(-1,effect,0);
}

void Effect::SetVolume(unsigned int new_volume)
{
	// set volume of the chunk 
	Mix_VolumeChunk(effect,new_volume);
}

