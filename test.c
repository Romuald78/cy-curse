#include <stdio.h>
#include <stdlib.h>

#include "libGameRGR2.h"

typedef struct{
    unsigned char carac;
} UserData;

void init(void* pUserData, Screen* pScreen){
    UserData* pDat = NULL;
    if(pUserData==NULL){
        RAGE_QUIT(100, "Game user data pointer NULL !\n");    
    }
    if(pScreen==NULL){
        RAGE_QUIT(101, "Game screen pointer NULL !\n");    
    }
    pDat = (UserData*)pUserData;
    
    pDat->carac = ' ';
}

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

    debug("character=|%c| value=|%3d|\n", pDat->carac, pEvt->code);
    pDat->carac += 1;
}

int  update(void* pUserData, Screen* pScreen, unsigned long deltaTime){
    UserData* pDat = NULL;
    if(pUserData==NULL){
        RAGE_QUIT(300, "Game user data pointer NULL !\n");    
    }
    if(pScreen==NULL){
        RAGE_QUIT(301, "Game screen pointer NULL !\n");    
    }
    pDat = (UserData*)pUserData;

    if (pDat->carac > 127){
        return 1;
    }

    return 0;
}

void draw(void* pUserData, Screen* pScreen){
    UserData* pDat = NULL;
    if(pUserData==NULL){
        RAGE_QUIT(400, "Game user data pointer NULL !\n");    
    }
    if(pScreen==NULL){
        RAGE_QUIT(401, "Game screen pointer NULL !\n");    
    }
    pDat = (UserData*)pUserData;

    move(10,10);
    printw("|%c|", pDat->carac);
}

void finish(void* pUserData){
    UserData* pDat = NULL;
    if(pUserData==NULL){
        RAGE_QUIT(500, "Game user data pointer NULL !\n");    
    }
    pDat = (UserData*)pUserData;


}

int main(int argc, char** argv){

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

    
    
/*
    // Init 'curses' library
    initscr();
    // Colors are useable
    start_color();
    // define text/background color pairs (with color index)
    init_pair(1, COLOR_YELLOW, COLOR_BLACK);
    // No echo for key press
    noecho();
    // no cursor displayed
    curs_set(0);
    
    // Variables (position of the player)
    int x = 2;
    int y = 2;
    int last_y = 1;    
        
    // Game loop
    while(1){
        // -----------------------------------        
        // DISPLAY SCREEN DATA
        // -----------------------------------        
        clear();
        // Draw border
        move(0,0);
        printw(" #");
        for(int dx=1;dx<=19;dx++){
            printw("##");
        }                
        printw("# ");
        move(20,0);
        printw(" #");
        for(int dx=1;dx<=19;dx++){
            printw("##");
        }                
        printw("# ");
        for(int dy=1;dy<=19;dy++){
            move(dy,0);
            printw(" #");
            move(dy,2*20);
            printw("# ");
        }
        // Draw player (@) at position (x,y)
        // Set color pair 1 (defined above)
        attron(COLOR_PAIR(1));
        move(y,2*x);
        printw("@ @");            
        move(y+1,2*x);
        if(last_y == 1){
            printw("  >");            
        }
        else{
            printw("<  ");
        }
        move(y+2,2*x);
        printw(" o ");
        // reset color pair 0
        attroff(COLOR_PAIR(1));
        // all drawings are displayed really
        refresh();

        // -----------------------------------
        // Get key code from keyboard
        // -----------------------------------        
        int c = getch();
        // If there is no actual keyboard active, it returns ERR
        if(c != ERR){
            // The ESCAPE key has been pressed            
            if(c==27){
                // Exit from game loop
                break;
            }
            
            // KEYPAD_2 has been pressed (down)
            if (c==50){
                y++;
                if(y>17) y=17;
            }
            // KEYPAD_4 has been pressed (left)
            if (c==52){
                x--;                
                last_y = -1;
                if(x<1) x=1;
            }
            // KEYPAD_6 has been pressed (right)
            if (c==54){
                x++;
                last_y = 1;
                if(x>18) x=18;
            }
            // KEYPAD_8 has been pressed (up)
            if (c==56){
                y--;
                if(y<1) y=1;
            }    
        }
    }  

    // Terminate curses library use
    echo();
    endwin();
//*/
 
}
