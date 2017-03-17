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

enum class Movement{LEFT, RIGHT, JUMP};

class Sprite{
public:
    Sprite();
    ~Sprite();
    
    void init(const char *path, SDL_Rect c, int _x, int _y, int _width, int _height);
    
    void move(Movement command);
    void render();
    void set_camera();
    void getCurrentMapInfo(Map m);
    
    int getPosX();
    int getPosY();
    
private:
    int x;
    int y;
    int width;
    int height;
    int LEVEL_WIDTH;
    int LEVEL_HEIGHT;
    
    int posX;
    int posY;
    
    int velX;
    int velY;
    
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Surface* ssprite;
    SDL_Texture* tsprite;
    SDL_Rect camera;
    
    SDL_Surface* currentMap;
};


