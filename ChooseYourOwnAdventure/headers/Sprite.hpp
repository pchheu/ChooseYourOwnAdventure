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
#include "Camera.hpp"

enum class Movement{LEFT, RIGHT, JUMP};

class Sprite{
public:
    Sprite();
    Sprite(std::string path, float _width, float _height, float posX, float posY);
    ~Sprite();
    
    void init(std::string, float _width, float _height);
    
    void render(float camX, float camY);
    void getCurrentMapInfo(Map m);
    void update();
    
    int getLevelWidth();
    int getLevelHeight();
    int getWidth();
    int getHeight();
    
    float getX();
    float getY();
    
    const sides::Side getCollisionSide(Rectangle &other) const;
    const Rectangle getBoundingBox() const;
    
protected:
    float x;
    float y;
    
    int width;
    int height;
    
    float velX;
    float velY;
    
    SDL_Surface* ssprite, swindow;
    SDL_Texture* tsprite;
    
    SDL_Rect csprite;
    Rectangle boundingBox;
    
private:
    int LEVEL_WIDTH;
    int LEVEL_HEIGHT;
    
    Map currentMap = *new Map();
    
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Rect collisionBox;
    
    SDL_Surface* scurrentMap;
};
