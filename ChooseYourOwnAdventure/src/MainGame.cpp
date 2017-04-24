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
const int maxFPS = 100000/FPS;

MainGame::MainGame(){
    window = nullptr;
    screenWidth = 1080;
    screenHeight = 800;
    
    currentState = GameState::MENU;
}

MainGame::~MainGame(){
}

//Runs the game
void MainGame::run(){
    initSystems();
    gameLoop();
}

//Initializes all the graphics
void MainGame::initSystems(){
    //Initializes SDL and other packages
    if(SDL_Init(SDL_INIT_EVERYTHING == -1)){
        fatalError(SDL_GetError());
    }
    
    if(TTF_Init() == -1){
        fatalError(TTF_GetError());
    }
    
    if(!IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG)){
        fatalError(IMG_GetError());
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

//Game loop where most of the logic is handled
void MainGame::gameLoop(){
    DialogueTree tree = *new DialogueTree();
    tree.init();
    currentlevel = Map();
    player = Player(Vector2(0,300));
    currentlevel.mapInit("Images/newbackgroundcolor.jpg", "level1");
    player.getCurrentMapInfo(currentlevel);
    screen.initCamera();
    
    int lastUpdate = SDL_GetTicks();
    currentlevel.renderMap("level1");
    screen.updateMap(currentlevel.getlevelWidth(), currentlevel.getlevelHeight());
    
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
        
        currentlevel.draw(Camera::camera);
        player.draw();
        tree.performDialogue();
        screen.updateCamera(player.getX(),player.getY());
        
        SDL_RenderPresent(renderer);
    }
}

//Handles keyboard inputs from the player
void MainGame::processInput(){
    SDL_Event evnt;
    const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);
    
    while(SDL_PollEvent(&evnt) == true){
        switch (evnt.type){
            case SDL_QUIT:
                currentState = GameState::EXIT;
                break;
            case SDL_KEYDOWN:
                if(evnt.key.repeat == 0){
                    pressedKeys[evnt.key.keysym.scancode] = true;
                    heldKeys[evnt.key.keysym.scancode] = true;
                }
                break;
            case SDL_KEYUP:
                releasedKeys[evnt.key.keysym.scancode] = true;
                heldKeys[evnt.key.keysym.scancode] = false;
        }
        
        if(heldKeys[SDL_SCANCODE_LEFT]){
            player.moveLeft();
        }
        if(heldKeys[SDL_SCANCODE_RIGHT]){
            player.moveRight();
        }
        if(heldKeys[SDL_SCANCODE_SPACE]){
            player.jump();
        }
        if(!heldKeys[SDL_SCANCODE_LEFT] && !heldKeys[SDL_SCANCODE_RIGHT]){
            player.stopMoving();
        }
    }
}

//Updates everything in the game based on the elasped time
void MainGame::update(float elaspedTime){
    player.update(elaspedTime);
    
    //Check tile collisions
    std::vector<Rectangle> others;
    if((others = currentlevel.checkTileCollisions(player.getBoundingBox())).size() > 0){
        //Player has collided with a tile
        player.handleTileCollisions(others);
    }
}
