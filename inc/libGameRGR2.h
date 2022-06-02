#ifndef LIBGAMERGR_H
    #define LIBGAMERGR_H

    //------------------------------
    // INCLUDES
    //------------------------------
    #include <curses.h>

    //------------------------------
    // CONSTANTS
    //------------------------------
    
    //------------------------------
    // ENUMS, STRUCTURES AND CALLBACKS
    //------------------------------
    // Key code
    typedef int KeyCode;
    // Event structure
    typedef struct {
        KeyCode  code;      
    } Event;            
    // Canvas Structure
    typedef struct {
        int width;      // number of characters along X-axis
        int height;     // number of characters along Y-axis
    } Screen;       
    // User Callback Functions
    typedef void (*InitCallback  )(void* pUSerData, Screen* pScreen);
    typedef void (*EventCallback )(void* pUserData, Screen* pScreen, Event* pEvt);
    typedef int  (*UpdateCallback)(void* pUserData, Screen* pScreen, unsigned long deltaTime);
    typedef void (*DrawCallback  )(void* pUSerData, Screen* pScreen);
    typedef void (*FinishCallback)(void* pUserData);
    // Callback structure
    typedef struct{
        InitCallback   cbInit;        
        EventCallback  cbEvent;        
        UpdateCallback cbUpdate;
        DrawCallback   cbDraw;
        FinishCallback cbFinish;        
    } Callbacks;    
    // Full game structure
    typedef struct{
        Screen*    pScreen;
        void*      pUserData;
        Callbacks* pUserCallbacks; 
        int        displayFPS;       
    } GameData;
    
    //------------------------------
    // FUNCTIONS
    //------------------------------           
    // Errors
    void rageQuit(const char* fname,
              const int   lineno,
              const char* fxname,
              const int   errorCode,
              const char* format, ...);
    #define RAGE_QUIT(errCode, format, ...) rageQuit(__FILE__, __LINE__, __func__, errCode, format, ##__VA_ARGS__)
    // debug 
    void debug(const char* format, ...);
    // Game functions
    GameData* createGame(int nbCharX, int nbCharY, void* pUserData, Callbacks* pCb, int fps);
    void gameLoop(GameData* pGame);
    // Draw API TODO
    void drawText(Screen* pScreen, int x, int y, char* pText);
#endif
