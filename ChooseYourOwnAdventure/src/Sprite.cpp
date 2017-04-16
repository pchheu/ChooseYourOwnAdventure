//
//  Sprite.cpp
//  ChooseYourOwnAdventure
//
//  Created by Peter Chheu on 2/21/17.
//  Copyright © 2017 Peter Chheu. All rights reserved.
//

#include "Sprite.hpp"

const int SCREEN_WIDTH = 1080;
const int SCREEN_HEIGHT = 800;

Sprite::Sprite(){
}

Sprite::~Sprite(){
}

//Alternative constructor that creates the display and gets sprite dimensions
Sprite::Sprite(std::string path, float _width, float _height, float posX, float posY){
    ssprite = IMG_Load(path.c_str());
    
    if(ssprite == nullptr){
        std::cout << "Error: " << IMG_GetError() << std::endl;
    }
    
    window = SDL_GL_GetCurrentWindow();
    renderer = SDL_GetRenderer(window);
    tsprite = SDL_CreateTextureFromSurface(renderer, ssprite);
    
    csprite.x = 0;
    csprite.y = 300;
    csprite.w = _width;
    csprite.h = _height;
    
    x = posX;
    y = posY;
    
    width = _width;
    height = _height;
    
    boundingBox = Rectangle(x, y, width, height);
}

void Sprite::render(float camX, float camY){
    csprite.x = x - camX;
    csprite.y = y - camY;

    SDL_RenderCopy(renderer, tsprite, NULL, &csprite);
}

void Sprite::getCurrentMapInfo(Map m){
    currentMap = m;
    scurrentMap = m.getMapSurface();
    LEVEL_WIDTH = m.getlevelWidth();
    LEVEL_HEIGHT = m.getlevelHeight();
}

float Sprite::getX(){
    return x;
}

float Sprite::getY(){
    return y;
}

int Sprite::getLevelWidth(){
    return LEVEL_WIDTH;
}

int Sprite::getLevelHeight(){
    return LEVEL_HEIGHT;
}

int Sprite::getWidth(){
    return width;
}

int Sprite::getHeight(){
    return height;
}

const sides::Side Sprite::getCollisionSide(Rectangle &other) const{
    int amtRight, amtLeft, amtTop, amtBottom;
    amtRight = this->getBoundingBox().getRight() - other.getLeft();
    amtLeft = other.getRight() - this->getBoundingBox().getLeft();
    amtTop = other.getBottom() - this->getBoundingBox().getTop();
    amtBottom = this->getBoundingBox().getBottom() - other.getTop();
    
    int vals[4] = { abs(amtRight), abs(amtLeft), abs(amtTop), abs(amtBottom) };
    int lowest = vals[0];
    for (int i = 0; i < 4; i++) {
        if (vals[i] < lowest) {
            lowest = vals[i];
        }
    }
    
    return
    lowest == abs(amtRight) ? sides::RIGHT :
    lowest == abs(amtLeft) ? sides::LEFT :
    lowest == abs(amtTop) ? sides::TOP :
    lowest == abs(amtBottom) ? sides::BOTTOM :
    sides::NONE;
}

const Rectangle Sprite::getBoundingBox() const{
    return boundingBox;
}

void Sprite::update(){
    boundingBox = Rectangle(x, y, width, height);
}
