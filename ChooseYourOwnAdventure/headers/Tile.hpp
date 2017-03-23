//
//  Tile.hpp
//  ChooseYourOwnAdventure
//
//  Created by Peter Chheu on 3/15/17.
//  Copyright © 2017 Peter Chheu. All rights reserved.
//

#include "MainGame.hpp"
#include <iostream>
#include "SDL2/SDL.h"
#include "SDL2_image/SDL_image.h"
#include <OpenGL/gl.h>
#include <stdio.h>
#include <fstream>

class Tile
{
public:
    //Initializes position and type
    Tile( int x, int y, int tileType );
    
    //Shows the tile
    void render( SDL_Rect& camera );
    
    //Get the tile type
    int getType();
    
    //Get the collision box
    SDL_Rect getBox();
    
private:
    //The attributes of the tile
    SDL_Rect mBox;
    
    //The tile type
    int mType;
};
