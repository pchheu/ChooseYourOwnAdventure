//
//  Map.cpp
//  ChooseYourOwnAdventure
//
//  Created by Peter Chheu on 2/21/17.
//  Copyright © 2017 Peter Chheu. All rights reserved.
//
#include "Map.hpp"
#include <algorithm>
#include <cmath>
#include <sstream>
#include "tinyxml2.h"

using namespace tinyxml2;

Map::Map(){
    
}

Map::~Map(){
    
}

void Map::mapInit(const char *path, std::string name){
    map_surface = IMG_Load(path);
    
    if(map_surface == nullptr){
        std::cout << "Error: Could not load map image" << std::endl;
    }
    map_texture = SDL_CreateTextureFromSurface(renderer, map_surface);
    
    mapName = name;
}

void Map::draw(SDL_Rect c){
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

void Map::renderMap(char* mapName) {
    //Parse the .tmx file
    std::stringstream ss;
    ss << "Maps/" << mapName << ".tmx"; //Pass in Map 1, we get maps/Map 1.tmx
    XMLDocument doc(ss.str().c_str());
    
    XMLElement* mapNode = doc.FirstChildElement("map");
    
    if(mapNode == nullptr){
        std::cout << "Unable to retreive first node" << std::endl;
    }
    
    
    //Get the width and the height of the whole map and store it in _size
    int width, height;
    mapNode->QueryIntAttribute("width", &width);
    mapNode->QueryIntAttribute("height", &height);
    this->_size = Vector2(width, height);
    
    //Get the width and the height of the tiles and store it in _tileSize
    int tileWidth, tileHeight;
    mapNode->QueryIntAttribute("tilewidth", &tileWidth);
    mapNode->QueryIntAttribute("tileheight", &tileHeight);
    this->_tileSize = Vector2(tileWidth, tileHeight);
    
    //Loading the tilesets
    XMLElement* pTileset = mapNode->FirstChildElement("tileset");
    if (pTileset != NULL) {
        while (pTileset) {
            int firstgid;
            const char* source = pTileset->FirstChildElement("image")->Attribute("source");
            char* path;
            std::stringstream ss;
            ss << source;
            pTileset->QueryIntAttribute("firstgid", &firstgid);
            SDL_Surface* img = IMG_Load(ss.str().c_str());
            SDL_Texture* tex = SDL_CreateTextureFromSurface(renderer, img);
            this->_tilesets.push_back(Tileset(tex, firstgid));
            
            /*
            //Get all of the animations for that tileset
            XMLElement* pTileA = pTileset->FirstChildElement("tile");
            if (pTileA != NULL) {
                while (pTileA) {
                    AnimatedTileInfo ati;
                    ati.StartTileId = pTileA->IntAttribute("id") + firstgid;
                    ati.TilesetsFirstGid = firstgid;
                    XMLElement* pAnimation = pTileA->FirstChildElement("animation");
                    if (pAnimation != NULL) {
                        while (pAnimation) {
                            XMLElement* pFrame = pAnimation->FirstChildElement("frame");
                            if (pFrame != NULL) {
                                while (pFrame) {
                                    ati.TileIds.push_back(pFrame->IntAttribute("tileid") + firstgid);
                                    ati.Duration = pFrame->IntAttribute("duration");
                                    pFrame = pFrame->NextSiblingElement("frame");
                                }
                            }
                            pAnimation = pAnimation->NextSiblingElement("animation");
                        }
                    }
                    this->_animatedTileInfos.push_back(ati);
                    pTileA = pTileA->NextSiblingElement("tile");
                }
            }
            pTileset = pTileset->NextSiblingElement("tileset");
            */
        }
    }
    
    //Loading the layers
    XMLElement* pLayer = mapNode->FirstChildElement("layer");
    if (pLayer != NULL) {
        while (pLayer) {
            //Loading the data element
            XMLElement* pData = pLayer->FirstChildElement("data");
            if (pData != NULL) {
                while (pData) {
                    //Loading the tile element
                    XMLElement* pTile = pData->FirstChildElement("tile");
                    if (pTile != NULL) {
                        int tileCounter = 0;
                        while (pTile) {
                            //Build each individual tile here
                            //If gid is 0, no tile should be drawn. Continue loop
                            if (pTile->IntAttribute("gid") == 0) {
                                tileCounter++;
                                if (pTile->NextSiblingElement("tile")) {
                                    pTile = pTile->NextSiblingElement("tile");
                                    continue;
                                }
                                else {
                                    break;
                                }
                            }
                            
                            //Get the tileset for this specific gid
                            int gid = pTile->IntAttribute("gid");
                            Tileset tls;
                            int closest = 0;
                            for (int i = 0; i < this->_tilesets.size(); i++) {
                                if (this->_tilesets[i].FirstGid <= gid) {
                                    if (this->_tilesets[i].FirstGid > closest) {
                                        closest = this->_tilesets[i].FirstGid;
                                        tls = this->_tilesets.at(i);
                                    }
                                }
                            }
                            
                            if (tls.FirstGid == -1) {
                                //No tileset was found for this gid
                                tileCounter++;
                                if (pTile->NextSiblingElement("tile")) {
                                    pTile = pTile->NextSiblingElement("tile");
                                    continue;
                                }
                                else {
                                    break;
                                }
                            }
                            
                            //Get the position of the tile in the level
                            int xx = 0;
                            int yy = 0;
                            xx = tileCounter % width;
                            xx *= tileWidth;
                            yy += tileHeight * (tileCounter / width);
                            Vector2 finalTilePosition = Vector2(xx, yy);
                            
                            //Calculate the position of the tile in the tileset
                            Vector2 finalTilesetPosition = this->getTilesetPosition(tls, gid, tileWidth, tileHeight);
                            
                            //Build the actual tile and add it to the level's tile list
                            /*
                            bool isAnimatedTile = false;
                            AnimatedTileInfo ati;
                            for (int i = 0; i < this->_animatedTileInfos.size(); i++) {
                                if (this->_animatedTileInfos.at(i).StartTileId == gid) {
                                    ati = this->_animatedTileInfos.at(i);
                                    isAnimatedTile = true;
                                    break;
                                }
                            }
                            if (isAnimatedTile == true) {
                                std::vector<Vector2> tilesetPositions;
                                for (int i = 0; i < ati.TileIds.size(); i++) {
                                    tilesetPositions.push_back(this->getTilesetPosition(tls, ati.TileIds.at(i),
                                                                                        tileWidth, tileHeight));
                                }
                                AnimatedTile tile(tilesetPositions, ati.Duration,
                                                  tls.Texture, Vector2(tileWidth, tileHeight), finalTilePosition);
                                this->_animatedTileList.push_back(tile);
                            }
                            else {*/
                                Tile tile(tls.Texture, Vector2(tileWidth, tileHeight),
                                          finalTilesetPosition, finalTilePosition);
                                this->_tileList.push_back(tile);
                            //}
                            tileCounter++;
                            pTile = pTile->NextSiblingElement("tile");
                        }
                    }
                    
                    pData = pData->NextSiblingElement("data");
                }
            }
            
            pLayer = pLayer->NextSiblingElement("layer");
        }
    }
    
    //Parse out the collisions
    XMLElement* pObjectGroup = mapNode->FirstChildElement("objectgroup");
    if (pObjectGroup != NULL) {
        while (pObjectGroup) {
            const char* name = pObjectGroup->Attribute("name");
            std::stringstream ss;
            ss << name;
            if (ss.str() == "collisions") {
                XMLElement* pObject = pObjectGroup->FirstChildElement("object");
                if (pObject != NULL) {
                    while (pObject) {
                        float x, y, width, height;
                        x = pObject->FloatAttribute("x");
                        y = pObject->FloatAttribute("y");
                        width = pObject->FloatAttribute("width");
                        height = pObject->FloatAttribute("height");
                        this->_collisionRects.push_back(Rectangle(
                                                                  std::ceil(x),
                                                                  std::ceil(y),
                                                                  std::ceil(width),
                                                                  std::ceil(height)
                                                                  ));
                        
                        pObject = pObject->NextSiblingElement("object");
                    }
                }
            }
            if (ss.str() == "spawn points") {
                XMLElement* pObject = pObjectGroup->FirstChildElement("object");
                if (pObject != NULL) {
                    while (pObject) {
                        float x = pObject->FloatAttribute("x");
                        float y = pObject->FloatAttribute("y");
                        const char* name = pObject->Attribute("name");
                        std::stringstream ss;
                        ss << name;
                        if (ss.str() == "player") {
                            this->_spawnPoint = Vector2(std::ceil(x),
                                                        std::ceil(y));
                        }
                        
                        pObject = pObject->NextSiblingElement("object");
                    }
                }
            }
            /*
            else if (ss.str() == "doors") {
                XMLElement* pObject = pObjectGroup->FirstChildElement("object");
                if (pObject != NULL) {
                    while (pObject) {
                        float x = pObject->FloatAttribute("x");
                        float y = pObject->FloatAttribute("y");
                        float w = pObject->FloatAttribute("width");
                        float h = pObject->FloatAttribute("height");
                        Rectangle rect = Rectangle(x, y, w, h);
                        
                        XMLElement* pProperties = pObject->FirstChildElement("properties");
                        if (pProperties != NULL) {
                            while (pProperties) {
                                XMLElement* pProperty = pProperties->FirstChildElement("property");
                                if (pProperty != NULL) {
                                    while (pProperty) {
                                        const char* name = pProperty->Attribute("name");
                                        std::stringstream ss;
                                        ss << name;
                                        if (ss.str() == "destination") {
                                            const char* value = pProperty->Attribute("value");
                                            std::stringstream ss2;
                                            ss2 << value;
                                            Door door = Door(rect, ss2.str());
                                            this->_doorList.push_back(door);
                                        }
                                        pProperty = pProperty->NextSiblingElement("property");
                                    }
                                }
                                pProperties = pProperties->NextSiblingElement("properties");
                            }
                        }
                        
                        pObject = pObject->NextSiblingElement("object");
                    }
                }
            }*/
            /*
            else if (ss.str() == "enemies") {
                float x, y;
                XMLElement* pObject = pObjectGroup->FirstChildElement("object");
                if (pObject != NULL) {
                    while (pObject) {
                        x = pObject->FloatAttribute("x");
                        y = pObject->FloatAttribute("y");
                        const char* name = pObject->Attribute("name");
                        std::stringstream ss;
                        ss << name;
                        if (ss.str() == "bat") {
                            this->_enemies.push_back(new Bat(graphics, Vector2(std::floor(x) * globals::SPRITE_SCALE,
                                                                               std::floor(y) * globals::SPRITE_SCALE)));
                        }
                        
                        pObject = pObject->NextSiblingElement("object");
                    }
                }
            }*/
            
            pObjectGroup = pObjectGroup->NextSiblingElement("objectgroup");
        }
    }
}

std::vector<Rectangle> Map::checkTileCollisions(const Rectangle &other) {
    std::vector<Rectangle> others;
    for (int i = 0; i < this->_collisionRects.size(); i++) {
        if (this->_collisionRects.at(i).collidesWith(other)) {
            others.push_back(this->_collisionRects.at(i));
        }
    }
    return others;
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

const Vector2 Map::getPlayerSpawnPoint() const {
    return this->_spawnPoint;
}

Vector2 Map::getTilesetPosition(Tileset tls, int gid, int tileWidth, int tileHeight) {
    int tilesetWidth, tilesetHeight;
    SDL_QueryTexture(tls.Texture, NULL, NULL, &tilesetWidth, &tilesetHeight);
    int tsxx = gid % (tilesetWidth / tileWidth) - 1;
    tsxx *= tileWidth;
    int tsyy = 0;
    int amt = ((gid - tls.FirstGid) / (tilesetWidth / tileWidth));
    tsyy = tileHeight * amt;
    Vector2 finalTilesetPosition = Vector2(tsxx, tsyy);
    return finalTilesetPosition;
}

bool Map::Test(){
    XMLDocument xml_doc;
    
    XMLError eResult = xml_doc.LoadFile("test.xml");
    if (eResult != XML_SUCCESS) return false;
    
    XMLNode* root = xml_doc.FirstChildElement("to");
    if (root == nullptr) return false;
    
    XMLElement* element = root->FirstChildElement("from");
    if (element == nullptr) return false;
    
    return true;
}
