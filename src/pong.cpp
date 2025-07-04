// ---------------------------------------------- PONG.CPP ----------------------------------------
//                                                                                                 |
//       contains all of the class methods' definitions and some other funcitons' definitions      |
//       for music objects take a look at MIXER.HPP AND MIXER.CPP                                  |
//                                                                                                 |
// ------------------------------------------------------------------------------------------------


// including libraries 
#include "../include/pong.hpp"
#include <SDL2/SDL_mixer.h>

// static data member 
bool Game::run_game = true;

// init functuion 
// which inits SDL2, SDL_image, SDL_ttf, SDL_mixer 
void INIT()
{
    if(SDL_Init(SDL_INIT_EVERYTHING) > 0)
	// if error occurs, log messages
        std::cout << "Error while initializing sdl2!\n";
    if(!IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG))
        std::cout << "Error while initilalizing SDL2_image!\n";
    if(Mix_Init( MIX_INIT_MID | MIX_INIT_MOD | MIX_INIT_OGG | MIX_INIT_WAVPACK | MIX_INIT_OPUS | MIX_INIT_FLAC | MIX_INIT_MP3) == -1)
        std::cout << "Couldn't initialize the mixer library! The Error is: " << Mix_GetError();
   TTF_Init();
   // seed random 
   srand(time(NULL));
   if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT,2,2048) < 0)
	   std::cout << "Error While opening the audio device! " << Mix_GetError() << '\n';
}

// implementation of display funtion for start screen 
void DisplayStart(Game& obj)
{
    // load assets and create textures 
    TTF_Font* font = TTF_OpenFont("./assets/fonts/space.ttf",20);
    bool run_start = true;
    SDL_Event ev;
    SDL_Surface* text_surface1 = TTF_RenderText_Blended(font,"Welcome to Pong Game!",{255,255,255});
    SDL_Surface* text_surface2 = TTF_RenderText_Blended(font,"Press <ENTER> to start",{255,255,255});
    SDL_Texture *texture_text1 = SDL_CreateTextureFromSurface(obj.getRender(),text_surface1),
                *texture_text2 = SDL_CreateTextureFromSurface(obj.getRender(),text_surface2);
    SDL_FreeSurface(text_surface1);
    SDL_FreeSurface(text_surface2);
    // rects for texts 
    SDL_Rect rect_1({100,150,700,200}),
             rect_2({200,400,500,100});
    while(run_start)
    {
	// event handling 
        while(SDL_PollEvent(&ev))
        {
            // if enter is pressed, start game 
            if(ev.key.keysym.sym == SDLK_RETURN || ev.key.keysym.sym == SDLK_RETURN2)
                run_start = false;
        }
	// clear render
        SDL_RenderClear(obj.getRender());
        SDL_RenderCopy(obj.getRender(),texture_text1,NULL,&rect_1);
        SDL_RenderCopy(obj.getRender(),texture_text2,NULL,&rect_2);
	// present render 
        SDL_RenderPresent(obj.getRender());
    }
    // if it quits , then destroy textures and free memory 
    SDL_DestroyTexture(texture_text1);
    SDL_DestroyTexture(texture_text2); 
    TTF_CloseFont(font);
}


Game::Game(std::string windowname,uint w,uint h)
{
    //create window instance with default values
    window = SDL_CreateWindow(windowname.c_str(),
                            SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED-20,
                            w,h,SDL_WINDOW_SHOWN);
    // bind renderer with window 
    render = SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED);
}

Game::~Game()
{
    // clean up allocated memory 
    SDL_DestroyRenderer(render);
    SDL_DestroyWindow(window);
}

Player::Player(std::string filepath,int x,int y,int w, int h,SDL_Renderer* rend):rect({x,y,w,h}),render(rend)
{
    // load image and create texture 
    SDL_Surface* image;
    image = IMG_Load(filepath.c_str());
    texture = SDL_CreateTextureFromSurface(render,image);
    SDL_FreeSurface(image);
}
Player::~Player()
{ 
    // free memory 
    SDL_DestroyTexture(texture);
}
void Player::up()
{
    // if up, then subtract player speed from y coordinate 
    rect.y -= PLAYER_SPEED; 
}
void Player::down()
{
    // if down, implement same logic 
    rect.y += PLAYER_SPEED;
}
void Player::Render()
{
    SDL_RenderCopy(render,texture,NULL,&rect);
}

int Player::getY() const
{
    return rect.y;
}

Ball::Ball(std::string filepath, float x, float y, int w,SDL_Renderer* rend):render(rend),speed_of_ball(BALL_SPEED)
{
    // create a surface and load image 
    SDL_Surface* image;
    image = IMG_Load(filepath.c_str());
    rect.x = x; rect.y = y; rect.w = w; rect.h = w;
    // create texture 
    texture = SDL_CreateTextureFromSurface(render,image);
    SDL_FreeSurface(image);
    // create a random angle and make the ball move in this direction 
    float angle = (rand()%120 - 60)*M_PI / 180.0f;
    int dir = (rand()%2 == 0)?1:-1;
    // velocity components
    vx = cos(angle)*speed_of_ball*dir;
    vy = sin(angle)*speed_of_ball;
}
Ball::~Ball()
{
    // free memory 
    SDL_DestroyTexture(texture);
}

void Ball::Render()
{
    SDL_RenderCopy(render,texture,NULL,&rect);
}

void Ball::bounceHorizontal()
{
    // if it bounces horizontally, it means ball is going to keep its vx(x component of velocity) but y component is going to change 
    vy = -vy;   
}

void Ball::Implement()
{
    // modify x and y coordinates 
    x+=vx;
    y+=vy;
    // modify rect's coordinates ( x and y are data members of class )
    rect.x = x;
    rect.y = y;
}

void Ball::setSpeed(unsigned int new_speed)
{
    // if necessary set speed again 
    speed_of_ball = new_speed;
}

void Ball::bounceVertical()
{
    // same logic as bounceHorizontal() 
    vx = -vx;
}

void Ball::Reset(int X, int Y)
{
    x = X; y = Y;
    // reset coordinates and randomize the direction again
    float angle = (rand()%120 - 60)*M_PI / 180.0f;
    int dir = (rand()%2 == 0)?1:-1;
    vx = cos(angle)*speed_of_ball*dir;
    vy = sin(angle)*speed_of_ball;
}

Detector::Detector(SDL_Rect* rR,SDL_Rect* rL, SDL_Rect* rB):rect_b(rB),rect_l(rL),rect_r(rR)
{

}
int Detector::detect()
{
    if(SDL_HasIntersection(rect_b,rect_l) == SDL_TRUE)
    {
	    SDL_Rect intersection;
	    SDL_IntersectRect(rect_b,rect_l,&intersection);
	    if (intersection.h > intersection.w)
		    return 1;
	    else 
		    return 4;
    }
    else if(SDL_HasIntersection(rect_b,rect_r) == SDL_TRUE ) 
    {
	    SDL_Rect intersection;
	    SDL_IntersectRect(rect_b,rect_r,&intersection);
	    if (intersection.h > intersection.w)
		    return 1;
	    else 
		    return 4;
    }
    return  0;
}

ScoreRenderer::ScoreRenderer(std::string filepath,std::string message, int x, int y, int w, int h, SDL_Renderer* rend):score(0),text(message)
{
	// load font 
	font = TTF_OpenFont(filepath.c_str(),FONTSIZE);
	if (font == NULL)
		std::cout << "The font can't be loaded! Error is: " << TTF_GetError() << '\n';
	std::string sc_text = text + std::to_string(score);
	// set rect object
	rect.x = x; rect.y = y; rect.w = w; rect.h = h;
	// bind render 
	render = rend;
	text_s = TTF_RenderText_Blended(font,sc_text.c_str(),{255,255,255});
	texture = SDL_CreateTextureFromSurface(render,text_s);

}

ScoreRenderer::~ScoreRenderer()
{
	// free memory
	SDL_FreeSurface(text_s);
	SDL_DestroyTexture(texture);
	TTF_CloseFont(font);
}

void ScoreRenderer::Render()
{
	SDL_RenderCopy(render,texture,NULL,&rect);
}


void ScoreRenderer::Update()
{
	// is called when score is lifted up 
	// because it is a kind of expensive function and calling it in each single loop 
	// of main game may slow down the game or reduce the efficiency
	SDL_FreeSurface(text_s);
	SDL_DestroyTexture(texture);
	// update the text 
	std::string sc_text = text + std::to_string(score);
	// create texture again 
	text_s = TTF_RenderText_Blended(font,sc_text.c_str(),{255,255,255});
	texture = SDL_CreateTextureFromSurface(render,text_s);

}

void ScoreRenderer::Lift(unsigned int count)
{
	score += count;
	this -> Update();
}



