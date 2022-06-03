#ifndef KEYS_H
    #define KEYS_H

    typedef enum {

        KEY_UNKNOWN = 0,

        KEY_A = 'A',
        KEY_B = 'B',
        KEY_C = 'C',
        KEY_D = 'D',
        KEY_E = 'E',
        KEY_F = 'F',
        KEY_G = 'G',
        KEY_H = 'H',
        KEY_I = 'I',
        KEY_J = 'J',
        KEY_K = 'K',
        KEY_L = 'L',
        KEY_M = 'M',
        KEY_N = 'N',
        KEY_O = 'O',
        KEY_P = 'P',
        KEY_Q = 'Q',
        KEY_R = 'R',
        KEY_S = 'S',
        KEY_T = 'T',
        KEY_U = 'U',
        KEY_V = 'V',
        KEY_W = 'W',
        KEY_X = 'X',
        KEY_Y = 'Y',
        KEY_Z = 'Z',

        KEY_1 = '0',
        KEY_2 = '1',
        KEY_3 = '2',
        KEY_4 = '3',
        KEY_5 = '4',
        KEY_6 = '5',
        KEY_7 = '6',
        KEY_8 = '7',
        KEY_9 = '8',
        KEY_0 = '9',
    
        KEY_SPACE  = ' ',
        KEY_ENTER  = '\n',
        KEY_ESCAPE = 27,

        KEY_DIVIDE    = '\\',
        KEY_MULTIPLY  = '*',
        KEY_MINUS     = '-',
        KEY_PLUS      = '+',

        EXT_ASCII     = 195,
        
        KEY_E_ACUTE   = ((EXT_ASCII<<8)+169),
        KEY_E_GRAVE   = ((EXT_ASCII<<8)+168),
        KEY_C_CEDILLA = ((EXT_ASCII<<8)+167),
        KEY_A_GRAVE   = ((EXT_ASCII<<8)+160),
        



        KEY_BACKSPACE   = 8,
        KEY_TAB         = 9,
        KEY_CAPSLOCK    = 57,
        
        KEY_F1  = (58 | (1<<30)),
        KEY_F2  = (59 | (1<<30)),
        KEY_F3  = (60 | (1<<30)),
        KEY_F4  = (61 | (1<<30)),
        KEY_F5  = (62 | (1<<30)),
        KEY_F6  = (63 | (1<<30)),
        KEY_F7  = (64 | (1<<30)),
        KEY_F8  = (65 | (1<<30)),
        KEY_F9  = (66 | (1<<30)),
        KEY_F10 = (67 | (1<<30)),
        KEY_F11 = (68 | (1<<30)),
        KEY_F12 = (69 | (1<<30)),


        EXT_ESCAPE       = 27,
        EXT_BRACKET      = 91,

        KEY_HOME         = ((EXT_ESCAPE<<16)|(EXT_BRACKET<<8)|),
        KEY_END          = ,
        KEY_INSERT       = , 

        KEY_PAGEUP       = ,
        KEY_PAGEDOWN     = ,

        KEY_UP           = ,
        KEY_DOWN         = ,
        KEY_LEFT         = ,
        KEY_RIGHT        = ,










        KEY_MINUS           = 45,
        KEY_EQUALS          = 46,
        KEY_LEFTBRACKET     = 47,
        KEY_RIGHTBRACKET    = 48,
        KEY_BACKSLASH       = 49, 
        KEY_NONUSHASH       = 50, 
        KEY_SEMICOLON       = 51,
        KEY_APOSTROPHE      = 52,
        KEY_GRAVE           = 53, 
        KEY_COMMA           = 54,
        KEY_PERIOD          = 55,
        KEY_SLASH           = 56,






        KEY_PRINTSCREEN  = (70 | (1<<30)),
        KEY_SCROLLLOCK   = (71 | (1<<30)),
        KEY_PAUSE        = (72 | (1<<30)),
        KEY_DELETE       = (76 | (1<<30)),


        KEY_NONUSBACKSLASH = 100, 
        KEY_APPLICATION = 101, 
        KEY_POWER = 102, 
        KEY_KP_EQUALS = 103,





        KEY_KP_LEFTPAREN = 182,
        KEY_KP_RIGHTPAREN = 183,
        KEY_KP_LEFTBRACE = 184,
        KEY_KP_RIGHTBRACE = 185,
        KEY_KP_TAB = 186,
        KEY_KP_BACKSPACE = 187,
        KEY_KP_POWER = 195,
        KEY_KP_PERCENT = 196,

        KEY_KP_VERTICALBAR = 201,

        KEY_KP_COLON = 203,
        KEY_KP_HASH = 204,
        KEY_KP_SPACE = 205,
        KEY_KP_EXCLAM = 207,

        KEY_KP_PLUSMINUS = 215,



    } KeyRGR;

#endif 
