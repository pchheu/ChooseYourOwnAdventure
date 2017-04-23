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
#include <string>
#include <iostream>
#include <vector>
#include "SDL2/SDL.h"
#include "SDL2_image/SDL_image.h"
#include "SDL2_ttf/SDL_ttf.h"
#include "Errors.hpp"
#include "Camera.hpp"

using namespace std;

enum class WORLDSTATE{PAINTEDWORLD, UNPAINTEDWORLD};

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
    
    WORLDSTATE performDialogue();
    
    string getCurrentString();
    
private:
    vector<DialogueNode *> dialogueNodes;
    SDL_Window* window = SDL_GL_GetCurrentWindow();
    SDL_Renderer* renderer = SDL_GetRenderer(window);
    
};

#endif /* DialogueTree_hpp */
