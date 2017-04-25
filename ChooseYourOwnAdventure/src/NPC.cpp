//
//  NPC.cpp
//  ChooseYourOwnAdventure
//
//  Created by Peter Chheu on 4/25/17.
//  Copyright © 2017 Peter Chheu. All rights reserved.
//

#include "NPC.hpp"

NPC::NPC(){
}

NPC::NPC(Vector2 spawnPoint) :
AnimatedSprite("Images/owlsprite.png", 0, 300, 85, 131, spawnPoint.x, spawnPoint.y, 150){
    spawn = spawnPoint;
    
    dx = 0;
    dy = 0;
    
    this->setupAnimations();
    this->playAnimation("IdleLeft");
}

void NPC::setupAnimations() {
    this->addAnimation(3, 0, 0, "Idle", 85, 131, Vector2(0,0));
}

void NPC::animationDone(std::string currentAnimation){
}

void NPC::update(float elapsedTime){
    AnimatedSprite::update(elapsedTime);
}

void NPC::draw(){
    AnimatedSprite::draw(x, y);
}
