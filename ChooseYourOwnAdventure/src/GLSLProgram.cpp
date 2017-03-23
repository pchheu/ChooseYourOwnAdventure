//
//  GLSLProgram.cpp
//  ChooseYourOwnAdventure
//
//  Created by Peter Chheu on 3/17/17.
//  Copyright © 2017 Peter Chheu. All rights reserved.
//

#include "GLSLProgram.hpp"
#include "Errors.hpp"
#include <fstream>
#include <iostream>
#include <vector>

GLSLProgram::GLSLProgram() : programID(0), vertexShaderID(0), fragmentShaderID(0){
    
}

GLSLProgram::~GLSLProgram(){
    
}

//Compiles the shaders so graphics can be drawn from the GPU
void GLSLProgram::compileShaders(const std::string& vertexShaderFilePath, const std::string& fragmentShaderFilePath){
    vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
    if(vertexShaderID == 0){
        fatalError("Vertex shader failed to be created");
    }
    
    fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
    if(fragmentShaderID == 0){
        fatalError("Fragment shader failed to be created");
    }
    
    compileShader(vertexShaderFilePath, vertexShaderID);
    compileShader(fragmentShaderFilePath, fragmentShaderID);
}

void GLSLProgram::linkShaders(){
    //Attach the shaders to our program
    glAttachShader(programID, vertexShaderID);
    glAttachShader(programID, fragmentShaderID);
    
    //Link our program
    glLinkProgram(programID);
    
    GLint isLinked = 0;
    glGetProgramiv(programID, GL_LINK_STATUS, (int *)&isLinked);
    if( isLinked == GL_FALSE){
        GLint maxLenth = 0;
        glGetProgramiv(programID, GL_INFO_LOG_LENGTH, &maxLenth);
        
        std::vector<GLchar> infoLog(maxLenth);
        glGetProgramInfoLog(programID, maxLenth, &maxLenth, &infoLog[0]);
        
        glDeleteProgram(programID);
        glDeleteShader(vertexShaderID);
        glDeleteShader(fragmentShaderID);
        
        std::printf("%s\n", &(infoLog[0]));
        fatalError("Shaders failed to link");
    }
}

void GLSLProgram::compileShader(const std::string& filePath, GLuint id){
    programID = glCreateProgram();
    
    std::ifstream shaderFile(filePath);
    if(shaderFile.fail()){
        perror(filePath.c_str());
        fatalError("Failed to open " + filePath);
    }
    
    std::string fileContents = "";
    std::string line;
    
    //Parses through the shader files and adds the content to a single string
    while(std::getline(shaderFile, line)){
        fileContents += line + "\n";
    }
    
    shaderFile.close();
    
    const char* contentsPtr = fileContents.c_str();
    glShaderSource(id, 1, &contentsPtr, nullptr);
    
    glCompileShader(id);
    
    GLint success = 0;
    glGetShaderiv(vertexShaderID, GL_COMPILE_STATUS, &success);
    
    if( success == GL_FALSE ){
        GLint maxlength = 0;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &maxlength);
        
        //Null character is included
        std::vector<char> errorLog(maxlength);
        glGetShaderInfoLog(id, maxlength, &maxlength, &errorLog[0]);
        
        //Provide the infolog and exit with failure
        glDeleteShader(id);
        
        std::printf("%s\n", &(errorLog[0]));
        fatalError("Shader " + filePath + "failed to comile");
    }

}
