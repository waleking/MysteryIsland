#include <windows.h> 
#include <windowsx.h> 
#include <mmsystem.h>
#include <conio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <malloc.h>
#include <memory.h>
#include <string.h>
#include <stdarg.h>
#include <stdio.h> 
#include <math.h>
#include <io.h>
#include <fcntl.h>
#include <dshow.h>
#include <ddraw.h>
#include <dsound.h>
#include <dinput.h>
#include <stdlib.h>
#include <time.h>

#pragma comment(lib,"ddraw.lib") 
#pragma comment(lib,"Winmm.lib") 
#pragma comment(lib,"dsound.lib")
#pragma comment(lib,"dxguid.lib")
#pragma comment(lib,"dinput.lib")
#pragma comment(lib,"dinput8.lib")
#pragma comment(lib,"dplay.lib")
#include "wave.h"
#include "image.h"
#include "dinput.h"
#include "Person.h"

// TYPES //////////////////////////////////////////////////////

// basic unsigned types
typedef unsigned short USHORT;
typedef unsigned short WORD;
typedef unsigned char  UCHAR;
typedef unsigned char  BYTE;
// MACROS /////////////////////////////////////////////////

// tests if a key is up or down
#define KEYDOWN(vk_code) ((GetAsyncKeyState(vk_code) & 0x8000) ? 1 : 0)
#define KEYUP(vk_code)   ((GetAsyncKeyState(vk_code) & 0x8000) ? 0 : 1)

//////////////////////////////////////////////////////////////////////////

enum GAME_STATE{Help,Gameseletct,Island,Playfield,Temple_red,Temple_yellow,Temple_purple,Temple_blue,AboutUs,Quit};

extern int gGame_state;

enum Direction{Up=0,Right=1,Down=2,Left=3};

enum Chess_State{Empty=0,Want_to_be_filled=1,Have_been_filled=2,Temp_occupied=3,Wall=4};

extern GAME_STATE Temple_temp;

extern LPDIRECTDRAWSURFACE7 gLevel_map_temp;
