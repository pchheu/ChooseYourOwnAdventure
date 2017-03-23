//
//  Map.hpp
//  ChooseYourOwnAdventure
//
//  Created by Peter Chheu on 2/21/17.
//  Copyright © 2017 Peter Chheu. All rights reserved.
//

#pragma once

#include <iostream>
#include "SDL2/SDL.h"
#include "SDL2_image/SDL_image.h"
#include <OpenGL/gl.h>
#include <stdio.h>
#include <fstream>
#include <string>

class Map{
public:
    Map();
    ~Map();
    
    void mapInit(const char* path, std::string name);
    void renderMap(SDL_Rect c);
    void destroyMap();
    void updateCamera(SDL_Rect c);
    
    int getlevelWidth();
    int getlevelHeight();
    
    SDL_Surface* getMapSurface();
    
private:
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Texture* map_texture;
    SDL_Surface* map_surface;
    
    std::string map_name;
    
    SDL_Rect camera;
};
