//
//  DialogueTree.cpp
//  ChooseYourOwnAdventure
//
//  Created by Peter Chheu on 4/22/17.
//  Copyright © 2017 Peter Chheu. All rights reserved.
//

#include "DialogueTree.hpp"

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
    DialogueNode *node1 = new DialogueNode("");
    DialogueNode *node2 = new DialogueNode("");
    DialogueNode *node3 = new DialogueNode("");
    DialogueNode *node4 = new DialogueNode("");
    
    //Node 0
    node0->dialogueOptions.push_back(DialogueOption("What is this place?", 0, node1));
    node0->dialogueOptions.push_back(DialogueOption("Who are you?", 0, node2));
    dialogueNodes.push_back(node0);
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
WORLDSTATE DialogueTree::performDialogue(int playerX, int playerY, int npcX, int npcY){
    //Sets dimenions of the dialogue box
    SDL_Rect message = {(playerX - Camera::camera.x) - 20, (playerY - Camera::camera.y) - 190};
    SDL_Rect box;
    
    SDL_Rect option1Box;
    SDL_Rect option1 = {(playerX - Camera::camera.x) - 105, (playerY - Camera::camera.y) - 90};
    
    SDL_Rect option2Box;
    SDL_Rect option2 = {(playerX - Camera::camera.x) + 55, (playerY - Camera::camera.y) - 90};
    
    
    if(dialogueNodes.empty()){
        fatalError("Unable to build dialogue tree");
        return WORLDSTATE::PAINTEDWORLD;
    }
    
    DialogueNode *currentNode = dialogueNodes[0];
    
    //Sets up the color for the font
    SDL_Color color = {255, 255, 255};
    
    const char* text = (currentNode->text).c_str();
    SDL_Surface* surfaceMessage = TTF_RenderText_Solid(Chalkboard, text, color);
    SDL_Texture* textureMessage = SDL_CreateTextureFromSurface(renderer, surfaceMessage);
    
    string option1text = currentNode->dialogueOptions[0].text;
    const char* text1 = option1text.c_str();
    SDL_Surface* surfaceOption1 = TTF_RenderText_Solid(Chalkboard, text1, color);
    SDL_Texture* textureOption1 = SDL_CreateTextureFromSurface(renderer, surfaceOption1);
    
    string option2text = currentNode->dialogueOptions[1].text;
    const char* text2 = option2text.c_str();
    SDL_Surface* surfaceOption2 = TTF_RenderText_Solid(Chalkboard, text2, color);
    SDL_Texture* textureOption2 = SDL_CreateTextureFromSurface(renderer, surfaceOption2);
    
    message.w = surfaceMessage->w;
    message.h = surfaceMessage->h;
    
    option1.x = surfaceOption1->w;
    option2.y = surfaceOption1->h;
    
    box = {message.x - 25,
           message.y - 10,
           surfaceMessage->w + 50,
           surfaceMessage->h + 25};
    
    option1Box = {(playerX - Camera::camera.x) - 125,
                  (playerY - Camera::camera.y) - 100,
                   surfaceOption1->w,
                   surfaceOption1->h + 10};
    
    option2Box = {(playerX - Camera::camera.x) + 75,
                  (playerY - Camera::camera.y) - 100,
                   surfaceOption2->w + 10,
                   surfaceOption2->h + 10};
    
    option1 = {option1Box.x,
               option1Box.y,
               surfaceOption1->w,
               surfaceOption1->h};
    
    option2 = {option2Box.x + 6,
               option2Box.y + 5,
               surfaceOption2->w,
               surfaceOption2->h};
    
    SDL_RenderCopy(renderer, dialoguebox_texture, NULL, &box);
    SDL_RenderCopy(renderer, textureMessage, NULL, &message);
    
    SDL_RenderCopy(renderer, dialoguebox_texture, NULL, &option1Box);
    SDL_RenderCopy(renderer, textureOption1, NULL, &option1);
    
    SDL_RenderCopy(renderer, dialoguebox_texture, NULL, &option2Box);
    SDL_RenderCopy(renderer, textureOption2, NULL, &option2);
    
    SDL_FreeSurface(surfaceOption1);
    SDL_DestroyTexture(textureOption1);
    
    SDL_FreeSurface(surfaceOption2);
    SDL_DestroyTexture(textureOption2);
    
    SDL_FreeSurface(surfaceMessage);
    SDL_DestroyTexture(textureMessage);
    //while(true){
    //}
    return WORLDSTATE::PAINTEDWORLD;
}
