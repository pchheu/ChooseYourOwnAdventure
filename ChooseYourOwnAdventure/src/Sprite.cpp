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

int FPS = 60;
int FrameStartTimeMs = 0;

Sprite::Sprite(){
}

Sprite::~Sprite(){
}

//Initializes the sprites dimensions and pulls the window/renderer
void Sprite::init(std::string path, float _width, float _height){
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
    
    width = _width;
    height = _height;
    
    posX = 500.0;
    posY = 600.0;
    
    velX = 400.0/FPS;
    velY = 400.0/FPS;
    
    boundingBox = Rectangle(x, y, width, height);
}

//Redraws the sprite to show movement
void Sprite::move(Movement command){
    FrameStartTimeMs = SDL_GetTicks();
    
    switch (command) {
        case Movement::LEFT:
            if(posX > 0){
                posX -= velX;
            }
            
            collisionBox.x = posX;
            break;
        case Movement::RIGHT:
            if(posX + width < LEVEL_WIDTH){
                posX += velX;
            }
            
            collisionBox.x = posX;
            break;
        case Movement::JUMP:
            posY -= velY;
            
            if( (posY < 0) || (posY + height > LEVEL_HEIGHT)){
                //Move back
                posY += velY;
            }
            
            collisionBox.y = posY;
            break;
            
        break;
    }
    
    //while(SDL_GetTicks() - FrameStartTimeMs < 1000/FPS);
}

void Sprite::render(float camX, float camY){
    csprite.x = posX - camX;
    csprite.y = posY - camY;

    SDL_RenderCopy(renderer, tsprite, NULL, &csprite);
}

void Sprite::getCurrentMapInfo(Map m){
    currentMap = m;
    scurrentMap = m.getMapSurface();
    LEVEL_WIDTH = m.getlevelWidth();
    LEVEL_HEIGHT = m.getlevelHeight();
}

float Sprite::getPosX(){
    return posX;
}

float Sprite::getPosY(){
    return posY;
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
