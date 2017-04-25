//
//  NPC.hpp
//  ChooseYourOwnAdventure
//
//  Created by Peter Chheu on 4/25/17.
//  Copyright © 2017 Peter Chheu. All rights reserved.
//

#ifndef NPC_hpp
#define NPC_hpp

#include "AnimatedSprite.hpp"

class NPC : public AnimatedSprite{
public:
    NPC();
    NPC(Vector2 spawnPoint);
    
    void draw();
    void update(float elapsedTime);
    
    virtual void animationDone(std::string currentAnimation);
    virtual void setupAnimations();
    
    float getX();
    float getY();
    
private:
    SDL_Window* window = SDL_GL_GetCurrentWindow();
    SDL_Renderer* renderer = SDL_GetRenderer(window);
    
    Vector2 spawn;
    
    float dx, dy;

};
#endif /* NPC_hpp */
