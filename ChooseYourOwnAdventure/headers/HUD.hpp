//
//  HUD.hpp
//  ChooseYourOwnAdventure
//
//  Created by Peter Chheu on 4/17/17.
//  Copyright © 2017 Peter Chheu. All rights reserved.
//

#ifndef HUD_hpp
#define HUD_hpp

#include <stdio.h>
#include <iostream>
#include <map>
#include "SDL2/SDL.h"
#include "SDL2_image/SDL_image.h"
#include "Camera.hpp"

class HUD{
public:
    HUD();
    ~HUD();
    
    void display();
    void hide();
    void setupDialogue();
    
private:
    SDL_Rect messageRect;
    SDL_Surface* surfaceMsg;
    SDL_Texture* message;
    bool visible;
    
    SDL_Window* window = SDL_GL_GetCurrentWindow();
    SDL_Renderer* renderer = SDL_GetRenderer(window);
};

struct node{
    std::string dialogue;
    node *left;
    node *right;
};

#endif /* HUD_hpp */
