#include <stdio.h>
#include <stdlib.h>

#include "libGameRGR2.h"

// User data for the game
typedef struct{
    unsigned char x;
    unsigned char y;
} UserData;



//-------------------------------------------------------------
// INIT 
//-------------------------------------------------------------
void init(void* pUserData, Screen* pScreen){
    UserData* pDat = NULL;
    if(pUserData==NULL){
        RAGE_QUIT(100, "Game user data pointer NULL !\n");    
    }
    if(pScreen==NULL){
        RAGE_QUIT(101, "Game screen pointer NULL !\n");    
    }
    pDat = (UserData*)pUserData;

    // User code here
    


}

//-------------------------------------------------------------
// EVENT 
//-------------------------------------------------------------
void event(void* pUserData, Screen* pScreen, Event* pEvt){
    UserData* pDat = NULL;
    if(pUserData==NULL){
        RAGE_QUIT(200, "Game user data pointer NULL !\n");    
    }
    if(pScreen==NULL){
        RAGE_QUIT(201, "Game screen pointer NULL !\n");    
    }
    if(pEvt==NULL){
        RAGE_QUIT(202, "Game screen pointer NULL !\n");    
    }
    pDat = (UserData*)pUserData;

    // User code here
    // debug("event : |0x%x| \n", pEvt->code);
    
    
    
}

//-------------------------------------------------------------
// UPDATE 
//-------------------------------------------------------------
int  update(void* pUserData, Screen* pScreen, unsigned long deltaTime){
    UserData* pDat = NULL;
    if(pUserData==NULL){
        RAGE_QUIT(300, "Game user data pointer NULL !\n");    
    }
    if(pScreen==NULL){
        RAGE_QUIT(301, "Game screen pointer NULL !\n");    
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
        RAGE_QUIT(400, "Game user data pointer NULL !\n");    
    }
    if(pScreen==NULL){
        RAGE_QUIT(401, "Game screen pointer NULL !\n");    
    }
    pDat = (UserData*)pUserData;

    // user code here



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
    pGame = createGame(20,10, &data, &cb, 1);
    
    // Launch the game 
    gameLoop(pGame);
    
    // end of program
    return 0; 
}

