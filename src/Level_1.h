//Level_1.h
#ifndef LEVEL_1_H
#define LEVEL_1_H

#include <GLFT_Font.hpp>
#include "GameState.h"
#include "BrickControl.h"
#include "Ball.h"
#include "Bita.h"
#include "Timer.h"
#include "Bonus.h"
#include "Particles.h"
#include "Button.h"
#include "Checkbox.h"
#include "Texture.h"
#include <io.hpp>
#include <vector>
#include <SDL_mixer.h>
class Level_1 : public GameState
{
public:
    Level_1(int num_level,std::string filename);
    Level_1(){};
    ~Level_1();
    void render();
    void logic();
    void handle_events(SDL_Event&);
    void load_files();
    void replay();
    static bool pause;
    int num_level;
    int lives_start, score_start;
    static bool restarted;
protected:
    Mix_Chunk *hit;
    Mix_Chunk *hit_wall;
    SDL_Surface *level_label;
    SDL_Surface *level_label_small;
    SDL_Surface *clear_label;
    SDL_Surface *score_label;
    SDL_Surface *life_label;
    //Texture *heart_spr;
    Texture *ball_spr;
    //Texture *particle_spr;
    Ball *ball;
    Bita bita;
    Bonus *bonus;
    bool bonus_created;
    int collision_type;
    bool begin;
    bool clear;
    int drwidth;
    std::string drstring;
    bool game_over;
    bool show_particles;
    Timer timer;
    Timer timer_speed_up;
    Timer timer_speed_down;
    //GLFT_Font font_small;
    //SDL_Color textColor;
    int prevScore;
    int prevLives;
    //int num_level;
    Particles *particles[20];
    Button *resumeButton;
    Button *exitButton;
    Button *restartButton;
    Checkbox *soundOn;
    Checkbox *musicOn;
};

#endif
