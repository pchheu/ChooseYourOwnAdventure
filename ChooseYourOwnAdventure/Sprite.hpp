//
//  Sprite.hpp
//  ChooseYourOwnAdventure
//
//  Created by Peter Chheu on 2/21/17.
//  Copyright © 2017 Peter Chheu. All rights reserved.
//
#pragma once

class Sprite{
public:
    Sprite();
    ~Sprite();
    
    void init(int _x, int _y, int _width, int _height);
    
    void draw();
    
private:
    int x;
    int y;
    int width;
    int height;
};


