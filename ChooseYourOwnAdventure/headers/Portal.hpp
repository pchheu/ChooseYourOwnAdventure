//
//  Portal.hpp
//  ChooseYourOwnAdventure
//
//  Created by Peter Chheu on 4/25/17.
//  Copyright © 2017 Peter Chheu. All rights reserved.
//

#ifndef Portal_hpp
#define Portal_hpp

#include <iostream>
#include <stdio.h>
#include "SDL2/SDL.h"
#include "SDL2_image/SDL_image.h"
#include "Vector2.h"
#include "Map.hpp"
#include "AnimatedSprite.hpp"

class Portal : public AnimatedSprite{
public:
    Portal();
    Portal(const char* filePath, Vector2 spawn);
    
    void loadNextMap(Map m);
    
    virtual void animationDone(std::string currentAnimation);
    virtual void setupAnimations();
    
    void draw();
    
private:
    SDL_Window* window = SDL_GL_GetCurrentWindow();
    SDL_Renderer* renderer = SDL_GetRenderer(window);
    
    SDL_Surface* portalSurface;
    SDL_Texture* portalTexture;
    
    float posX, posY;
    
    SDL_Rect portalRect;
    
    Vector2 spawn;
    
};

#endif /* Portal_hpp */
