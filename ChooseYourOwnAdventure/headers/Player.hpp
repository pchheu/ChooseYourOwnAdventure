//
//  Player.cpp
//  ChooseYourOwnAdventure
//
//  Created by Peter Chheu on 3/24/17.
//  Copyright © 2017 Peter Chheu. All rights reserved.
//
#ifndef OBJECT_H
#define OBJECT_H

#include "AnimatedSprite.hpp"
#include "SDL2/SDL.h"
#include "SDL2_image/SDL_image.h"

enum Direction {
    LEFT,
    RIGHT,
    UP,
    DOWN
};

class Player : public AnimatedSprite {
public:
    Player();
    Player(Vector2 spawnPoint);
    void draw(int camx, int camy);
    void update(float elapsedTime);
    
    void moveLeft();
    void moveRight();
    void stopMoving();
    void jump();
    
    virtual void animationDone(std::string currentAnimation);
    virtual void setupAnimations();
    
    void handleTileCollisions(std::vector<Rectangle> &others);
    
    float getX();
    float getY();
    
private:
    SDL_Window* window = SDL_GL_GetCurrentWindow();
    SDL_Renderer* renderer = SDL_GetRenderer(window);
    float dx, dy;
    
    Direction facing;
    
    bool grounded;
};
#endif
