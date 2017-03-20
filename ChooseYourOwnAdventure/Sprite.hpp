//
//  Sprite.hpp
//  ChooseYourOwnAdventure
//
//  Created by Peter Chheu on 2/21/17.
//  Copyright © 2017 Peter Chheu. All rights reserved.
//
#pragma once

#include "Map.hpp"
#include <iostream>
#include "SDL2/SDL.h"
#include "SDL2_image/SDL_image.h"
#include <OpenGL/gl.h>
#include <stdio.h>
#include <string>

enum class Movement{LEFT, RIGHT, JUMP};

class Sprite{
public:
    Sprite();
    ~Sprite();
    
    void init(std::string, SDL_Rect c, float _width, float _height);
    
    void move(Movement command);
    void render();
    void set_camera();
    void getCurrentMapInfo(Map m);
    
    float getPosX();
    float getPosY();
    
    int getLevelWidth();
    int getLevelHeight();
    
private:
    int x;
    int y;
    int width;
    int height;
    int LEVEL_WIDTH;
    int LEVEL_HEIGHT;
    GLuint vboID;
    
    Map currentMap = *new Map();
    
    float posX;
    float posY;
    
    float velX;
    float velY;
    
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Surface* ssprite, swindow;
    SDL_Texture* tsprite;
    SDL_Rect camera;
    SDL_Rect csprite, dsprite;
    
    SDL_Surface* scurrentMap;
};
