#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>

#include "libGameRGR2.h"
#include "local.h"

GameData* createGame(int        nbCharX,
                     int        nbCharY,
                     void*      pUserData,
                     Callbacks* pCb,
                     int        fps){
    // Local vars
    Screen*   pScreen = NULL;
    GameData* pGame   = NULL;
    // Check parameters
    if(nbCharX <= 0 || nbCharY <= 0){
        RAGE_QUIT(1000, "Bad game dimensions : nbCharX=%d / nbCharY=%d\n", nbCharX, nbCharY);
    }
    // Check parameter pointers
    if(pUserData == NULL){
        RAGE_QUIT(1010, "Empty user data pointer !\n");
    }
    if(pCb == NULL){
        RAGE_QUIT(1020, "Empty callback pointer !\n");
    }
    // Check callbacks
    if( pCb->cbInit == NULL ){
        RAGE_QUIT(1030, "Empty INIT callback pointer !\n");
    }        
    if( pCb->cbEvent == NULL ){
        RAGE_QUIT(1031, "Empty EVENT callback pointer !\n");
    }                
    if( pCb->cbUpdate == NULL ){
        RAGE_QUIT(1032, "Empty UPDATE callback pointer !\n");
    }        
    if( pCb->cbDraw == NULL ){
        RAGE_QUIT(1033, "Empty DRAW callback pointer !\n");
    }        
    if( pCb->cbFinish == NULL ){
        RAGE_QUIT(1034, "Empty FINISH callback pointer !\n");    
    }        
    // Allocate SCREEN structure
    pScreen = malloc( sizeof(Screen) );
    if(pScreen == NULL){
        RAGE_QUIT(1040, "Screen malloc failed !\n");    
    }
    // Allocate Game struct
    pGame = malloc( sizeof(GameData) );
    if( pGame==NULL ){
        RAGE_QUIT(1050, "Screen malloc failed !\n");    
    }
    // Fill game structure
    pScreen->width        = nbCharX;
    pScreen->height       = nbCharY;
    pGame->pScreen        = pScreen;
    pGame->pUserData      = pUserData;
    pGame->pUserCallbacks = pCb;
    pGame->displayFPS     = fps;  
    // return game structure
    return pGame;  
}

void gameLoop(GameData* pGame){
    // Locals
    WINDOW*    pWin = NULL;
    Screen*    pScr = NULL;
    void*      pDat = NULL;
    Callbacks* pCb  = NULL;
    int       loop = 0;
    unsigned long startTime = 0;
    unsigned long endTime   = 0;
    unsigned long frameTime = 0;
    // Check params
    checkGame(pGame, 2000);
    // Store pointers locally
    pScr = pGame->pScreen;
    pDat = pGame->pUserData;
    pCb  = pGame->pUserCallbacks;
    
    // Init of GFX (curses library)
    pWin = initscr();
    start_color();
    noecho();
    curs_set(0);
    nodelay(pWin, TRUE);
    
    // Call init here
    pCb->cbInit(pDat, pScr);
    
    // First time measurement
    startTime = getTimeMicros();  
      
    //=======================================
    // START of game loop
    //=======================================
    while(loop==0){
        
        //--------------------------
        // (call event if needed)
        //--------------------------
        loop |= checkEvent(pGame);
        
        //--------------------------
        // (call update)
        //--------------------------
        loop |= pCb->cbUpdate(pDat, pScr, frameTime);
        
        //--------------------------
        // (call draw + display FPS)
        //--------------------------
        clear();
        pCb->cbDraw(pDat, pScr);
        if(pGame->displayFPS != 0){
            move(0,0);
            printw("|FPS %ld|", (unsigned long)(0.99 + 1000000.0/frameTime));
        }
        refresh();

        //--------------------------
        // Wait for next frame
        //--------------------------
        // Get frame time
        endTime   = getTimeMicros();
        frameTime = endTime - startTime;
        startTime = endTime; 
        // Wait to achieve 60FPS
        if(frameTime <= 16666){
            usleep(16666-frameTime);
        }       
    }
    //=======================================
    // END of game loop
    //=======================================

    //--------------------------
    // Call finish here and exit
    //--------------------------
    pCb->cbFinish(pDat);

    // Finish curses
    echo();
    endwin();
}



