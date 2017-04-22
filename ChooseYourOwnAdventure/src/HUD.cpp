//
//  HUD.cpp
//  ChooseYourOwnAdventure
//
//  Created by Peter Chheu on 4/17/17.
//  Copyright © 2017 Peter Chheu. All rights reserved.
//

#include "HUD.hpp"

HUD::HUD(){
    visible = false;
    
    messageRect.x = Camera::getCamX() + 400;
    messageRect.y = Camera::getCamY() - 300;
    messageRect.w = 100;
    messageRect.h = 100;
}

void HUD::display(){
    visible = true;
}

void HUD::hide(){
    visible = false;
}

void HUD::setupDialogue(){
    
}
