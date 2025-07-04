// ---------------------------------------------- MAIN.CPP ----------------------------------------
//                                                                                                 |
//                    main file                                                                    |
//                                                                                                 |
// ------------------------------------------------------------------------------------------------

#include "../include/pong.hpp"
#include "../include/mixer.hpp"

// simple shell command for compiling on linux 
// g++ ./src/*.cpp -o ./bin/pongprog -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer -I ./include 

// creating game objects 
Game myApp("Pong");
Player pL("./assets/images/red.jpg",LEFTSTART_X,LEFTSTART_Y,PADDLE_W,PADDLE_H,myApp.getRender());
Player pR("./assets/images/blue.jpg",RIGHTSTART_X,RIGHTSTART_Y,PADDLE_W,PADDLE_H,myApp.getRender());
Ball *ball = new Ball("./assets/images/white.jpg",BALL_STARTX,BALL_STARTY,BALLSIZE,myApp.getRender());
Detector detector(pR.getRect(),pL.getRect(),ball->getRect());
Effect* collide;

// evaluate fps (it is not actually FPS value like 30, 60 or something else)
// main idea is implementation of hard limit 
int fps = 1000.0 / FPS;
bool firstloop = true;
bool leaved = false;
int main()
{
    // init libs
    INIT();
    // create renderer objects for scores
    ScoreRenderer rScore("./assets/fonts/space.ttf","Score right: ",SCORE_R_X,SCOREBOX_Y,SCOREBOX_W,SCOREBOX_H,myApp.getRender());
    ScoreRenderer lScore("./assets/fonts/space.ttf","Score left: ",SCORE_L_X,SCOREBOX_Y,SCOREBOX_W,SCOREBOX_H,myApp.getRender());
    // display start page first
    DisplayStart(myApp);
    SDL_Event ev;
    collide = new Effect("./assets/sounds/collide.flac");
    // mainloop 
    while(Game::run_game)
    {
        Uint32 start = SDL_GetTicks();
        while(SDL_PollEvent(&ev))
        {
	    // event handling 
            if(ev.type == SDL_QUIT)
                Game::run_game = false;
            else if(ev.type == SDL_KEYDOWN)
            {
                const Uint8* state = SDL_GetKeyboardState(NULL);
		// pL.getY() > 0 bounds player and prevents the player from going over the edge 
                if(state[SDL_SCANCODE_W] && pL.getY() > 0)
                    pL.up();
		// same logic as pL.getY() but we have to multiply it with paddle height because get method returns top-left coordinate
                else if(state[SDL_SCANCODE_S] && (pL.getY()+PADDLE_H) < SCREEN_H)
                    pL.down();
		// for stopping the game, press p, it stops for 4 secs but you can modify it
		if (state[SDL_SCANCODE_P])
			SDL_Delay(4000);
		// same logic as pL (player left)
                if(state[SDL_SCANCODE_UP] && pR.getY() > 0)
                    pR.up();
                else if(state[SDL_SCANCODE_DOWN] && (pR.getY()+PADDLE_H) < SCREEN_H)
                    pR.down();
            }
        }
	// if ball is on the edge, make it bounced
        if(ball->getY() <= 0 || ball->getY()+BALLSIZE >= SCREEN_H)
            ball->bounceHorizontal();
        int val = detector.detect();
        if(val == 1 || val == 2){
            ball->bounceVertical();
	    collide -> Play();
	}
	else if(val == 4)
	{
		ball->bounceHorizontal();
		collide->Play();
	}
	// clear render 
        SDL_RenderClear(myApp.getRender());
        pL.Render();
        pR.Render();
        ball->Render();
	// if it leaves from left side of the screen, so lift player right's score 1  
        if(ball->getX() + BALLSIZE <= 0){
            ball->Reset(BALL_STARTX,BALL_STARTY);
	    leaved = true;
	    rScore.Lift(1);
        }
	// or if it leaves from right side, lift player left's score 
        else if (ball->getX() > SCREEN_W){
            ball->Reset(BALL_STARTX,BALL_STARTY);
	    leaved = true;
	    lScore.Lift(1);
        }
	// draw a vertical line 
        SDL_SetRenderDrawColor(myApp.getRender(),255,255,255,255);
        SDL_RenderDrawLine(myApp.getRender(),LINESTARTX,LINESTARTY,LINESTARTX,SCREEN_H);
        SDL_SetRenderDrawColor(myApp.getRender(),0,0,0,255);
	rScore.Render();
	lScore.Render();
	// present changes 
        SDL_RenderPresent(myApp.getRender());
	// if ball has leaved, make a delay 
	if(leaved){
		SDL_Delay(500);
		leaved = false;
	}
	// make a delay at the beginning of the game
        if(firstloop){
            SDL_Delay(500);
            firstloop = false;
        }
	ball -> Implement();
	// calculate ellapsed time 
        Uint32 ellpased = SDL_GetTicks() - start;
	// if time is less than required time for fps, delay it(hard limit)
        if(ellpased < fps)
            SDL_Delay(fps - ellpased);
    }
    // free dynamic memory 
    delete ball;
    delete collide;
    return 0;
}
