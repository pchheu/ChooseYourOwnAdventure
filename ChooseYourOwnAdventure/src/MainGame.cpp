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
    
    while(currentState == GameState::MENU){
        int a;
        SDL_RenderClear(renderer);
        menu.draw();
        a = menu.handlePlay();
        if(a == 1){
            currentState = GameState::PLAY;
        }
        SDL_RenderPresent(renderer);
    }
     
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
    glClearColor(0.0f, 0.0f, 0.0f, 0.0);
    
    //Initializes music
    music = Mix_LoadMUS("/music/cappuccino.mp3");
    Mix_PlayMusic(music, -1);
    Mix_VolumeMusic(50);
    
    //Initializes main menu
    menu = *new MainMenu("/Images/tempmenu.png", screenWidth, screenHeight);
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
        
        Vector2 npcspawn = currentlevel.getNPCSpawnPoint();
        if(npcspawn.x != 0 && npcspawn.y != 0){
            owl.draw();
        }
        player.draw();
        
        Vector2 portalspawn = currentlevel.getPortalLocation();
        if(portalspawn.x != 0 && portalspawn.y != 0){
            p.draw();
        }
        
        if(tree.hasTalked()){
            dialogueEngaged = false;
        }
        
        if(dialogueEngaged){
            player.stopMoving();
            world = tree.performDialogue(player.getX(), player.getY(), owl.getX(), owl.getY());
            heldKeys[SDL_SCANCODE_LEFT] = false;
            heldKeys[SDL_SCANCODE_RIGHT] = false;
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
                if(evnt.key.repeat == 0 && !dialogueEngaged){
                    pressedKeys[evnt.key.keysym.scancode] = true;
                    heldKeys[evnt.key.keysym.scancode] = true;
                }
                break;
            case SDL_KEYUP:
                releasedKeys[evnt.key.keysym.scancode] = true;
                heldKeys[evnt.key.keysym.scancode] = false;
        }
        
        if(heldKeys[SDL_SCANCODE_LEFT] && !dialogueEngaged){
            player.moveLeft();
        }
        if(heldKeys[SDL_SCANCODE_RIGHT] && !dialogueEngaged){
            player.moveRight();
        }
        if(heldKeys[SDL_SCANCODE_SPACE] && !dialogueEngaged){
            player.jump();
        }
        if(!heldKeys[SDL_SCANCODE_LEFT] && !heldKeys[SDL_SCANCODE_RIGHT]){
            player.stopMoving();
        }
        if(evnt.type == SDL_KEYDOWN){
            if(evnt.key.keysym.sym == SDLK_UP){
                Rectangle playerRect = player.getBoundingBox();
                Rectangle portalRect = p.getBoundingBox();
                
                if(playerRect.collidesWith(portalRect)){
                    std::cout << "Up pressed at portal" << std::endl;
                    if(world == 0){
                        currentlevel = level2;
                        
                        p.updateLocation(currentlevel.getPortalLocation());
                        owl.updateLocation(currentlevel.getNPCSpawnPoint());
                        
                        player.setLocation(currentlevel.getPlayerSpawnPoint());
                    }else if(world == 1){
                        currentlevel = level3;;
                        
                        p.updateLocation(currentlevel.getPortalLocation());
                        owl.updateLocation(currentlevel.getNPCSpawnPoint());
                        
                        player.setLocation(currentlevel.getPlayerSpawnPoint());
                    }
                }
            }
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
    //Loads all the maps
    level1 = *new Map();
    level2 = *new Map();
    level3 = *new Map();
    
    level1.renderMap("level1");
    level2.renderMap("level2");
    level3.renderMap("level3");
    
    level1.mapInit("/Images/newbackgroundcolor.jpg", "level1");
    level2.mapInit("/Images/newbackground.jpg", "level2");
    level3.mapInit("/Images/newbackgroundcolor.jpg", "level3");
    
    tree = *new DialogueTree();
    tree.init();
    
    currentlevel = level1;
    nextlevel = level2;
    
    owl = *new NPC(currentlevel.getNPCSpawnPoint());
    
    player = *new Player(currentlevel.getPlayerSpawnPoint());
    player.getCurrentMapInfo(currentlevel);
    
    p = *new Portal("Images/portal2.png", currentlevel.getPortalLocation());
    
    screen.initCamera();
}
