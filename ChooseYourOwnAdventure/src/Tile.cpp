//
//  Tile.cpp
//  ChooseYourOwnAdventure
//
//  Created by Peter Chheu on 3/15/17.
//  Copyright © 2017 Peter Chheu. All rights reserved.
//

#include "Tile.hpp"

//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

//Tile constants
const int TILE_WIDTH = 100;
const int TILE_HEIGHT = 100;

Tile::Tile( int x, int y, int tileType ){
    //Get the offsets
    mBox.x = x;
    mBox.y = y;
    
    //Set the collision box
    mBox.w = TILE_WIDTH;
    mBox.h = TILE_HEIGHT;
    
    //Get the tile type
    mType = tileType;
}

/*
void Tile::render( SDL_Rect& camera ){
    //If the tile is on screen
    if( checkCollision( camera, mBox ) )
    {
        //Show the tile
        gTileTexture.render( mBox.x - camera.x, mBox.y - camera.y, &gTileClips[ mType ] );
    }
}
*/
