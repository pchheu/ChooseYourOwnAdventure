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
#include <iostream>
#include "SDL2/SDL.h"
#include "SDL2_image/SDL_image.h"
#include <OpenGL/gl.h>
#include <stdio.h>
#include "Timer.hpp"

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
    void update(float elapsedTime);
    
    SDL_Window* window;
    SDL_Rect camera;
    
    int screenHeight;
    int screenWidth;
    int countedFrames;
    
    float elaspedTime;
    
    SDL_Renderer* renderer;
    
    GameState currentState;
    
    Sprite character = *new Sprite();
    Player player = *new Player();
    Camera screen = *new Camera();
    Timer fpsTimer;
};
