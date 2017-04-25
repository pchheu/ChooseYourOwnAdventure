//
//  Portal.cpp
//  ChooseYourOwnAdventure
//
//  Created by Peter Chheu on 4/25/17.
//  Copyright © 2017 Peter Chheu. All rights reserved.
//

#include "Portal.hpp"

Portal::Portal(){
    
}

Portal::Portal(const char* filePath, Vector2 spawn):
AnimatedSprite(filePath, 0, 300, 131, 187, spawn.x, spawn.y, 0){
    posX = spawn.x;
    posY = spawn.y;
    
    this->setupAnimations();
    this->playAnimation("door");
}

void Portal::draw(){    
    AnimatedSprite::draw(posX, posY);
}

void Portal::animationDone(std::string currentAnimation){
}

void Portal::setupAnimations(){
    this->addAnimation(1, 0, 0, "door", 131, 181, Vector2(0, 0));
}
