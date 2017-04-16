//
//  Tile.hpp
//  ChooseYourOwnAdventure
//
//  Created by Peter Chheu on 3/15/17.
//  Copyright © 2017 Peter Chheu. All rights reserved.
//

#include <iostream>
#include "SDL2/SDL.h"
#include "SDL2_image/SDL_image.h"
#include <OpenGL/gl.h>
#include <stdio.h>
#include <fstream>
#include "Vector2.h"
#include "Camera.hpp"

class Tile {
public:
    Tile();
    Tile(SDL_Texture* tileset, Vector2 size, Vector2 tilesetPosition, Vector2 position);
    void update(int elapsedTime);
    void draw();
    
protected:
    SDL_Texture* _tileset;
    Vector2 _size;
    Vector2 _tilesetPosition;
    Vector2 _position;
    
    SDL_Window* window = SDL_GL_GetCurrentWindow();
    SDL_Renderer* renderer = SDL_GetRenderer(window);
};
