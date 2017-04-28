//
//  DialogueTree.hpp
//  ChooseYourOwnAdventure
//
//  Created by Peter Chheu on 4/22/17.
//  Copyright © 2017 Peter Chheu. All rights reserved.
//

#ifndef DialogueTree_hpp
#define DialogueTree_hpp

#include <stdio.h>
#include <unistd.h>
#include <string>
#include <iostream>
#include <vector>
#include "SDL2/SDL.h"
#include "SDL2_image/SDL_image.h"
#include "SDL2_ttf/SDL_ttf.h"
#include "Errors.hpp"
#include "Camera.hpp"
#include "Player.hpp"

using namespace std;

enum class WORLDSTATE{PAINTEDWORLD, UNPAINTEDWORLD};
enum class BUTTONSTATE{BUTTON1, BUTTON2, NEUTRAL};

class DialogueNode;

class DialogueOption{
public:
    DialogueOption(string _text, int _returnCode, DialogueNode *_nextNode);
    string text;
    int returnCode;
    DialogueNode *nextNode;
};

class DialogueNode{
public:
    DialogueNode(string _text);
    string text;
    vector<DialogueOption> dialogueOptions;
};

class DialogueTree{
public:
    DialogueTree();
    
    void init();
    void destroyTree();
    
    bool hasTalked();
    
    WORLDSTATE performDialogue(int playerX, int playerY, int npcX, int npcY);
    
    string getCurrentString();
    bool dialogueOnce = false;
    
private:
    //Sets up the color for the font
    SDL_Color white = {255, 255, 255};
    SDL_Color black = {0, 0, 0};
    
    DialogueNode *currentNode;
    
    TTF_Font* Chalkboard = TTF_OpenFont("/Library/Fonts/Chalkboard.ttc", 32);
    
    void setupButtons(std::string option1text, std::string option2text);
    
    SDL_Event click;
    
    SDL_Rect option1Box, option2Box, option1, option2, message, box;
    
    void buttonHandler();
    
    bool pressed = false;
    
    vector<DialogueNode *> dialogueNodes;
    SDL_Window* window = SDL_GL_GetCurrentWindow();
    SDL_Renderer* renderer = SDL_GetRenderer(window);
    
    SDL_Surface* dialoguebox = IMG_Load("/Images/dialoguebox.png");
    SDL_Texture* dialoguebox_texture = SDL_CreateTextureFromSurface(renderer, dialoguebox);
    
    SDL_Surface* surfaceMessage;
    SDL_Surface* surfaceOption1;
    SDL_Surface* surfaceOption2;
    SDL_Texture* textureMessage;
    SDL_Texture* textureOption1;
    SDL_Texture* textureOption2;
    
    WORLDSTATE world = WORLDSTATE::PAINTEDWORLD;
    BUTTONSTATE button = BUTTONSTATE::NEUTRAL;
};

#endif /* DialogueTree_hpp */
