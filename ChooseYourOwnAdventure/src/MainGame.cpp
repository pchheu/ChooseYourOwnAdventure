//
//  MainGame.cpp
//  ChooseYourOwnAdventure
//
//  Created by Peter Chheu on 2/21/17.
//  Copyright © 2017 Peter Chheu. All rights reserved.
//

#include "MainGame.hpp"
#include "Sprite.hpp"
#include "Errors.hpp"



MainGame::MainGame(){
    window = nullptr;
    screenWidth = 1080;
    screenHeight = 800;
    
    currentState = GameState::PLAY;
}

MainGame::~MainGame(){
}

void MainGame::run(){
    initSystems();
    character.init("Images/sprite.png", 118, 185);
    gameLoop();
}

void MainGame::initSystems(){
    //Initializes SDL and other packages
    SDL_Init(SDL_INIT_EVERYTHING);
    if(!IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG)){
        std::cout << "Init Error: " << IMG_GetError() << std::endl;
    }
    
    //Creates the window
    window = SDL_CreateWindow("ChooseYourOwnAdventure",
                              SDL_WINDOWPOS_UNDEFINED,
                              SDL_WINDOWPOS_UNDEFINED,
                              screenWidth,
                              screenHeight,
                              SDL_WINDOW_OPENGL);
    
    if(window == nullptr){
        fatalError("SDL Window could not be created.");
    }
    
    
    //Sets up our OpenGL context
    SDL_GLContext glContext = SDL_GL_CreateContext(window);
    if(glContext == nullptr){
        fatalError("SDL_GL context could not be created.");
    }
    
    //Tells SDL that we want a double buffered window so we don't
    //have any flickering
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    
    //Initializes the renderer
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    
    //Sets the background color once the screen is flushed
    glClearColor(1.0f, 1.0f, 1.0f, 1.0);
    
    countedFrames = 0;
    fpsTimer.start();
    
}

void MainGame::gameLoop(){
    Map firstlevel = *new Map();
    firstlevel.mapInit("Images/map.bmp", "level1");
    character.getCurrentMapInfo(firstlevel);
    screen.initCamera(character);
    camera = screen.getCamInfo();
    
    while(currentState != GameState::EXIT){
//-------------------Calculate average FPS-------------------//
        
        processInput();
        camera = screen.getCamInfo();
        
//------------------Render graphics--------------------//
        SDL_RenderClear(renderer);
        
        firstlevel.renderMap(camera);
        character.render(camera.x, camera.y);
        
        SDL_RenderPresent(renderer);
        float avgFPS = countedFrames / (fpsTimer.getTicks() / 1000.f);
        if(avgFPS > 2000000){
            avgFPS = 0;
        }
        if(fpsTimer.getTicks() < 1000/60){
            SDL_Delay((1000/60) - fpsTimer.getTicks());
        }
    }
}

void MainGame::processInput(){
    SDL_Event evnt;
    float posX, posY;
    
    while(SDL_PollEvent(&evnt) == true){
        switch (evnt.type) {
            case SDL_QUIT:
                currentState = GameState::EXIT;
                break;
            case SDL_KEYDOWN:
                switch (evnt.key.keysym.sym) {
                    case SDLK_LEFT:
                        character.move(Movement::LEFT);
                        posX = character.getPosX();
                        posY = character.getPosY();
                        screen.updateCamera(posX, posY);
                        
                        std::cout << "Left key pressed" << std::endl;
                        break;
                    case SDLK_RIGHT:
                        character.move(Movement::RIGHT);
                        posX = character.getPosX();
                        posY = character.getPosY();
                        screen.updateCamera(posX, posY);
                        
                        std::cout << "Right key pressed" << std::endl;
                        break;
                    case SDLK_SPACE:
                        character.move(Movement::JUMP);
                        posX = character.getPosX();
                        posY = character.getPosY();
                        screen.updateCamera(posX, posY);
                        
                        std::cout << "Space pressed" << std::endl;
                        break;
                }
                break;
        }
    }
}

void MainGame::drawGame(){
    //character.render();
}
