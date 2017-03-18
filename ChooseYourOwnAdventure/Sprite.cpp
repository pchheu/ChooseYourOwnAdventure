//
//  Sprite.cpp
//  ChooseYourOwnAdventure
//
//  Created by Peter Chheu on 2/21/17.
//  Copyright © 2017 Peter Chheu. All rights reserved.
//

#include "Sprite.hpp"

const int SCREEN_WIDTH = 1080;
const int SCREEN_HEIGHT = 700;

Sprite::Sprite(){
    vboID = 0;
}

Sprite::~Sprite(){
    if(vboID != 0){
        glDeleteBuffers(1, &vboID);
    }
}

//Initializes the sprites dimensions and pulls the window/renderer
void Sprite::init(const char *path, SDL_Rect c, float _x, float _y, float _width, float _height){
    ssprite = IMG_Load(path);
    
    if(ssprite == nullptr){
        std::cout << "Error: " << IMG_GetError() << std::endl;
    }
    
    /*
    window = SDL_GL_GetCurrentWindow();
    renderer = SDL_GetRenderer(window);
    tsprite = SDL_CreateTextureFromSurface(renderer, ssprite);
     */
    
    if(vboID == 0){
        glGenBuffers(1, &vboID);
    }
    
    float vertexData[12];
    
    //First Triangle
    vertexData[0] = x + width;
    vertexData[1] = y + width;
    
    vertexData[2] = x;
    vertexData[3] = y + height;
    
    vertexData[4] = x;
    vertexData[5] = y;
    
    //Second Triangle
    vertexData[6] = x;
    vertexData[7] = y;
    
    vertexData[8] = x + width;
    vertexData[9] = y;
    
    vertexData[10] = x + width;
    vertexData[11] = y + height;
    
    glBindBuffer(GL_ARRAY_BUFFER, vboID);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);
    
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    
    camera = c;
    
    x = _x;
    y = _y;
    width = _width;
    height = _height;
    
    posX = 500;
    posY = 300;
    
    velX = 30;
    velY = 30;
}

//Redraws the sprite to show movement
void Sprite::move(Movement command){
    switch (command) {
        case Movement::LEFT:
            posX -= velX;
            if( posX < 0 || (posX + width > LEVEL_WIDTH)){
                //Move back
                posX -= velX;
            }
            
            render();
            
            //std::cout << "Left key pressed" << std::endl;
            break;
        case Movement::RIGHT:
            posX += velX;
            if( posX < 0 || (posX + width > LEVEL_WIDTH)){
                //Move back
                posX -= velX;
            }
            
            render();
            
            //std::cout << "Right key pressed" << std::endl;
            break;
        case Movement::JUMP:
            posY += velY;
            
            if( (posY < 0) || (posY + height > LEVEL_HEIGHT)){
                //Move back
                posY -= velY;
            }
            
            render();
            
            //std::cout << "Space pressed" << std::endl;
            break;
            
        break;
    }
}

void Sprite::set_camera(){
    //Centers the camera over the sprite
    camera.x = (posX + width/2) - SCREEN_WIDTH/2;
    camera.y = (posY + height/2) - SCREEN_HEIGHT/2;
    
    std::cout << "CameraX: " << camera.x << std::endl;
    std::cout << "CameraY: " << camera.y << std::endl;
    
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
    glBindBuffer(GL_ARRAY_BUFFER, vboID);
    
    glEnableVertexAttribArray(0);
    
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);
    
    glDrawArrays(GL_TRIANGLES, 0, 6);
    
    glDisableVertexAttribArray(0);
    
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    
    /*
    //Updates camera as the sprite moves
    set_camera();
    
    SDL_Texture* tcurrentMap = SDL_CreateTextureFromSurface(renderer, currentMap);
    SDL_RenderCopy(renderer, tcurrentMap, &camera, NULL);
    SDL_RenderCopy(renderer, tsprite, &csprite, NULL);
     */
}

void Sprite::getCurrentMapInfo(Map m){
    currentMap = m.getMapSurface();
    LEVEL_WIDTH = m.getlevelWidth();
    LEVEL_HEIGHT = m.getlevelHeight();
}
