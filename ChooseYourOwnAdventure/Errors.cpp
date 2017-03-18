//
//  Errors.cpp
//  ChooseYourOwnAdventure
//
//  Created by Peter Chheu on 3/17/17.
//  Copyright © 2017 Peter Chheu. All rights reserved.
//

#include "Errors.hpp"

//Helper function incase the window was unable to be created
void fatalError(std::string errorString){
    std::cout << errorString << std::endl;
    std::cout << "Enter any key to quit..." << std::endl;
    int tmp;
    std::cin >> tmp;
    SDL_Quit();
}
