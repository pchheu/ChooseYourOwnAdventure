//
//  MainMenu.cpp
//  ChooseYourOwnAdventure
//
//  Created by Peter Chheu on 4/22/17.
//  Copyright © 2017 Peter Chheu. All rights reserved.
//

#include "MainMenu.hpp"

MainMenu::MainMenu(){
    
}

MainMenu::~MainMenu(){
    
}

MainMenu::MainMenu(char* filePath, int w, int h){
    screenWidth = w;
    screenHeight = h;
    
    menu_surface = IMG_Load(filePath);
    menu_texture = SDL_CreateTextureFromSurface(renderer, menu_surface);
    
    SDL_FreeSurface(menu_surface);
    
    background.x = 0;
    background.y = 0;
    background.w = screenWidth;
    background.h = screenHeight;
    
    playButton.x = 375;
    playButton.y = 430;
    playButton.w = 343;
    playButton.h = 137;
}

void MainMenu::draw(){
    SDL_RenderCopy(renderer, menu_texture, NULL, &background);
}

int MainMenu::handlePlay(){
    SDL_Event evnt;
    bool inside = true;
    
    while(SDL_PollEvent(&evnt) == true){
        if(evnt.type == SDL_MOUSEBUTTONDOWN){
            //Get mouse position
            int x,y;
            SDL_GetMouseState(&x, &y);
            
            //Mouse is inside the buttons
            if(x < playButton.x){
                inside = false;
            }
            
            //Mouse is right of the buttons
            if(x > playButton.x + playButton.w){
                inside = false;
            }
            
            //Mouse is above the buttons
            if(y < playButton.y){
                inside = false;
            }
            
            //Mouse is below the buttons
            if(y > playButton.y + playButton.h){
                inside = false;
            }
            
            //Mouse is over the buttons
            if(inside == true){
                return 1;
                std::cout << "Play pressed" << std::endl;
            }
        }
    }
    return 0;
}
