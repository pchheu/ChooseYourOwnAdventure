//
//  AnimatedSprite.cpp
//  ChooseYourOwnAdventure
//
//  Created by Peter Chheu on 3/23/17.
//  Copyright © 2017 Peter Chheu. All rights reserved.
//

#include "AnimatedSprite.hpp"

AnimatedSprite::AnimatedSprite(){
}

AnimatedSprite::AnimatedSprite(const std::string filePath,
                               int sourceX,
                               int sourceY,
                               int width,
                               int height,
                               float posX,
                               float posY,
                               float ntimeToUpdate):
Sprite(filePath, width, height, posX, posY){
    frameIndex = 0;
    timeToUpdate = ntimeToUpdate;
    currentAnimation = "";
    currentAnimationOnce = false;
    visible = true;
    
    window = SDL_GL_GetCurrentWindow();
    renderer = SDL_GetRenderer(window);
}

void AnimatedSprite::addAnimation(int frames, int x, int y, std::string name, int width, int height, Vector2 offset){
    std::vector<SDL_Rect> rectangles;
    for(int i = 0; i < frames; i++){
        SDL_Rect newRect = { (i + x) * width, y, width, height };
        rectangles.push_back(newRect);
    }
    this->animations.insert(std::pair<std::string, std::vector<SDL_Rect>>(name, rectangles));
    this->offsets.insert(std::pair<std::string, Vector2>(name, offset));
}

void AnimatedSprite::resetAnimations(){
    this->animations.clear();
    this->offsets.clear();
}

void AnimatedSprite::playAnimation(std::string animation, bool once){
    this->currentAnimationOnce = once;
    
    if(this->currentAnimation != animation){
        this->currentAnimation = animation;
        this->frameIndex = 0;
    }
}

void AnimatedSprite::setVisible(bool visible){
    this->visible = visible;
}

void AnimatedSprite::update(int elapsedTime){
    Sprite::update();
    
    timeElapsed += elapsedTime;
    if(timeElapsed > timeToUpdate){
        timeElapsed -= timeToUpdate;
        if(frameIndex < this->animations[this->currentAnimation].size() - 1){
            frameIndex++;
        }else{
            if(currentAnimationOnce == true){
                this->setVisible(false);
            }
            frameIndex = 0;
        }
    }
}

void AnimatedSprite::draw(int x, int y){
    if(this->visible){
        SDL_Rect destRect;
        destRect.x = (x + offsets[currentAnimation].x) - Camera::getCamX();
        destRect.y = (y + offsets[currentAnimation].y) - Camera::getCamY();
        destRect.w = Sprite::getWidth();
        destRect.h = Sprite::getHeight();
        
        SDL_Rect sourceRect = animations[currentAnimation][frameIndex];
        SDL_RenderCopy(renderer, tsprite, &sourceRect, &destRect);
    }
}

void AnimatedSprite::animationDone(std::string currentAnimation){
    frameIndex = 0;
    animationDone(currentAnimation);
}

void AnimatedSprite::setupAnimations(){
    this->addAnimation(3, 0, 0, "runLeft", 100, 100, Vector2(0,0));
}
