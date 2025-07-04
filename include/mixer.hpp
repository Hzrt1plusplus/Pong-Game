// ---------------------------------------------- MIXER.HPP ----------------------------------------------
//                                                                                                        |
// The header file for definitions of classes for sound effects and bg music(if you have one you can add) |
//                                                                                                        |
// -------------------------------------------------------------------------------------------------------

#pragma once

// including sdl_mixer library 
#include <SDL2/SDL_mixer.h>
// including std cpp libraries 
#include <string>
#include <iostream>

// NOTE: NO NEED TO DEFINE A FUNCTION FOR INITIALIZING SDL_MIXER IN THERE OR IN SOURCE FILE BECAUSE 
// WE ALREADY HAVE INIT() METHOD IN PONG.HPP (TAKE A LOOK) 

// music class for bg music and etc...
class Music {
	public:
		Music(std::string);
		~Music();
		void Play(int);
		void Pause();
		void SetVolume(unsigned int);
	private:
		Mix_Music* music;
};

// effect class 
// for sound effects which are actually chunks 
class Effect {
	private:
		Mix_Chunk* effect;
	public:
		Effect(std::string);
		~Effect();
		void Play();
		void SetVolume(unsigned int);
};
