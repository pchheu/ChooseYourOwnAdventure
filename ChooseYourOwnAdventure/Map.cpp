//
//  Map.cpp
//  ChooseYourOwnAdventure
//
//  Created by Peter Chheu on 2/21/17.
//  Copyright © 2017 Peter Chheu. All rights reserved.
//

#include "Map.hpp"

Map::Map(const char *path){
    map_surface = IMG_Load(path);
    
    if(map_surface == nullptr){
        std::cout << "Error: Could not load image" << std::endl;
    }
    
    window = SDL_GL_GetCurrentWindow();
    renderer = SDL_GetRenderer(window);
    map_texture = SDL_CreateTextureFromSurface(renderer, map_surface);
    SDL_FreeSurface(map_surface);
}

Map::~Map(){
    
}

void Map::renderMap(){
    SDL_RenderCopy(renderer, map_texture, NULL, NULL);
}

void Map::destroyMap(){
    /* Unsure if these exit the program or just delete the local variables
     
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
     
    */
}
