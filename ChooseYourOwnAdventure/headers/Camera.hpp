//
//  Camera.hpp
//  ChooseYourOwnAdventure
//
//  Created by Peter Chheu on 3/18/17.
//  Copyright © 2017 Peter Chheu. All rights reserved.
//
#pragma once

#include <stdio.h>
#include <iostream>
#include "SDL2/SDL.h"
#include "SDL2_image/SDL_image.h"
#include <OpenGL/gl.h>
//#include "Player.hpp"

class Camera{
public:
    Camera();
    ~Camera();
    
    void initCamera();
    void updateCamera(int x, int y);
    void getSpriteInfo();
    void updateMap(int width, int height);
    SDL_Rect getCamInfo();
    
    static SDL_Rect camera;
    
    float x;
    float y;
    
    static int getCamX();
    static int getCamY();
    
private:
    float posX;
    float posY;
    
    int swidth;
    int sheight;
    
    int LEVEL_WIDTH;
    int LEVEL_HEIGHT;
};
