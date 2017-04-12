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

void Camera::initCamera(Player p){
    //Sets up the size of the camera
    camera.x = 0;
    camera.y = 0;
    camera.w = SCREEN_WIDTH;
    camera.h = SCREEN_HEIGHT;
    
    p1 = &p;
    
    swidth = 145;
    sheight = 105;
    
    LEVEL_WIDTH = p.getLevelWidth();
    LEVEL_HEIGHT = p.getLevelHeight();
}

void Camera::updateCamera(float x, float y){
    LEVEL_WIDTH = p1->getLevelWidth();
    LEVEL_HEIGHT = p1->getLevelHeight();
    
    //Gets position of the sprite in respect to the camera
    posX = x;
    posY = y;
    
    //Centers the camera over the sprite
    camera.x = (posX + swidth/2) - SCREEN_WIDTH/2;
    camera.y = (posY + sheight/2) - SCREEN_HEIGHT/2;
    
    //Keeps the camera in bounds
    if( camera.x < 0 ){
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

void Camera::updateMap(int width, int height){
    //Grabs the dimensions of the level
    LEVEL_HEIGHT = height;
    LEVEL_WIDTH = width;
}

SDL_Rect Camera::getCamInfo(){
    return camera;
}

int Camera::getCamX(){
    return camera.x;
}

int Camera::getCamY(){
    return camera.y;
}
