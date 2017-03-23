//
//  Map.cpp
//  ChooseYourOwnAdventure
//
//  Created by Peter Chheu on 2/21/17.
//  Copyright © 2017 Peter Chheu. All rights reserved.
//

#include "Map.hpp"

Map::Map(){
    
}

Map::~Map(){
    
}

void Map::mapInit(const char *path, std::string name){
    map_surface = IMG_Load(path);
    
    if(map_surface == nullptr){
        std::cout << "Error: Could not load map image" << std::endl;
    }
    
    window = SDL_GL_GetCurrentWindow();
    renderer = SDL_GetRenderer(window);
    map_texture = SDL_CreateTextureFromSurface(renderer, map_surface);
    
    map_name = name;
}

void Map::renderMap(SDL_Rect c){
    SDL_RenderCopy(renderer, map_texture, &c, NULL);
}

void Map::destroyMap(){
    /* Unsure if these exit the program or just delete the local variables
     
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
     
    */
}

void Map::updateCamera(SDL_Rect c){
    camera = c;
}

int Map::getlevelWidth(){
    return map_surface->w;
}

int Map::getlevelHeight(){
    return map_surface->h;
}

SDL_Surface* Map::getMapSurface(){
    return map_surface;
}
