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

using namespace std;

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
    string text;
    vector <DialogueOption> dialogueOptions;
};

class DialogueTree{
public:
    DialogueTree();
    
    void init();
    void destroyTree();
    
    int performDialogue();
    
private:
    vector <DialogueNode *> dialogueNodes;
    
};

#endif /* DialogueTree_hpp */
