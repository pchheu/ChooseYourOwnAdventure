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

    if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0){
        fatalError(Mix_GetError());
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
    
    //Initializes music
    music = Mix_LoadMUS("/music/cappuccino.mp3");
    Mix_PlayMusic(music, -1);
    Mix_VolumeMusic(60);
}

//Game loop where most of the logic is handled
void MainGame::gameLoop(){
    initObjects();
    
    int lastUpdate = SDL_GetTicks();
    screen.updateMap(currentlevel.getlevelWidth(), currentlevel.getlevelHeight());
    
    //Game loop starts
    while(currentState != GameState::EXIT){
        //-------------------Calculate FPS/Process inputs-------------------//
        processInput();
        
        const int currentTimeMS = SDL_GetTicks();
        int elaspedTime = currentTimeMS - lastUpdate;
        update(std::min(elaspedTime, maxFPS));
        lastUpdate = currentTimeMS;
        
        //------------------Render graphics--------------------//
        SDL_RenderClear(renderer);
        
        currentlevel.draw(Camera::camera);
        owl.draw();
        player.draw();
        p.draw();
        
        if(dialogueEngaged){
            player.stopMoving();
            tree.performDialogue(player.getX(), player.getY(), owl.getX(), owl.getY());
        }
        
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
    owl.update(elaspedTime);
    
    //Check tile collisions
    std::vector<Rectangle> others;
    if((others = currentlevel.checkTileCollisions(player.getBoundingBox())).size() > 0){
        //Player has collided with a tile
        player.handleTileCollisions(others);
    }
    
    //Checks for any special events that triggered
    std::vector<Rectangle> triggers;
    if((triggers = currentlevel.checkTriggerCollisions(player.getBoundingBox())).size() > 0){
        dialogueEngaged = true;
    }
}

//Initializes all entities, maps, and other assets
void MainGame::initObjects(){
    tree = *new DialogueTree();
    tree.init();
    
    currentlevel = *new Map();
    currentlevel.renderMap("level1");
    currentlevel.mapInit("Images/newbackgroundcolor.jpg", "level1");
    usleep(500000);
    
    owl = *new NPC(currentlevel.getNPCSpawnPoint());
    usleep(100000);
    
    player = *new Player(currentlevel.getPlayerSpawnPoint());
    player.getCurrentMapInfo(currentlevel);
    usleep(100000);
    
    p = *new Portal("Images/portal2.png", currentlevel.getPortalLocation());
    
    screen.initCamera();
}
