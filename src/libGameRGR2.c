#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <sys/time.h>
#include <unistd.h>

#include "libGameRGR2.h"

unsigned long getTimeMicros(){
    struct timeval tv;
    gettimeofday(&tv,NULL);
    return (tv.tv_sec*1000000) + (tv.tv_usec/1);
} 

void debug(const char* format, ...){
    // List of arguments
    va_list args;
    // only write to stderr if format is ok
    if(format == NULL){
        RAGE_QUIT(1, "'format' string pointer is NULL !\n");    
    }
    // Start retrieving arguments
    va_start(args, format );
    fputs("[DEBUG] ", stderr);
    vfprintf(stderr, format, args );       
    // Clean up list
    va_end  (args);
    fflush(stderr);    
}

void rageQuit(const char* fname,
              const int   lineno,
              const char* fxname,
              const int   errorCode,
              const char* format, ...){
    // List of arguments
    va_list args;
    // display information (if format string is ok)
    fputs("--------------------\n", stderr);
    if(format != NULL){
        // Start retrieving arguments
        va_start(args, format );
        fputs("[ERROR] ", stderr);
        vfprintf(stderr, format, args );       
        // Clean up list
        va_end  (args);
    }
    fputs("\n", stderr);
    fprintf(stderr, "File     : '%s'\n", fname );
    fprintf(stderr, "Function : '%s( )'\n", fxname);
    fprintf(stderr, "Line     :  %d \n", lineno);
    fprintf (stderr, "\nProgram exited with code (%d).\n", errorCode);
    fputs("--------------------\n", stderr);
    fflush(stderr);    
    exit(errorCode);
}

GameData* createGame(int        nbCharX,
                     int        nbCharY,
                     void*      pUserData,
                     Callbacks* pCb,
                     int        fps){
    // Local vars
    Screen*   pScreen;
    GameData* pGame = NULL;
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
    int        loop = 0;
    int        ch   = ERR+1;
    Event      evt;
    unsigned long startTime = 0;
    unsigned long endTime   = 0;
    unsigned long frameTime = 0;
    // Check params
    if(pGame == NULL){
        RAGE_QUIT(2000, "Game data pointer NULL !\n");
    }
    // Store pointers locally
    pScr = pGame->pScreen;
    pDat = pGame->pUserData;
    pCb  = pGame->pUserCallbacks;

    if(pScr == NULL){
        RAGE_QUIT(2001, "Game screen pointer NULL !\n");
    }
    if(pDat == NULL){
        RAGE_QUIT(2002, "Game user data pointer NULL !\n");
    }
    if(pCb == NULL){
        RAGE_QUIT(2003, "Game user callback pointer NULL !\n");
    }
    
    // Init of GFX (curses library)
    pWin = initscr();
    start_color();
    init_pair(1, COLOR_YELLOW, COLOR_RED);
    noecho();
    curs_set(0);
    nodelay(pWin, TRUE);
    
    // Call init here
    pCb->cbInit(pDat, pScr);
    
    // First time measurement
    startTime = getTimeMicros();    
    // Game loop here
    while(loop==0){
        
        // (call event if needed)
        while( (ch=getch()) != ERR ){    
            fprintf(stderr, "-key %d", ch);
            evt.code = ch;
            pCb->cbEvent(pDat, pScr, &evt);            
        }
        fputs("\n", stderr);
        // (call update)
        loop = pCb->cbUpdate(pDat, pScr, frameTime);
        
        // (call draw + display FPS)
        clear();
        pCb->cbDraw(pDat, pScr);
        if(pGame->displayFPS != 0){
            move(0,0);
            printw("|FPS %ld|", (unsigned long)(0.99 + 1000000.0/frameTime));
        }
        refresh();
        // Get frame time
        endTime   = getTimeMicros();
        frameTime = endTime - startTime;
        startTime = endTime; 
        // Wait to achieve 60FPS
        if(frameTime <= 16666){
            usleep(16666-frameTime);
        }       
    }
    // Call finish here and exit
    pCb->cbFinish(pDat);
    // Finish curses
    echo();
    endwin();
}


