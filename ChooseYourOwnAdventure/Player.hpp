//
//  Player.cpp
//  ChooseYourOwnAdventure
//
//  Created by Peter Chheu on 3/24/17.
//  Copyright © 2017 Peter Chheu. All rights reserved.
//

#include "AnimatedSprite.hpp"
#include "SDL2/SDL.h"
#include "SDL2_image/SDL_image.h"
//#include "Map.hpp"

enum Direction {
    LEFT,
    RIGHT,
    UP,
    DOWN
};

class Player : public AnimatedSprite {
public:
    Player();
    Player(Vector2 spawnPoint);
    void draw();
    void update(float elapsedTime);
    
    /* void moveLeft
     * Moves the player left by -dx
     */
    void moveLeft();
    
    /* void moveRight
     * Moves the player right by dx
     */
    void moveRight();
    
    /* void stopMoving
     * Stops moving the player
     */
    void stopMoving();
    
    /* void jump
     * Starts jumping
     */
    void jump();
    
    virtual void animationDone(std::string currentAnimation);
    virtual void setupAnimations();
    
    void handleTileCollisions(std::vector<Rectangle> &others);
    
    const float getX() const;
    const float getY() const;
    
private:
    SDL_Window* window = SDL_GL_GetCurrentWindow();
    SDL_Renderer* renderer = SDL_GetRenderer(window);
    float _dx, _dy;
    
    Direction _facing;
    
    bool _grounded;
};
