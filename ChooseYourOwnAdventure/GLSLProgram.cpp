//
//  GLSLProgram.cpp
//  ChooseYourOwnAdventure
//
//  Created by Peter Chheu on 3/17/17.
//  Copyright © 2017 Peter Chheu. All rights reserved.
//

#include "GLSLProgram.hpp"

GLSLProgram::GLSLProgram() : programID(0), vertexShaderID(0), fragmentShaderID(0){
    
}

GLSLProgram::~GLSLProgram(){
    
}

void GLSLProgram::compileShaders(const std::string& vertexShaderFilePath, const std::string& fragmentShaderFilePath){
    vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
    if(vertexShaderID == 0){
        std::cout << "Unable to create vertex shader." << std::endl;
    }
}

void GLSLProgram::linkShaders(){
    
}
