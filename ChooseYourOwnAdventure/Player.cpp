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

Player::Player() {}

Player::Player(Vector2 spawnPoint) :
AnimatedSprite("spritesheets/bunnyspritesheet.png", 0, 0, 118, 185, spawnPoint.x, spawnPoint.y, 100),
_dx(0),
_dy(0),
_facing(RIGHT),
_grounded(false)
{
    SDL_Surface* player = IMG_Load("Images/bunnyspritesheet.png");
    if(player == nullptr){
        std::cout << "Could not open the image" << std::endl;
    }
    
    this->setupAnimations();
    this->playAnimation("IdleRight");
}

void Player::setupAnimations() {
    this->addAnimation(1, 0, 0, "IdleLeft", 139, 97, Vector2(0,0));
    this->addAnimation(1, 1, 1, "IdleRight", 139, 97, Vector2(0,0));
    this->addAnimation(3, 1, 1, "RunLeft", 139, 97, Vector2(0,0));
    this->addAnimation(3, 0, 0, "RunRight", 139, 97, Vector2(0,0));
    this->addAnimation(1, 0, 3, "RunLeftUp", 16, 16, Vector2(0,0));
    this->addAnimation(3, 3, 16, "RunRightUp", 16, 16, Vector2(0,0));
}

void Player::animationDone(std::string currentAnimation) {}

const float Player::getX() const {
    return this->x;
}

const float Player::getY() const {
    return this->y;
}

void Player::moveLeft() {
    if (this->_grounded == true) {
        return;
    }
    this->_dx = -player_constants::WALK_SPEED;
    this->playAnimation("RunLeft");
    this->_facing = LEFT;
}

void Player::moveRight() {
    if (this->_grounded == true) {
        return;
    }
    this->_dx = player_constants::WALK_SPEED;
    this->playAnimation("RunRight");
    this->_facing = RIGHT;
}

void Player::stopMoving() {
    this->_dx = 0.0f;
    this->playAnimation(this->_facing == RIGHT ? "IdleRight" : "IdleLeft");
}


void Player::jump() {
    if (this->_grounded) {
        this->_dy = 0;
        this->_dy -= player_constants::JUMP_SPEED;
        this->_grounded = false;
    }
}

//void handleTileCollisions
//Handles collisions with ALL tiles the player is colliding with
void Player::handleTileCollisions(std::vector<Rectangle> &others) {
    //Figure out what side the collision happened on and move the player accordingly
    for (int i = 0; i < others.size(); i++) {
        sides::Side collisionSide = Sprite::getCollisionSide(others.at(i));
        if (collisionSide != sides::NONE) {
            switch (collisionSide) {
                case sides::TOP:
                    this->_dy = 0;
                    this->y = others.at(i).getBottom() + 1;
                    if (this->_grounded) {
                        this->_dx = 0;
                        this->x -= this->_facing == RIGHT ? 1.0f : -1.0f;
                    }
                    
                    break;
                case sides::BOTTOM:
                    this->y = others.at(i).getTop() - this->boundingBox.getHeight() - 1;
                    this->_dy = 0;
                    this->_grounded = true;
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
    if (this->_dy <= player_constants::GRAVITY_CAP) {
        this->_dy += player_constants::GRAVITY * elapsedTime;
    }
    
    //Move by dx
    this->x += this->_dx * elapsedTime;
    //Move by dy
    this->y += this->_dy * elapsedTime;
    
    AnimatedSprite::update(elapsedTime);
}

void Player::draw() {
    AnimatedSprite::draw(this->x, this->y);
}
