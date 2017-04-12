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
    const float JUMP_SPEED = 0.7f;
    
    const float GRAVITY = 0.002f;
    const float GRAVITY_CAP = 0.8f;
}

Player::Player(){
}

Player::Player(Vector2 spawnPoint) :
AnimatedSprite("Images/bunny.png", 0, 0, 145, 105, spawnPoint.x, spawnPoint.y, 100){
    
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
    this->addAnimation(1, 0, 210, "JumpLeft", 145, 105, Vector2(0,0));
    this->addAnimation(1, 1, 210, "JumpRight", 145, 105, Vector2(0,0));
}

void printAnimations(){

}

void Player::animationDone(std::string currentAnimation){
}

const float Player::getX() const {
    return this->x;
}

const float Player::getY() const {
    return this->y;
}

void Player::moveLeft() {
    if (this->grounded == true) {
        return;
    }
    this->dx = -player_constants::WALK_SPEED;
    this->playAnimation("RunLeft");
    this->facing = LEFT;
}

void Player::moveRight() {
    if (this->grounded == true) {
        return;
    }
    this->dx = player_constants::WALK_SPEED;
    this->playAnimation("RunRight");
    this->facing = RIGHT;
}

void Player::stopMoving() {
    this->dx = 0.0f;
    this->playAnimation(this->facing == RIGHT ? "IdleRight" : "IdleLeft");
}


void Player::jump() {
    if (this->grounded) {
        this->dy = 0;
        this->dy -= player_constants::JUMP_SPEED;
        this->grounded = false;
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
    /*
    //Apply gravity
    if (dy <= player_constants::GRAVITY_CAP) {
        dy += player_constants::GRAVITY * elapsedTime;
    }*/
    std::cout << "y: " << y << std::endl;
    std::cout << "x: " << x << std::endl;
    
    //Move by dx
    x += dx * elapsedTime;
    //Move by dy
    y += dy * elapsedTime;
    
    AnimatedSprite::update(elapsedTime);
}

void Player::draw(){
    AnimatedSprite::draw(x, y);
}
