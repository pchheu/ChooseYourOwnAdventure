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
WORLDSTATE DialogueTree::performDialogue(){
    //Sets dimenions of the dialogue box
    SDL_Rect message = {Camera::camera.x + 375, Camera::camera.y + 260};
    SDL_Rect box;
    SDL_Rect option1;
    SDL_Rect option2;
    
    if(dialogueNodes.empty()){
        fatalError("Unable to build dialogue tree");
        return WORLDSTATE::PAINTEDWORLD;
    }
    
    DialogueNode *currentNode = dialogueNodes[0];
    
    //Sets up the color for the font
    SDL_Color color = {255, 255, 255};
    
    const char* text = (currentNode->text).c_str();
    SDL_Surface* surfaceMessage = TTF_RenderUTF8_Solid(Chalkboard, text, color);
    SDL_Texture* textureMessage = SDL_CreateTextureFromSurface(renderer, surfaceMessage);
    
    message.w = surfaceMessage->w;
    message.h = surfaceMessage->h;
    
    box = {Camera::camera.x + 350, Camera::camera.y + 250, surfaceMessage->w + 50, surfaceMessage->h + 25};
    
    SDL_RenderCopy(renderer, dialoguebox_texture, NULL, &box);
    SDL_RenderCopy(renderer, textureMessage, NULL, &message);
    
    SDL_FreeSurface(surfaceMessage);
    SDL_DestroyTexture(textureMessage);
    //while(true){
    //}
    return WORLDSTATE::PAINTEDWORLD;
}
