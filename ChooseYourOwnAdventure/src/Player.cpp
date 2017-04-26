//
//  Player.cpp
//  ChooseYourOwnAdventure
//
//  Created by Peter Chheu on 3/24/17.
//  Copyright © 2017 Peter Chheu. All rights reserved.
//
#include "Player.hpp"

namespace player_constants {
    const float WALK_SPEED = 0.2f;
    const float JUMP_SPEED = 1.0f;
    
    const float GRAVITY = 0.002f;
    const float GRAVITY_CAP = 0.8f;
}

Player::Player(){
}

Player::Player(Vector2 spawnPoint) :
AnimatedSprite("Images/bunny2.png", 0, 300, 145, 105, spawnPoint.x, spawnPoint.y, 150){
    respawn = spawnPoint;
    
    dx = 0;
    dy = 0;
    facing = RIGHT;
    grounded = false;
    
    this->setupAnimations();
    this->playAnimation("IdleRight");
}

void Player::setupAnimations() {
    this->addAnimation(1, 0, 0, "IdleLeft", 145, 105, Vector2(0,0));
    this->addAnimation(1, 0, 105, "IdleRight", 145, 105, Vector2(0,0));
    this->addAnimation(3, 0, 0, "RunLeft", 145, 105, Vector2(0,0));
    this->addAnimation(3, 0, 105, "RunRight", 145, 105, Vector2(0,0));
    this->addAnimation(1, 0, 210, "JumpRight", 145, 105, Vector2(0,0));
    this->addAnimation(1, 1, 210, "JumpLeft", 145, 105, Vector2(0,0));
}

void Player::animationDone(std::string currentAnimation){
}

float Player::getX(){
    return x;
}

float Player::getY(){
    return y;
}

void Player::moveLeft(){
    if (this->grounded == false) {
        return;
    }
    
    this->dx = -player_constants::WALK_SPEED;
    this->playAnimation("RunLeft");
    this->facing = LEFT;
    this->moving = true;
}

void Player::moveRight(){
    if (this->grounded == false) {
        return;
    }
    
    this->dx = player_constants::WALK_SPEED;
    this->playAnimation("RunRight");
    this->facing = RIGHT;
    this->moving = true;
}

void Player::stopMoving() {
    this->dx = 0.0f;
    this->playAnimation(this->facing == RIGHT ? "IdleRight" : "IdleLeft");
    this->moving = false;
}


void Player::jump() {
    if(!playOnce){
        Mix_PlayChannel(-1, jumpNoise, 0);
        playOnce = true;
    }
    
    if (this->grounded) {
        this->dy = 0;
        this->dy -= player_constants::JUMP_SPEED;
        if(facing == LEFT){
            this->playAnimation("JumpLeft");
        }else if(facing == RIGHT){
            this->playAnimation("JumpRight");
        }
        this->grounded = false;
        this->jumped = true;
    }
}

//Handles collisions with ALL tiles the player is colliding with
void Player::handleTileCollisions(std::vector<Rectangle> &others) {
    //Figure out what side the collision happened on and move the player accordingly
    for (int i = 0; i < others.size(); i++) {
        sides::Side collisionSide = Sprite::getCollisionSide(others.at(i));
        if (collisionSide != sides::NONE) {
            switch (collisionSide) {
                case sides::TOP:
                    this->dy = 0;
                    this->y = others.at(i).getBottom() + 1;
                    if (this->grounded) {
                        this->dx = 0;
                        this->x -= this->facing == RIGHT ? 1.0f : -1.0f;
                    }
                    break;
                case sides::BOTTOM:
                    if(jumped && moving){
                        this->playAnimation(this->facing == RIGHT ? "RunRight" : "RunLeft");
                        jumped = false;
                        playOnce = false;
                    }else if(jumped){
                        this->playAnimation(this->facing == RIGHT ? "IdleRight" : "IdleLeft");
                        jumped = false;
                        playOnce = false;
                    }
                    this->y = others.at(i).getTop() - this->boundingBox.getHeight() - 1;
                    this->dy = 0;
                    this->grounded = true;
                    break;
                case sides::LEFT:
                    this->x = others.at(i).getRight() + 1;
                    break;
                case sides::RIGHT:
                    this->x = others.at(i).getLeft() - this->boundingBox.getWidth() - 1;
                    break;
            }
            
        }
    }
}

void Player::update(float elapsedTime) {
    //Apply gravity
    if (dy <= player_constants::GRAVITY_CAP) {
        dy += player_constants::GRAVITY * elapsedTime;
    }
    
    //Move by dx
    x += dx * elapsedTime;
    
    //Checks left and right bounds
    if( x < 0 ){
        x = 0;
    }
    if( x + getWidth() > getLevelWidth() ){
        x = getLevelWidth() - getWidth();
    }
    
    //Move by dy
    y += dy * elapsedTime;
    
    //Respawns if fallen out of map
    if(y > getLevelHeight() + 500){
        x = respawn.x;
        y = respawn.y;
        dy = 0;
    }
    
    AnimatedSprite::update(elapsedTime);
}

void Player::draw(){
    AnimatedSprite::draw(x, y);
}
