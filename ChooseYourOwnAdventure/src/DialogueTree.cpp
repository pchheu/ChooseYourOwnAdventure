//
//  DialogueTree.cpp
//  ChooseYourOwnAdventure
//
//  Created by Peter Chheu on 4/22/17.
//  Copyright © 2017 Peter Chheu. All rights reserved.
//

#include "DialogueTree.hpp"


//Constructor for the dialogue options
DialogueOption::DialogueOption(string _text, int _returnCode, DialogueNode *_nextNode){
    
}

//Constructor for the tree
DialogueTree::DialogueTree(){
    
}

//Sets up the tree
void DialogueTree::init(){
    DialogueNode *node0 = new DialogueNode;
    DialogueNode *node1 = new DialogueNode;
    DialogueNode *node2 = new DialogueNode;
    DialogueNode *node3 = new DialogueNode;
    DialogueNode *node4 = new DialogueNode;
}

//Destroys the tree to free up memory
void DialogueTree::destroyTree(){
    
}

//Goes through the dialogue logic
int DialogueTree::performDialogue(){
    return 0;
}
