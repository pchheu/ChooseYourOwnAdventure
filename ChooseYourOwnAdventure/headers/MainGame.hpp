//
//  MainGame.hpp
//  ChooseYourOwnAdventure
//
//  Created by Peter Chheu on 2/21/17.
//  Copyright © 2017 Peter Chheu. All rights reserved.
//

#pragma once

#include "Camera.hpp"
#include "Player.hpp"
#include "Errors.hpp"
#include "Portal.hpp"
#include "NPC.hpp"
#include "SDL2/SDL.h"
#include "DialogueTree.hpp"
#include "SDL2_image/SDL_image.h"
#include "SDL2_ttf/SDL_ttf.h"
#include "SDL2_mixer/SDL_mixer.h"
#include <OpenGL/gl.h>
#include <stdio.h>
#include <iostream>
#include <unistd.h>

enum class GameState{MENU, PLAY, EXIT};

class MainGame{
public:
    MainGame();
    ~MainGame();

    void run();

private:
    void initSystems();
    void gameLoop();
    void processInput();
    void drawGame();
    void update(float elapsedTime);
    void menu();
    void initObjects();
    
    SDL_Window* window;
    SDL_Rect camera;
    
    std::map<SDL_Scancode, bool> heldKeys;
    std::map<SDL_Scancode, bool> pressedKeys;
    std::map<SDL_Scancode, bool> releasedKeys;
    
    Mix_Music *music;
    
    int screenHeight;
    int screenWidth;
    
    float elaspedTime;
    
    bool dialogueEngaged = false;
    
    SDL_Renderer* renderer;
    
    GameState currentState;

    Portal p;
    DialogueTree tree;
    NPC owl;
    Player player;
    Map currentlevel, nextlevel;
    Map level1, level2, level3;
    Camera screen;
};
