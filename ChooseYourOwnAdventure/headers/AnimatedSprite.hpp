//
//  AnimatedSprite.hpp
//  ChooseYourOwnAdventure
//
//  Created by Peter Chheu on 3/23/17.
//  Copyright © 2017 Peter Chheu. All rights reserved.
//

#include <stdio.h>
#include "Sprite.hpp"
#include "Vector2.h"
#include <map>
#include <vector>
#include "SDL2/SDL.h"
#include "SDL2_image/SDL_image.h"

class AnimatedSprite : public Sprite{
public:
    AnimatedSprite();
    
    AnimatedSprite(const std::string filePath,
                   int sourceX,
                   int sourceY,
                   int width,
                   int height,
                   float posX,
                   float posY,
                   float ntimeToUpdate);

     //Plays the animation provided if it's not already playing
    void playAnimation(std::string animation, bool once = false);

    //Updates the animated sprite (timer)
    void update(int elapsedTime);
    
    //Draws the sprite to the screen
    void draw(int x, int y);
    
    //Sets up default animations
    virtual void setupAnimations();
    
protected:
    double timeToUpdate;
    bool currentAnimationOnce;
    std::string currentAnimation;
    
    void addAnimation(int frames, int x, int y, std::string name, int width, int height, Vector2 offset);
    
    void resetAnimations();
    
    void stopAnimation();
    
    void setVisible(bool visible);
    
    //Logic that happens when an animation ends
    virtual void animationDone(std::string currentAnimation) = 0;
    
private:
    SDL_Window* window;
    SDL_Renderer* renderer;
    
    std::map<std::string, std::vector<SDL_Rect>> animations;
    std::map<std::string, Vector2> offsets;
    
    int frameIndex;
    double timeElapsed;
    bool visible;
};
