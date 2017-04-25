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
    void draw();
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
    
    Vector2 respawn;
    
    float dx, dy;
    
    Direction facing;
    
    Mix_Chunk *jumpNoise = Mix_LoadWAV("/music/jump.wav");
    bool playOnce = false;
    
    bool grounded;
    bool jumped;
    bool moving;
};
#endif
