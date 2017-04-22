//
//  MainMenu.hpp
//  ChooseYourOwnAdventure
//
//  Created by Peter Chheu on 4/22/17.
//  Copyright © 2017 Peter Chheu. All rights reserved.
//

#ifndef MainMenu_hpp
#define MainMenu_hpp

#include "SDL2/SDL.h"
#include "SDL2_image/SDL_image.h"
#include <stdio.h>
#include <string>
#include <fstream>

class MainMenu{
    
public:
    MainMenu(int w, int h);
    ~MainMenu();
    
    void draw();
    void handlePlay();
    void handleLoad();
    
private:
    int screenWidth;
    int screenHeight;
    
    SDL_Rect playButton;
    SDL_Rect loadButton;
    
    SDL_Surface* menu_surface;
    SDL_Texture* menu_texture;
    
    SDL_Surface* playButton_surface;
    SDL_Texture* playButton_texture;
    
    SDL_Surface* loadButton_surface;
    SDL_Texture* loadButton_texture;

    SDL_Rect menu;
};
#endif /* MainMenu_hpp */
