//
//  Vector2.h
//  ChooseYourOwnAdventure
//
//  Created by Peter Chheu on 3/21/17.
//  Copyright © 2017 Peter Chheu. All rights reserved.
//

#ifndef Vector2_h
#define Vector2_h

struct Vector2{
    int x, y;
    Vector2():
        x(0),y(0)
    {}
    Vector2(int x, int y) :
        x(x), y(y)
    {}
    Vector2 zero(){
        return Vector2(0,0);
    }
};

#endif /* Vector2_h */
