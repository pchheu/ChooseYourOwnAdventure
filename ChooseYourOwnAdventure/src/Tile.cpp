//
//  Tile.cpp
//  ChooseYourOwnAdventure
//
//  Created by Peter Chheu on 3/15/17.
//  Copyright © 2017 Peter Chheu. All rights reserved.
//

#include "Tile.hpp"

Tile::Tile(){
}

Tile::Tile(SDL_Texture* tileset, Vector2 size, Vector2 tilesetPosition, Vector2 position) :
_tileset(tileset),
_size(size),
_tilesetPosition(tilesetPosition),
_position(Vector2(position.x, position.y)){
}

void Tile::update(int elapsedTime) {}

void Tile::draw() {
    SDL_Rect destRect = { this->_position.x, this->_position.y, this->_size.x, this->_size.y};
    SDL_Rect sourceRect = { this->_tilesetPosition.x, this->_tilesetPosition.y, this->_size.x, this->_size.y };

    SDL_RenderCopy(renderer, _tileset, &sourceRect, &destRect);
}
