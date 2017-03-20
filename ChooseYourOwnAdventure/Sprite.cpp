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
    //vboID = 0;
}

Sprite::~Sprite(){
    /*if(vboID != 0){
        glDeleteBuffers(1, &vboID);
    }*/
}

//Initializes the sprites dimensions and pulls the window/renderer
void Sprite::init(std::string path, SDL_Rect c, float _width, float _height){
    ssprite = IMG_Load(path.c_str());
    
    if(ssprite == nullptr){
        std::cout << "Error: " << IMG_GetError() << std::endl;
    }
    
    window = SDL_GL_GetCurrentWindow();
    renderer = SDL_GetRenderer(window);
    tsprite = SDL_CreateTextureFromSurface(renderer, ssprite);
     
    camera = c;
    
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
            if(posX > 0)
                posX -= velX;
            /*
            if( posX < 0 || (posX + width > LEVEL_WIDTH)){
                //Move back
                posX -= velX;
            }*/
            
            csprite.x = posX;
            render();
            
            //std::cout << "Left key pressed" << std::endl;
            break;
        case Movement::RIGHT:
            if(posX < LEVEL_WIDTH)
                posX += velX;
            
            csprite.x = posX;
            render();
            
            //std::cout << "Right key pressed" << std::endl;
            break;
        case Movement::JUMP:
            posY -= velY;
            
            if( (posY < 0) || (posY + height > LEVEL_HEIGHT)){
                //Move back
                posY += velY;
            }
            
            csprite.y = posY;
            render();
            
            //std::cout << "Space pressed" << std::endl;
            break;
            
        break;
    }
    
    while(SDL_GetTicks() - FrameStartTimeMs < 1000/FPS);
}

void Sprite::set_camera(){
    //Centers the camera over the sprite
    camera.x = (posX + width/2) - SCREEN_WIDTH/2;
    camera.y = (posY + height/2) - SCREEN_HEIGHT/2;
    
    //std::cout << "CameraX: " << camera.x << std::endl;
    //std::cout << "CameraY: " << camera.y << std::endl;
    
    //Keeps the camera in bounds
    if(camera.x < 0){
        camera.x = 0;
    }
    if( camera.y < 0 ){
        camera.y = 0;
    }
    if( camera.x > LEVEL_WIDTH - camera.w ){
        camera.x = LEVEL_WIDTH - camera.w;
    }
    if( camera.y > LEVEL_HEIGHT - camera.h ){
        camera.y = LEVEL_HEIGHT - camera.h;
    }
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
    //Updates camera as the sprite moves
    //set_camera();
    //currentMap.updateCamera(camera);
    //SDL_Texture* tcurrentMap = SDL_CreateTextureFromSurface(renderer, scurrentMap);
    
    //SDL_RenderCopy(renderer, tcurrentMap, &camera, NULL);
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
