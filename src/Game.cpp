//Game.cpp
#include "Game.h"
#include <sound.hpp>

extern int stateID;
extern int nextState;
extern std::ofstream loger;
extern std::vector<Texture*>textureList;
extern AudioEngine *audio;
extern AudioSoundFX *snd_bonusget, *snd_hit, *snd_pow;
extern AudioMusic *audio_music;
extern GLFT_Font font;
extern GLFT_Font fontLevel;
extern GLFT_Font font_small;
Game::Game()
{
    currentState = NULL;
}

Game::~Game()
{
	#ifdef DEBUG
		log("Game destructor");
	#endif
    Close();
}

void Game::change_state()
{
    //If the state needs to be changed
    if( nextState != STATE_NULL )
    {
        //Delete the current state
        if( nextState != STATE_EXIT )
        {
            delete currentState;
        }

        //Change the state
        switch( nextState )
        {
            case STATE_TITLE:
                currentState = new Title();
                break;

            case STATE_HELP:
                currentState = new Help();
                break;
            case STATE_LEVEL_1:
                currentState = new Level_1(1,"level_1.map");
                break;
            case STATE_LEVEL_2:
                currentState = new Level_1(2,"level_2.map");
                break;
            case STATE_LEVEL_3:
                currentState = new Level_1(3,"level_3.map");
                break;
            case STATE_INTRO:
                currentState = new Title();
                break;
            case STATE_GAMEOVER:
                currentState = new Title();
                break;
        }

        //Change the current state ID
        stateID = nextState;

        //NULL the next state ID
        nextState = STATE_NULL;
    }
}

bool Game::Start()
{
    return true;
}

bool Game::InitGL()
{
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER,1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 32);
    glEnable( GL_TEXTURE_2D );
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
    glClearColor(0,0,0,1);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0,SCREEN_WIDTH, SCREEN_HEIGHT, 0, -1, 1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    if(glGetError() != GL_NO_ERROR)
    {
        log("ERROR: gl not init, " + glGetError());
        return false;
    }
    return true;
}

bool Game::Init()
{
    if(SDL_Init(SDL_INIT_EVERYTHING) == -1)
    {
        log("ERROR: init failed");
        return false;
    }

	::AudioEngine::Start();
/*
    if(Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 1024) == -1)
    {
        return false;
    }
*/
    return true;
}


bool Game::LoadFiles()
{
    std::string filename, mus_basedir;

    mus_basedir = "sounds/music";

//Load Images------------------------------------------------
    filename = path_construct("images", "BetonBrick_n.png");
    Texture *brickbtn_tex = new Texture;
    if(brickbtn_tex->load_from_file(filename) == false)
    {
        log("ERROR: " + filename + " not found");
        return false;
    }
    textureList.push_back(brickbtn_tex);
//-----------------------------------------------------------
    filename = path_construct ("images", "StrongBrick.png");
    Texture *brickstr_tex = new Texture;
    if(brickstr_tex->load_from_file(filename) == false)
    {
        log("ERROR: " + filename + " not found");
        return false;
    }
    textureList.push_back(brickstr_tex);
//-----------------------------------------------------------
    filename = path_construct ("images", "brick.png");
    Texture *brick_tex = new Texture;
    if(brick_tex->load_from_file(filename) == false)
    {
        log("ERROR: " + filename + " not found");
        return false;
    }
    textureList.push_back(brick_tex);
//-----------------------------------------------------------
    filename = path_construct ("images", "bita.bmp");
    Texture *bita_tex = new Texture;
    if(bita_tex->load_from_file(filename, 0xFF,0,0xFF) == false)
    {
        log("ERROR: " + filename + " not found");
        return false;
    }
    textureList.push_back(bita_tex);
//-----------------------------------------------------------
    filename = path_construct ("images", "ball.png");
    Texture *ball_tex = new Texture;
    if(ball_tex->load_from_file(filename, 0xFF,0,0xFF) == false)
    {
        log("ERROR: " + filename + " not found");
        return false;
    }
    textureList.push_back(ball_tex);
//-----------------------------------------------------------
    filename = path_construct("images", "bg.png");
    Texture *bg_tex = new Texture;
    if(bg_tex->load_from_file(filename) == false)
    {
        log("ERROR: " + filename + " not found");
        return false;
    }
    textureList.push_back(bg_tex);
//-----------------------------------------------------------
    filename = path_construct("images", "bg_intro.png");
    Texture *bgintro_tex = new Texture;
    if(bgintro_tex->load_from_file(filename) == false)
    {
        log("ERROR: " + filename + " not found");
        return false;
    }
    textureList.push_back(bgintro_tex);
//-----------------------------------------------------------
    filename = path_construct("images", "bg_title.png");
    Texture *bgtitle_tex = new Texture;
    if(bgtitle_tex->load_from_file(filename) == false)
    {
        log("ERROR: " + filename + " not found");
        return false;
    }
    textureList.push_back(bgtitle_tex);
//-----------------------------------------------------------
    filename = path_construct("images", "bg_Help.bmp");
    Texture *bghelp_tex = new Texture;
    if(bghelp_tex->load_from_file(filename) == false)
    {
        log("ERROR: " + filename + " not found");
        return false;
    }
    textureList.push_back(bghelp_tex);
//-----------------------------------------------------------
    filename = path_construct("images", "bonus_speed_up.png");
    Texture *speedup_tex = new Texture;
    if(speedup_tex->load_from_file(filename, 0xFF,0,0xFF) == false)
    {
        log("ERROR: " + filename + " not found");
        return false;
    }
    textureList.push_back(speedup_tex);
//-----------------------------------------------------------
    filename = path_construct("images", "bonus_speed_down.png");
    Texture *speeddown_tex = new Texture;
    if(speeddown_tex->load_from_file(filename, 0xFF,0,0xFF) == false)
    {
        log("ERROR: " + filename + " not found");
        return false;
    }
    textureList.push_back(speeddown_tex);
//-----------------------------------------------------------
    filename = path_construct("images", "bonus_life.png");
    Texture *life_tex = new Texture;
    if(life_tex->load_from_file(filename,0xFF,0,0xFF) == false)
    {
        log("ERROR: " + filename + " not found");
        return false;
    }
    textureList.push_back(life_tex);
//-----------------------------------------------------------
    filename = path_construct("images", "bonus_die.png");
    Texture *die_tex = new Texture;
    if(die_tex->load_from_file(filename,0xFF,0,0xFF) == false)
    {
        log("ERROR: " + filename + " not found");
        return false;
    }
    textureList.push_back(die_tex);
//-----------------------------------------------------------
    filename = path_construct("images", "bonus_add.png");
    Texture *add_tex = new Texture;
    if(add_tex->load_from_file(filename,0xFF,0,0xFF) == false)
    {
        log("ERROR: " + filename + " not found");
        return false;
    }
    textureList.push_back(add_tex);
//-----------------------------------------------------------
    filename = path_construct("images", "heart.png");
    Texture *heart_tex = new Texture;
    if(heart_tex->load_from_file(filename,0xFF,0,0xFF) == false)
    {
        log("ERROR: " + filename + " not found");
        return false;
    }
    textureList.push_back(heart_tex);
//-----------------------------------------------------------
    filename = path_construct("images", "particle.png");
    Texture *particle_tex = new Texture;
    if(particle_tex->load_from_file(filename,0xFF,0,0xFF) == false)
    {
        log("ERROR: " + filename + " not found");
        return false;
    }
    textureList.push_back(particle_tex);
//-----------------------------------------------------------

//Load fonts ------------------------------------------------
    filename = path_construct("fonts", "aerial.ttf");
//-----------------------------------------------------------
    font.open(filename, 10);
//-----------------------------------------------------------
    fontLevel.open(filename, 50);
//-----------------------------------------------------------
    font_small.open(filename, 20);
//-----------------------------------------------------------

//Load sound-------------------------------------------------
	snd_bonusget = new AudioSoundFX("bonus_get.ogg");
	snd_hit = new AudioSoundFX("hit.ogg");
	snd_pow = new AudioSoundFX("pow.ogg");
//-----------------------------------------------------------

//Load music-------------------------------------------------
	audio_music = new AudioMusic("intro.ogg");
//-----------------------------------------------------------

    return true;
}



bool Game::MainLoop()
{
	#ifdef DEBUG
		log("This is DEBUG build! It will log some debug info. If this is not what you want please recompile without -DDEBUG definition.\nInitializing...");
    #endif
    if(Init() == false)
    {
        log("ERROR: Init() = false");
        return false;
    }

    Window window;

    if(window.error() == true)
    {
        log("ERROR: error in window");
        return 1;
    }
    if(InitGL() == false)
    {
        return false;
    }
    #ifdef DEBUG
		log("Loading files...");
    #endif
    if(LoadFiles() == false)
    {
        log("ERROR: Some files failed to load :(");
        return false;
    }

    stateID = STATE_INTRO;

    //Set the current game state object
    currentState = new Intro();

    Timer fps;
    while(stateID != STATE_EXIT)
    {
        fps.Start();

        while(SDL_PollEvent(&event))
        {
            if(event.type == SDL_QUIT || (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_q))
            {
                currentState->set_next_state( STATE_EXIT );
            }
            window.handle_events(event);
            currentState->handle_events(event);
        }
        //deltaTicks = fps.Get_Ticks();
//        if(window.error() == true)
//        {
//            return 1;
//        }
        currentState->logic();
        fps.Start();
        //Change state if needed
        change_state();

        //Do state rendering
        glClear(GL_COLOR_BUFFER_BIT);
        currentState->render();

        SDL_GL_SwapBuffers();

        if(fps.Get_Ticks() < 1000/FRAMES_PER_SECOND)
        {
            SDL_Delay((1000/FRAMES_PER_SECOND) - fps.Get_Ticks());
        }
    }

    return true;
}

void Game::Close()
{
	#ifdef DEBUG
		log("Game::Close()");
    #endif
    loger.close();
    font.release();
    fontLevel.release();

    for(unsigned int i = 0; i < textureList.size(); i++)
    {
       textureList.erase(textureList.begin(), textureList.end());
    }

    //imageList.erase(imageList.begin(),imageList.end());
	Mix_HaltMusic();
	delete audio_music;
    ::AudioEngine::Stop();
    SDL_Quit();
}

