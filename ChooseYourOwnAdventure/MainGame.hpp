//
//  MainGame.hpp
//  ChooseYourOwnAdventure
//
//  Created by Peter Chheu on 2/21/17.
//  Copyright © 2017 Peter Chheu. All rights reserved.
//

#pragma once

#include "Camera.hpp"
#include "Sprite.hpp"
#include <iostream>
#include "SDL2/SDL.h"
#include "SDL2_image/SDL_image.h"
#include <OpenGL/gl.h>
#include <stdio.h>

enum class GameState{PLAY, EXIT};

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
    
    SDL_Window* window;
    SDL_Rect camera;
    
    int screenHeight;
    int screenWidth;
    
    SDL_Renderer* renderer;
    
    GameState currentState;
    
    Sprite character = *new Sprite();
    Camera screen = *new Camera();
};
