//
//  MainGame.cpp
//  ChooseYourOwnAdventure
//
//  Created by Peter Chheu on 2/21/17.
//  Copyright © 2017 Peter Chheu. All rights reserved.
//

#include "MainGame.hpp"
#include "Errors.hpp"

const int FPS = 60;
const int maxFPS = 1000/FPS;

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
    
}

void MainGame::gameLoop(){
    Map firstlevel = *new Map();
    player = *new Player(Vector2(0,300));
    firstlevel.mapInit("Images/map.bmp", "level1");
    player.getCurrentMapInfo(firstlevel);
    screen.initCamera(player);
    camera = screen.getCamInfo();
    
    int lastUpdate = SDL_GetTicks();
    
    //Game loop starts
    while(currentState != GameState::EXIT){
        //-------------------Calculate FPS-------------------//
        processInput();
        
        const int currentTimeMS = SDL_GetTicks();
        int elaspedTime = currentTimeMS - lastUpdate;
        update(std::min(elaspedTime, maxFPS));
        lastUpdate = currentTimeMS;
        
        //------------------Render graphics--------------------//
        SDL_RenderClear(renderer);
        
        //screen.updateMap(firstlevel.getlevelWidth(), firstlevel.getlevelHeight());
        
        camera = screen.getCamInfo();
        firstlevel.draw(camera);
        //firstlevel.renderMap("firstlevel");
        screen.updateCamera(player.getX(), player.getY());
        player.draw(screen.getCamX(), screen.getCamY());
        
        SDL_RenderPresent(renderer);
    }
}

void MainGame::processInput(){
    SDL_Event evnt;
    float posX, posY;
    
    while(SDL_PollEvent(&evnt) == true){
        switch (evnt.type){
            case SDL_QUIT:
                currentState = GameState::EXIT;
                break;
            case SDL_KEYUP:
                player.stopMoving();
                break;
            case SDL_KEYDOWN:
                switch (evnt.key.keysym.sym) {
                    case SDLK_LEFT:
                        player.moveLeft();
                        break;
                    case SDLK_RIGHT:
                        player.moveRight();
                        break;
                    case SDLK_SPACE:
                        player.jump();
                        break;
                }
                break;
        }
    }
}

void MainGame::drawGame(){
    //character.render();
}

void MainGame::update(float elaspedTime){
    player.update(elaspedTime);
}
