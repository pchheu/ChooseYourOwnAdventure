//
//  Camera.hpp
//  ChooseYourOwnAdventure
//
//  Created by Peter Chheu on 3/18/17.
//  Copyright © 2017 Peter Chheu. All rights reserved.
//
#pragma once

#include "Sprite.hpp"
#include <stdio.h>
#include <iostream>
#include "SDL2/SDL.h"
#include "SDL2_image/SDL_image.h"
#include <OpenGL/gl.h>

class Camera{
public:
    Camera();
    ~Camera();
    
    void initCamera(Sprite c);
    void updateCamera(float x, float y);
    void getSpriteInfo();
    SDL_Rect getCamInfo();
    
    SDL_Rect camera;
    
    int x;
    int y;
    
private:
    float posX;
    float posY;
    
    int swidth;
    int sheight;
    
    int LEVEL_WIDTH;
    int LEVEL_HEIGHT;
    
    Sprite* mc;
};
