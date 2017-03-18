//
//  GSLProgram.hpp
//  ChooseYourOwnAdventure
//
//  Created by Peter Chheu on 3/17/17.
//  Copyright © 2017 Peter Chheu. All rights reserved.
//
#pragma once

#include <stdio.h>
#include <string>
#include "OpenGL/gl.h"

class GLSLProgram{
public:
    GLSLProgram();
    ~GLSLProgram();
    
    void compileShaders(const std::string& vertexShaderFilePath, const std::string& fragmentShaderFilePath);
    
    void linkShaders();
private:
    GLuint programID;
    GLuint vertexShaderID;
    GLuint fragmentShaderID;
};

