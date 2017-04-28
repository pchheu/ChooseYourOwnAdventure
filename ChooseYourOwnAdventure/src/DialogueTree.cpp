//
//  DialogueTree.cpp
//  ChooseYourOwnAdventure
//
//  Created by Peter Chheu on 4/22/17.
//  Copyright © 2017 Peter Chheu. All rights reserved.
//

#include "DialogueTree.hpp"

const int screenWidth = 1080;
const int screenHeight = 800;

//Constructor for the dialogue node
DialogueNode::DialogueNode(string _text){
    text = _text;
}

//Constructor for the dialogue options
DialogueOption::DialogueOption(string _text, int _returnCode, DialogueNode *_nextNode){
    text = _text;
    returnCode = _returnCode;
    nextNode = _nextNode;
}

//Constructor for the tree
DialogueTree::DialogueTree(){
}

//Sets up the tree
void DialogueTree::init(){
    DialogueNode *node0 = new DialogueNode("Hello there!");
    DialogueNode *node1 = new DialogueNode("Say, what are you doing aroud here?");
    DialogueNode *node2 = new DialogueNode("Wow so rude!");
    DialogueNode *node3 = new DialogueNode("Aimless wanderer eh? Well maybe you should check out that portal");
    DialogueNode *node4 = new DialogueNode("Carrots! Try that portal over there.");
    DialogueNode *node5 = new DialogueNode("");
    
    //Node 0
    node0->dialogueOptions.push_back(DialogueOption("Hi!", 0, node1));
    node0->dialogueOptions.push_back(DialogueOption("Don't talk to me", 1, node2));
    dialogueNodes.push_back(node0);
    
    //Node 1
    node1->dialogueOptions.push_back(DialogueOption("I'm not entirely sure", 1, node3));
    node1->dialogueOptions.push_back(DialogueOption("I'm just here to collect carrots", 0, node4));
    dialogueNodes.push_back(node1);
    
    //Node 2
    node2->dialogueOptions.push_back(DialogueOption("I'm leaving now", 1, node5));
    node2->dialogueOptions.push_back(DialogueOption("I better not see you ever again", 1, node5));
    dialogueNodes.push_back(node2);
    
    //Node 3
    node3->dialogueOptions.push_back(DialogueOption("Hopefully I'll find something interesting", 1, node5));
    node3->dialogueOptions.push_back(DialogueOption("Hopefully I'll find meaning in life again", 0, node5));
    dialogueNodes.push_back(node3);
    
    //Node 4
    node4->dialogueOptions.push_back(DialogueOption("Thank you so much! I haven't eaten in days and I'm starving", 1, node5));
    node4->dialogueOptions.push_back(DialogueOption("Thank you so much!", 1, nullptr));
    dialogueNodes.push_back(node4);
    
    currentNode = dialogueNodes[0];
}

//Destroys the tree to free up memory
void DialogueTree::destroyTree(){
    for(int i = 0; i < dialogueNodes.size(); i++){
        delete dialogueNodes[i];
    }
    
    dialogueNodes.clear();
}

//Goes through the dialogue logic and brings up the HUD,
//returns the value of the outcomes of the dialogue
int DialogueTree::performDialogue(int playerX, int playerY, int npcX, int npcY){
    //Sets dimenions of the dialogue box
    message = {npcX - 30, npcY - 70};
    
    if(dialogueNodes.empty()){
        fatalError("Unable to build dialogue tree");
        return 0;
    }
    
    if(currentNode->dialogueOptions.empty()){
        dialogueOnce = true;
        if(world == WORLDSTATE::PAINTEDWORLD){
            return 0;
        }else{
            return 1;
        }
    }
    
    const char* text = (currentNode->text).c_str();
    surfaceMessage = TTF_RenderText_Solid(Chalkboard, text, white);
    textureMessage = SDL_CreateTextureFromSurface(renderer, surfaceMessage);
    
    string option1text = currentNode->dialogueOptions[0].text;
    string option2text = currentNode->dialogueOptions[1].text;
        
    message.w = surfaceMessage->w;
    message.h = surfaceMessage->h;
    
    box = {message.x - 25,
           message.y - 10,
           surfaceMessage->w + 50,
           surfaceMessage->h + 25};
        
    SDL_RenderCopy(renderer, dialoguebox_texture, NULL, &box);
    SDL_RenderCopy(renderer, textureMessage, NULL, &message);
    
    setupButtons(option1text, option2text);
    
    SDL_FreeSurface(surfaceMessage);
    SDL_DestroyTexture(textureMessage);
    
    return 0;
}

//Sets up the buttons for the dialogue options
void DialogueTree::setupButtons(std::string option1text, std::string option2text){
    const char* text1 = option1text.c_str();
    surfaceOption1 = TTF_RenderText_Solid(Chalkboard, text1, white);
    textureOption1 = SDL_CreateTextureFromSurface(renderer, surfaceOption1);
    
    const char* text2 = option2text.c_str();
    surfaceOption2 = TTF_RenderText_Solid(Chalkboard, text2, white);
    textureOption2 = SDL_CreateTextureFromSurface(renderer, surfaceOption2);

    option1Box = {Camera::getCamX() + ((screenWidth/2) - (surfaceOption1->w/2)),
                  Camera::getCamY() + ((screenHeight/2) - 75),
                  surfaceOption1->w + 40,
                  surfaceOption1->h + 15};
    
    option2Box = {Camera::getCamX() + ((screenWidth/2) - (surfaceOption2->w/2)),
                  Camera::getCamY() + screenHeight/2,
                  surfaceOption2->w + 40,
                  surfaceOption2->h + 15};
    
    option1 = {option1Box.x + 20,
               option1Box.y + 5,
               surfaceOption1->w,
               surfaceOption1->h};
    
    option2 = {option2Box.x + 20,
               option2Box.y + 5,
               surfaceOption2->w,
               surfaceOption2->h};
    
    SDL_RenderCopy(renderer, dialoguebox_texture, NULL, &option1Box);
    SDL_RenderCopy(renderer, textureOption1, NULL, &option1);
    
    SDL_RenderCopy(renderer, dialoguebox_texture, NULL, &option2Box);
    SDL_RenderCopy(renderer, textureOption2, NULL, &option2);
    
    buttonHandler();
    
    if(button == BUTTONSTATE::BUTTON1){
        button = BUTTONSTATE::NEUTRAL;
        if(currentNode->dialogueOptions[0].returnCode == 0){
            world = WORLDSTATE::PAINTEDWORLD;
        }else{
            world = WORLDSTATE::UNPAINTEDWORLD;
        }
        currentNode = currentNode->dialogueOptions[0].nextNode;
    
        if(currentNode == nullptr){
            return;
        }
    }else if(button == BUTTONSTATE::BUTTON2){
        button = BUTTONSTATE::NEUTRAL;
        if(currentNode->dialogueOptions[1].returnCode == 0){
            world = WORLDSTATE::PAINTEDWORLD;
        }else{
            world = WORLDSTATE::UNPAINTEDWORLD;
        }
        currentNode = currentNode->dialogueOptions[1].nextNode;
        
        if(currentNode == nullptr){
            return;
        }
    }
    
    SDL_FreeSurface(surfaceOption1);
    SDL_FreeSurface(surfaceOption2);
    
    SDL_DestroyTexture(textureOption1);
    SDL_DestroyTexture(textureOption2);
}

void DialogueTree::buttonHandler(){
    //Check if the mouse is inside either buttons
    bool insideButton1 = true;
    bool insideButton2 = true;
    
    while(SDL_PollEvent(&click) == true){
        if(click.type == SDL_MOUSEBUTTONDOWN){
            //Get mouse position
            int x, y;
            SDL_GetMouseState(&x, &y);
            
            //Mouse is inside the buttons
            if(x < option1Box.x){
                insideButton1 = false;
            }
            if(x < option2Box.x){
                insideButton2 = false;
            }
            
            //Mouse is right of the buttons
            if(x > option1Box.x + option1Box.w){
                insideButton1 = false;
            }
            if(x > option2Box.x + option2Box.w){
                insideButton2 = false;
            }
            
            //Mouse is above the buttons
            if(y < option1Box.y){
                insideButton1 = false;
            }
            if(y < option2Box.y){
                insideButton2 = false;
            }
            
            //Mouse is below the buttons
            if(y > option1Box.y + option1Box.h){
                insideButton1 = false;
            }
            if(y > option2Box.y + option2Box.h){
                insideButton2 = false;
            }
            
            //Mouse is over the buttons
            if(insideButton1 == true){
                button = BUTTONSTATE::BUTTON1;
                pressed = true;
                std::cout << "Button 1 pressed" << std::endl;
            }else if(insideButton2 == true){
                button = BUTTONSTATE::BUTTON2;
                pressed = true;
                std::cout << "Button 2 pressed" << std::endl;
            }
        }
    }
}

bool DialogueTree::hasTalked(){
    return dialogueOnce;
}
