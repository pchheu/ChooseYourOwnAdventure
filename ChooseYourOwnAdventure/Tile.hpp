//
//  Tile.hpp
//  ChooseYourOwnAdventure
//
//  Created by Peter Chheu on 3/15/17.
//  Copyright © 2017 Peter Chheu. All rights reserved.
//
/*
#include "MainGame.hpp"
#include <iostream>
#include "SDL2/SDL.h"
#include "SDL2_image/SDL_image.h"
#include <OpenGL/gl.h>
#include <stdio.h>

class Tile{
public:
    enum ETile { NOTHING, WALL, KILL, NTILES };
    
    static const int SIZE_X;
    static const int SIZE_Y;
    
private:
    static SDL_Texture (*pTextures)[NTILES]; // Array of pointer, point to the textures you want your tiles to look like
    SDL_Rect mRenderRect; /// Rectangle you draw to
    SDL_Renderer* renderer = SDL_GetRenderer(window);
    
public:
    Tile(){
        mRenderRect.w = SIZE_X; mRenderRect.h = SIZE_Y;
    }
    void InitTextures(){
        /* Load the Textures you want your tiles to be
    }
    
    ETile tile; // Which tile is this?
    
    void render(int PositionX, int PositionY){
        mRenderRect.x = PositionX; mRenderRect.y = PositionY;
        SDL_Render(renderer, &pTextures[tile], NULL, &DestRect() )
    }
};
int Tile::SIZE_X = 32;
int Tile::SIZE_Y = 32;

SDL_Texture (*Tile::pTextures)[NTILES];

// somewhere in main.cpp
const int TILES_X = 50;
const int TILES_Y = 50; //50x50 map
Tile MAP[TILES_X][TILES_Y];
*/
