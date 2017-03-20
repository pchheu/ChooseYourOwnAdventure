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
}

//Redraws the sprite to show movement
void Sprite::move(Movement command){
    FrameStartTimeMs = SDL_GetTicks();
    
    switch (command) {
        case Movement::LEFT:
            if(posX > 0){
                posX -= velX;
            }
            
            csprite.x = posX;
            render();
            break;
        case Movement::RIGHT:
            if(posX < LEVEL_WIDTH){
                posX += velX;
            }
            
            csprite.x = posX;
            render();
            break;
        case Movement::JUMP:
            posY -= velY;
            
            if( (posY < 0) || (posY + height > LEVEL_HEIGHT)){
                //Move back
                posY += velY;
            }
            
            csprite.y = posY;
            render();
            break;
            
        break;
    }
    
    while(SDL_GetTicks() - FrameStartTimeMs < 1000/FPS);
}

void Sprite::render(){
    /*
    glBindBuffer(GL_ARRAY_BUFFER, vboID);
    
    glEnableVertexAttribArray(0);
    
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);
    
    glDrawArrays(GL_TRIANGLES, 0, 6);
    
    glDisableVertexAttribArray(0);
    
    glBindBuffer(GL_ARRAY_BUFFER, 0);
     */
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
