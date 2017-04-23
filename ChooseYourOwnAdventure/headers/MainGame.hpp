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
#include "SDL2/SDL.h"
#include "DialogueTree.hpp"
#include "SDL2_image/SDL_image.h"
#include "SDL2_ttf/SDL_ttf.h"
#include <OpenGL/gl.h>
#include <stdio.h>
#include <iostream>

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
    
    SDL_Window* window;
    SDL_Rect camera;
    
    std::map<SDL_Scancode, bool> heldKeys;
    std::map<SDL_Scancode, bool> pressedKeys;
    std::map<SDL_Scancode, bool> releasedKeys;
    
    int screenHeight;
    int screenWidth;
    
    float elaspedTime;
    
    SDL_Renderer* renderer;
    
    GameState currentState;

    Player player;
    Map currentlevel, nextlevel;
    Camera screen;
};
