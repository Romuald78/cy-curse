#include <stdio.h>
#include <stdlib.h>

#include "libGameRGR2.h"

#define GRASS     1
#define CHARACTER 2


// User data for the game
typedef struct{
    char x;
    char y;
} UserData;



//-------------------------------------------------------------
// INIT 
//-------------------------------------------------------------
void init(void* pUserData, Screen* pScreen){
    UserData* pDat = NULL;
    if(pUserData==NULL){
        RAGE_QUIT(10, "Game user data pointer NULL !\n");    
    }
    if(pScreen==NULL){
        RAGE_QUIT(11, "Game screen pointer NULL !\n");    
    }
    pDat = (UserData*)pUserData;

    // User code here
    
    
    // init position
    pDat->x = 10;
    pDat->y = 10;
    // set grass color
    setColor(GRASS, 128,255,128);
    setColorPair(1, GRASS, GRASS);
    // Set player color 
    setColor(CHARACTER, 128, 128, 255);   
    setColorPair(2, CHARACTER, GRASS);

}

//-------------------------------------------------------------
// EVENT 
//-------------------------------------------------------------
void event(void* pUserData, Screen* pScreen, Event* pEvt){
    UserData* pDat = NULL;
    if(pUserData==NULL){
        RAGE_QUIT(20, "Game user data pointer NULL !\n");    
    }
    if(pScreen==NULL){
        RAGE_QUIT(21, "Game screen pointer NULL !\n");    
    }
    if(pEvt==NULL){
        RAGE_QUIT(22, "Game screen pointer NULL !\n");    
    }
    pDat = (UserData*)pUserData;

    // User code here
    
    switch(pEvt->code){
        case KEY_ARROW_LEFT :
            pDat->x--;
            break;
        case KEY_ARROW_RIGHT :
            pDat->x++;
            break;
        case KEY_ARROW_UP :
            pDat->y--;
            break;
        case KEY_ARROW_DOWN :
            pDat->y++;
            break;

        case KEY_TAB :
            debug("TAB\n");
            break;
        case KEY_RETURN :
            debug("RETURN\n");
            break;
        case KEY_DELETE :
            debug("DELETE\n");
            break;
        case KEY_SPACE :
            debug("SPACE\n");
            break;

        case KEY_F1 : 
            debug("F1\n");
            break;
        case KEY_F2 : 
            debug("F2\n");
            break;
        case KEY_F3 : 
            debug("F3\n");
            break;
        case KEY_F4 : 
            debug("F4\n");
            break;
        case KEY_F5 : 
            debug("F5\n");
            break;
        case KEY_F6 : 
            debug("F6\n");
            break;
        case KEY_F7 : 
            debug("F7\n");
            break;
        case KEY_F8 : 
            debug("F8\n");
            break;
        case KEY_F9 : 
            debug("F9\n");
            break;
        case KEY_F11 : 
            debug("F11\n");
            break;
        case KEY_F12 : 
            debug("F12\n");
            break;
            
        default : 
            if(pEvt->code < 127){
                debug("%c\n", pEvt->code);
            }
            break;
    }
    
    
    
}

//-------------------------------------------------------------
// UPDATE 
//-------------------------------------------------------------
int  update(void* pUserData, Screen* pScreen, unsigned long deltaTime){
    UserData* pDat = NULL;
    if(pUserData==NULL){
        RAGE_QUIT(30, "Game user data pointer NULL !\n");    
    }
    if(pScreen==NULL){
        RAGE_QUIT(31, "Game screen pointer NULL !\n");    
    }
    pDat = (UserData*)pUserData;

    // User code here
    
    

    // We return 0 to tell to continue, else the program will stop
    return 0;
}

//-------------------------------------------------------------
// DRAW 
//-------------------------------------------------------------
void draw(void* pUserData, Screen* pScreen){
    UserData* pDat = NULL;
    if(pUserData==NULL){
        RAGE_QUIT(40, "Game user data pointer NULL !\n");    
    }
    if(pScreen==NULL){
        RAGE_QUIT(41, "Game screen pointer NULL !\n");    
    }
    pDat = (UserData*)pUserData;

    // user code here
    for(int y=0; y<(pScreen->height); y++){
        drawLine(pScreen, 0, y, pScreen->width, '.', 2);
    }

    drawText(pScreen, pDat->x, pDat->y,   "🐎🐇"  , 2);
    
    
}

//-------------------------------------------------------------
// FINISH
//-------------------------------------------------------------
void finish(void* pUserData){
    UserData* pDat = NULL;
    if(pUserData==NULL){
        RAGE_QUIT(500, "Game user data pointer NULL !\n");    
    }
    pDat = (UserData*)pUserData;

    // user code here



}

//-------------------------------------------------------------
// MAIN 
//-------------------------------------------------------------
int main(int argc, char** argv){

    // Declare vars
    GameData* pGame = NULL;
    UserData  data;    
    Callbacks cb;

    // Fill the callback structure
    cb.cbInit   = init;
    cb.cbEvent  = event;
    cb.cbUpdate = update;
    cb.cbDraw   = draw;
    cb.cbFinish = finish;

    // Create the game structure
    pGame = createGame(30,15, &data, &cb, 0);
    
    // Launch the game 
    gameLoop(pGame);
    
    // end of program
    return 0; 
}

