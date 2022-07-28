#include <sys/time.h>

#include "libGameRGR2.h"

unsigned long getTimeMicros(){
    struct timeval tv;
    gettimeofday(&tv,NULL);
    return (tv.tv_sec*1000000) + (tv.tv_usec/1);
} 

void checkGame(GameData* pGame, int errCode){
    // Locals
    Screen*    pScr = NULL;
    void*      pDat = NULL;
    Callbacks* pCb  = NULL;
    // Check params
    if(pGame == NULL){
        RAGE_QUIT(errCode, "Game data pointer NULL !\n");
    }
    // Store pointers locally
    pScr = pGame->pScreen;
    pDat = pGame->pUserData;
    pCb  = pGame->pUserCallbacks;
    // Check internal pointers
    if(pScr == NULL){
        RAGE_QUIT(errCode+1, "Game screen pointer NULL !\n");
    }
    if(pDat == NULL){
        RAGE_QUIT(errCode+2, "Game user data pointer NULL !\n");
    }
    if(pCb == NULL){
        RAGE_QUIT(errCode+3, "Game user callback pointer NULL !\n");
    }    
}

int checkEvent(GameData* pGame){
    // Locals
    Screen*    pScr = NULL;
    void*      pDat = NULL;
    Callbacks* pCb  = NULL;
    Event      evt;
    int        ch = ERR+1;
    int        value = KEY_NONE;
    int        size  = 0;
    int        flagASCII = 0;
    int        flagESC   = 0;
    int        flagCSI   = 0;
    int        flagSPC   = 0;
    // Check params
    checkGame(pGame, 3000);
    // Store pointers locally
    pScr = pGame->pScreen;
    pDat = pGame->pUserData;
    pCb  = pGame->pUserCallbacks;
    
    // Get all key values from the stdin
    // Some keys generate several bytes
    while( (ch=getch()) != ERR ){  
        debug("|%3d|\n", ch);  
        value = (value<<8) | ch;
        size++;
        // Retrieve flags
        flagASCII = (size==1) && (value != EXT_ESC) && (value>=0) && (value<=127);        
        flagESC   = (size==1) && (value == EXT_ESC);
        flagSPC   = (size==2) && ((value & 0x0000FF00) == EXT_SPEC);        
        flagCSI   = (size==3) && ((value & 0x00FFFF00) == EXT_CSI); 
        
        // DEBUG
        if (flagASCII){
            if(value>='a' && value <='z'){
                value -= 32;
            }
            debug("ASCII   |%c/%d| \n", value, value);
        }
        if (flagCSI){
            debug("CSI     |%d/%d| \n", value&0xFF,value&0xFF);
        }
        if ( flagSPC ){
            debug("SPECIAL |%d/%d| \n", value&0xFF,value&0xFF);
        }
        // END DEBUG
        
        if( flagASCII || flagCSI || flagSPC ){
            evt.code = value;
            pCb->cbEvent(pDat, pScr, &evt);            
            value    = KEY_NONE;
            size     = 0;
        }
    }
    
    if(flagESC){
        return 1;
    }
    else{
        return 0;
    }
}

/*
void writeTerm(

    init_pair(1, rand()%8, rand()%8);
    attron(COLOR_PAIR(1));
    move(rand()%10, rand()%20);
    printw("#");
*/



