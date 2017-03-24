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
#include <string>
#include "Vector2.h"
#include <vector>
#include "Tile.hpp"
#include "Rectangle.hpp"

struct Tileset;

class Map{
public:
    Map();
    ~Map();
    
    void mapInit(const char* path, std::string name);
    void draw(SDL_Rect c);
    void renderMap(std::string mapName);
    void destroyMap();
    void updateCamera(SDL_Rect c);
    
    int getlevelWidth();
    int getlevelHeight();
    
    std::vector<Rectangle> checkTileCollisions(const Rectangle &other);
    
    const Vector2 getPlayerSpawnPoint() const;
    
    SDL_Surface* getMapSurface();
    
private:
    SDL_Window* window = SDL_GL_GetCurrentWindow();
    SDL_Renderer* renderer = SDL_GetRenderer(window);
    SDL_Texture* map_texture;
    SDL_Surface* map_surface;
    
    std::string mapName;
    
    Vector2 _spawnPoint;
    Vector2 _size;
    Vector2 _tileSize;
    
    std::vector<Tile> _tileList;
    std::vector<Tileset> _tilesets;
    std::vector<Rectangle> _collisionRects;
    
    Vector2 getTilesetPosition(Tileset tls, int gid, int tileWidth, int tileHeight);
    
    SDL_Rect camera;
};

struct Tileset{
    SDL_Texture* Texture;
    int FirstGid;
    Tileset(){
        this->FirstGid = -1;
    }
    Tileset(SDL_Texture* texture, int firstGid){
        this->Texture = texture;
        this->FirstGid = firstGid;
    }
};
