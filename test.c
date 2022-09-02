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
    
    switch(pEvt->code){
        case KEY_ARROW_LEFT :
            debug("LEFT\n");
            break;
        case KEY_ARROW_RIGHT :
            debug("RIGHT\n");
            break;
        case KEY_ARROW_UP :
            debug("UP\n");
            break;
        case KEY_ARROW_DOWN :
            debug("DOWN\n");
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

