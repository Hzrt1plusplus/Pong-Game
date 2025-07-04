// pong.hpp 
// this is a header file for Pong game which contains class and function definitions for game  

#ifndef PONG_HPP
#define PONG_HPP

// including c++ libraries 
#include <string>
#include <iostream>
#include <cmath>
#include <cstdlib>
#include <ctime>
// third part libs 
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_ttf.h"
#include "SDL2/SDL_mixer.h"

// macros 
#define RED {255,0,0}
#define BLUE {0,0,255}
#define GREEN {0,255,0}
#define WHITE {255,255,255}
#define BLACK {0,0,0}
#define SCREEN_H 650
#define SCREEN_W 900
#define PLAYER_SPEED 40
#define BALL_SPEED 10
#define LEFTSTART_X 0
#define BALLSIZE 50
#define PADDLE_W  40 
#define PADDLE_H  200
#define FPS 60
#define FONTSIZE 30
#define LINESTARTY 0
#define SCORE_L_X  (SCREEN_W*10/100)
#define SCORE_R_X  (SCREEN_W/2+SCORE_L_X)
#define SCOREBOX_Y  20
#define SCOREBOX_W  (SCREEN_W*40/100)-30
#define SCOREBOX_H  40
#define LEFTSTART_Y (SCREEN_H - PADDLE_H)/2
#define RIGHTSTART_X (SCREEN_W - PADDLE_W)
#define RIGHTSTART_Y (SCREEN_H - PADDLE_H)/2 
#define BALL_STARTX (SCREEN_W - BALLSIZE)/2
#define BALL_STARTY (SCREEN_H - BALLSIZE)/2
#define LINESTARTX (SCREEN_W/2)
#define OFFSET_W 10 

// an initializer function for initializing all libraries 
void INIT();

// main game class which is accountant about rendering and other stuff 
// and this class is a singleton class 
// which means that we are going to delete copy constructor and assignment operator 
class Game
{
    public:
        Game(const Game&) = delete;
        Game& operator=(const Game&) = delete;
        Game(std::string windowname,uint w = SCREEN_W,uint h = SCREEN_H);
        ~Game();
        // get methods
        SDL_Renderer* getRender() {return render;}
        static bool run_game;
    private:
        SDL_Renderer* render;
        SDL_Window* window;
};

// player class 
// right paddle and left paddle are also instance of this class
class Player
{
  public:
    Player(std::string,int,int,int,int,SDL_Renderer*);
    // default constructor is deleted 
    Player() = delete;
    ~Player();
    // move methods
    void up();
    void down();
    void Render();
    // get method for rect and y coordinate 
    int getY() const; 
    SDL_Rect* getRect() {return &rect;}
  private:  
    // data members 
    SDL_Texture* texture;
    SDL_Renderer* render;
    SDL_Rect rect;
};

// ball class 
class Ball{
    private:
	// data members
        SDL_Renderer* render;
        SDL_Texture* texture;
        SDL_Rect rect;
        float x,y;
        float vx ,vy;
        int speed_of_ball;
        
    public:	 
        Ball(std::string,float,float,int,SDL_Renderer*);
	~Ball();
        void Render();
        void bounceHorizontal();
        void bounceVertical();
        void Implement();
	// get methods 
        int getX() {return rect.x;}
        int getY() {return rect.y;}
        SDL_Rect* getRect() {return &rect;}
        void setSpeed(unsigned int);
	void Reset(int,int);

};

// class detector 
// is accountant for collisions between right paddle and ball or left paddle and ball 
class Detector
{
    public:
        Detector(SDL_Rect* rR,SDL_Rect* rL, SDL_Rect* rB);
	int detect();
	bool check();
    private:
        SDL_Rect *rect_r,*rect_l,*rect_b;
};

// score renderer class
// is accountant for rendering scores and contains both of rendering methods for right and left paddles' scores
class ScoreRenderer{
	public:
		ScoreRenderer(std::string,std::string,int,int,int,int,SDL_Renderer*);
		~ScoreRenderer();
		void Render();
		void Update();
		void Lift(unsigned int);
	private:
		SDL_Texture* texture;
		SDL_Rect rect;
		SDL_Renderer* render;
		unsigned int score;
		TTF_Font* font;
		SDL_Surface* text_s;
		std::string text;

};

// function for displaying start screen 
// is called only at the begining of game 
void DisplayStart(Game& obj);


#endif
