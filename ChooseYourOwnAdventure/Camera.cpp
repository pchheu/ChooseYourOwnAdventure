//
//  Camera.cpp
//  ChooseYourOwnAdventure
//
//  Created by Peter Chheu on 3/18/17.
//  Copyright © 2017 Peter Chheu. All rights reserved.
//

#include "Camera.hpp"

const int SCREEN_WIDTH = 1080;
const int SCREEN_HEIGHT = 800;

Camera::Camera(){
}

Camera::~Camera(){
}

void Camera::initCamera(Sprite c){
    //Sets up the size of the camera
    camera.x = 0;
    camera.y = 0;
    camera.w = SCREEN_WIDTH;
    camera.h = SCREEN_HEIGHT;
    
    //Allows the camera to keep track of the sprite
    mc = &c;
    
    swidth = 100;
    sheight = 100;
    
    LEVEL_WIDTH = mc->getLevelWidth();
    LEVEL_HEIGHT = mc->getLevelHeight();
    
}

void Camera::updateCamera(float x, float y){
    //Grabs the dimensions of the level
    LEVEL_WIDTH = mc->getLevelWidth();
    LEVEL_HEIGHT = mc->getLevelHeight();
    
    //Gets position of the sprite in respect to the camera
    posX = x;
    posY = y;
    
    //Centers the camera over the sprite
    camera.x = (posX + swidth/2) - SCREEN_WIDTH/3;
    camera.y = (posY + sheight/2) - SCREEN_HEIGHT/3;
 
    std::cout << camera.x << " " << camera.y << std::endl;
    
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

SDL_Rect Camera::getCamInfo(){
    return camera;
}
