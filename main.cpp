//////////////////////////////////////////////////////////////////////////
//2006.6.7 23:14
//
//神秘岛工作室
//
#define WIN32_LEAN_AND_MEAN  // just say no to MFC

#define INITGUID
#include "include.h"
#include "resource.h"


void _Gameselect();

void _Island(CPerson &DaVinci);

void _Playfield(CPerson &DaVinci);

void _Temple_red(CPerson &DaVinci);

void _Temple_yellow(CPerson &DaVinci);

void _Temple_purple(CPerson &DaVinci);

void _Temple_blue(CPerson &DaVinci);

void _Help();

void _AboutUs();

void _Quit();

using namespace std;
////GLOBALS//////////////////////////////////////////////////////////////////////////

HINSTANCE main_hinstance      = NULL; 
int       window_closed      = 0;    // tracks if window is closed
HWND      main_window_handle = NULL;// globally track hinstance

int gGame_state=Gameseletct;
int backmusic_option=SOUND_NULL;//控制声音的量，一旦背景音乐播放就不让它停下来
int sound_menu_mouseover=SOUND_NULL;//其他声音
int sound_menu_click1=SOUND_NULL;//鼠标点击的声音
int sound_island_mouseover=SOUND_NULL;

GAME_STATE Temple_temp;

LPDIRECTDRAWSURFACE7 gLevel_map_temp;

//////////////////////////////////////////////////////////////////////////

LRESULT CALLBACK WindowProc(HWND hwnd, 
						    UINT msg, 
                            WPARAM wparam, 
                            LPARAM lparam)
{
// this is the main message handler of the system
PAINTSTRUCT		ps;		// used in WM_PAINT
HDC				hdc;	// handle to a device context
//char buffer[80];        // used to print strings

// what is the message 
switch(msg)
	{	
	case WM_CREATE: 
        {
		// do initialization stuff here
        // return success
		return(0);
		} break;
   
	case WM_PAINT: 
		{
		// simply validate the window 
   	    hdc = BeginPaint(hwnd,&ps);	 
        
        // end painting
        EndPaint(hwnd,&ps);

        // return success
		return(0);
   		} break;

	case WM_DESTROY: 
		{

		// kill the application, this sends a WM_QUIT message 
		PostQuitMessage(0);

        // return success
		return(0);
		} break;

	default:break;

    } // end switch

// process any messages that we didn't take care of 
return (DefWindowProc(hwnd, msg, wparam, lparam));

} // end WinProc

/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////
int Game_Main(CPerson &DaVinci)//
{
//////////////////////////////////////////////////////////////////////////////////////////////
// make sure this isn't executed again
if (window_closed)
   return(0);

// for now test if user is hitting ESC and send WM_CLOSE
if (KEYDOWN(VK_ESCAPE))
   {
   PostMessage(main_window_handle,WM_CLOSE,0,0);
   window_closed = 1;
   } // end if

//////////////////////////////////////////////////////////////////////////////////////////////
////Dinput////
lpdimouse->GetDeviceState(sizeof(DIMOUSESTATE), (LPVOID)&mouse_state);
lpdikey->GetDeviceState(256, (LPVOID)keyboard_state);
// move the mouse cursor
mouse_x+=(mouse_state.lX);
mouse_y+=(mouse_state.lY);

// test bounds

// first x boundaries
if (mouse_x >= SCREEN_WIDTH)
   mouse_x = SCREEN_WIDTH-1;
else
if (mouse_x < 0)
   mouse_x = 0;

// now the y boundaries
if (mouse_y >= SCREEN_HEIGHT)
   mouse_y= SCREEN_HEIGHT-1;
else
if (mouse_y < 0)
   mouse_y = 0;

//////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////////
// this is the main loop of the game, do all your processing
// here
switch(gGame_state)
{

case Gameseletct:
	_Gameselect();break;//case Gameseletct的结束

case Island:
	_Island(DaVinci);break;

case Temple_blue:
	_Temple_blue(DaVinci);break;

case Temple_purple:
	_Temple_purple(DaVinci);break;

case Temple_yellow:
	_Temple_yellow(DaVinci);break;

case Temple_red:
	_Temple_red(DaVinci);break;

case Playfield:
	_Playfield(DaVinci);break;

case Help:
	_Help();break;

case AboutUs:
	_AboutUs();break;

case Quit:
	_Quit();break;
}//end of switch


////绘制鼠标//////////////////////////////////////////////////////////////////////////

DDraw_Draw_Surface(lpdds_cursor_pointer,mouse_x,mouse_y,20,20,lpddsback,1);
//////////////////////////////////////////////////////////////////////////

    while (FAILED(lpddsprimary->Flip(NULL, DDFLIP_WAIT)));/**/ ////HW：后备缓冲和主表面的切换
	Sleep(30);

// wait a sec


// return success or failure or your own return code here
return(1);

} // end Game_Main

//////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////

int Game_Init()
{
////设置鼠标初始的位置////////////////////////////////////////////////////////////////////////////
mouse_x = SCREEN_WIDTH/2;
mouse_y = SCREEN_HEIGHT/2;
////设置DDRAW//////////////////////////////////////////////////////////////////////////
if (FAILED(DirectDrawCreateEx(NULL, (void **)&lpdd, IID_IDirectDraw7, NULL)))
   return(0);

if (FAILED(lpdd->SetCooperativeLevel(main_window_handle, 
                                      DDSCL_FULLSCREEN | DDSCL_ALLOWMODEX | 
                                      DDSCL_EXCLUSIVE | DDSCL_ALLOWREBOOT)))
   return(0);

if (FAILED(lpdd->SetDisplayMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP,0,0)))
   return(0);

DDRAW_INIT_STRUCT(ddsd); 
ddsd.dwFlags = DDSD_CAPS | DDSD_BACKBUFFERCOUNT;
ddsd.dwBackBufferCount = 1;
ddsd.ddsCaps.dwCaps = DDSCAPS_PRIMARYSURFACE | DDSCAPS_COMPLEX | DDSCAPS_FLIP;

if (FAILED(lpdd->CreateSurface(&ddsd, &lpddsprimary, NULL)))
   return(0);
ddsd.ddsCaps.dwCaps = DDSCAPS_BACKBUFFER;

if (FAILED(lpddsprimary->GetAttachedSurface(&ddsd.ddsCaps, &lpddsback)))
  return(0);

RECT screen_rect= {0,0,SCREEN_WIDTH-1,SCREEN_HEIGHT-1};
lpddclipper = DDraw_Attach_Clipper(lpddsback,1,&screen_rect);   //HW: DDraw_Attach_Clipper()函数直接可调用

DDraw_Fill_Surface(lpddsprimary,0);//HW:DDraw_Fill_Surface()用于用一种颜色填充一个表面，可直接调用
DDraw_Fill_Surface(lpddsback,0);
////lpdds_backtitle的创建//////////////////////////////////////////////////////////////////////////
    if(!Load_Bitmap_File(&map_backtitle,"images\\backtitle.bmp"))
		return(0);
	lpdds_backtitle = DDraw_Create_Surface(SCREEN_WIDTH,SCREEN_HEIGHT,0,1);
	Scan_Image_Bitmap(&map_backtitle,lpdds_backtitle,SCREEN_WIDTH,SCREEN_HEIGHT);
	if(!Unload_Bitmap_File(&map_backtitle))
		return(0);
////lpdds_gameselect离屏表面的创建//////////////////////////////////////////////////////////////////////////
	if(!Load_Bitmap_File(&map_gameselect,"images\\gameselect.bmp"))
		return(0);
	lpdds_gameselect = DDraw_Create_Surface(SCREEN_WIDTH,SCREEN_HEIGHT,0,-1);
	Scan_Image_Bitmap(&map_gameselect,lpdds_gameselect,SCREEN_WIDTH,SCREEN_HEIGHT);
	if(!Unload_Bitmap_File(&map_gameselect))
		return(0);

////help的创建//////////////////////////////////////////////////////////////////////////
	if(!Load_Bitmap_File(&map_help,"images\\help.bmp"))
		return(0);
	lpdds_help = DDraw_Create_Surface(SCREEN_WIDTH,SCREEN_HEIGHT,0,-1);
	Scan_Image_Bitmap(&map_help,lpdds_help,SCREEN_WIDTH,SCREEN_HEIGHT);/**/
   if(!Unload_Bitmap_File(&map_help))
		return(0);   

////lpdds_playfield离屏表面的创建//////////////////////////////////////////////////////////////////////////
	if (!Load_Bitmap_File(&map_playfield,"images\\playfield.bmp")) 
		return(0);
	lpdds_playfield = DDraw_Create_Surface(SCREEN_WIDTH,SCREEN_HEIGHT,0,-1);
	Scan_Image_Bitmap(&map_playfield,lpdds_playfield,SCREEN_WIDTH,SCREEN_HEIGHT);
	if(!Unload_Bitmap_File(&map_playfield))
		return(0); 
////lpdds_island的创建//////////////////////////////////////////////////////////////////////////
	if (!Load_Bitmap_File(&map_island[0],"images\\islandmap.bmp")) 
		return(0);
	lpdds_island = DDraw_Create_Surface(640,360,0,-1);
	Scan_Image_Bitmap(&map_island[0],lpdds_island,640,360);
	if(!Unload_Bitmap_File(&map_island[0]))
		return(0); 
////lpdds_islandsky的创建//////////////////////////////////////////////////////////////////////////
    if (!Load_Bitmap_File(&map_island[1],"images\\islandmapsky.bmp")) 
		return(0);
	lpdds_islandsky = DDraw_Create_Surface(640,120,0,-1);
	Scan_Image_Bitmap(&map_island[1],lpdds_islandsky,640,120);
	if(!Unload_Bitmap_File(&map_island[1]))
		return(0); 
/////鼠标的图象创建////////////////////////////////////////////////
    if(!Load_Bitmap_File((&map_cursor_pointer),"images\\cursor_pointer1.bmp")) return(0);
	lpdds_cursor_pointer=DDraw_Create_Surface(20,20,0,0);
	Scan_Image_Bitmap(&map_cursor_pointer,lpdds_cursor_pointer,20,20);
	if(!Unload_Bitmap_File(&map_cursor_pointer))
		return(0);
//////用于显示鼠标位置的一个区域///////////////////////////////////////////////////////
    if(!Load_Bitmap_File(&map_black,"images\\black.bmp"))
	    return(0);

	lpdds_black=DDraw_Create_Surface(640,480,0,1);
	Scan_Image_Bitmap(&map_black,lpdds_black,640,480);
    if(!Unload_Bitmap_File(&map_black))
		return(0);/**/

////temple_red的创建//////////////////////////////////////////////////////////////////////////
    if(!Load_Bitmap_File(&map_temple_red,"images\\selectpuzzlebdrop_red副本.bmp"))
	    return(0);

	lpdds_temple_red=DDraw_Create_Surface(640,480,0,-1);
	Scan_Image_Bitmap(&map_temple_red,lpdds_temple_red,640,480);
    if(!Unload_Bitmap_File(&map_temple_red))
		return(0);/**/
 
////temple_yellow的创建//////////////////////////////////////////////////////////////////////////
   if(!Load_Bitmap_File(&map_temple_yellow,"images\\selectpuzzlebdrop_yellow副本.bmp"))
	    return(0);

	lpdds_temple_yellow=DDraw_Create_Surface(640,480,0,-1);
	Scan_Image_Bitmap(&map_temple_yellow,lpdds_temple_yellow,640,480);
    if(!Unload_Bitmap_File(&map_temple_yellow))
		return(0);/**/
////temple_blue的创建//////////////////////////////////////////////////////////////////////////
    if(!Load_Bitmap_File(&map_temple_blue,"images\\selectpuzzlebdrop_blue副本.bmp"))
	    return(0);

	lpdds_temple_blue=DDraw_Create_Surface(640,480,0,-1);
	Scan_Image_Bitmap(&map_temple_blue,lpdds_temple_blue,640,480);
    if(!Unload_Bitmap_File(&map_temple_blue))
		return(0);/**/
////temple_purple的创建//////////////////////////////////////////////////////////////////////////
   if(!Load_Bitmap_File(&map_temple_purple,"images\\selectpuzzlebdrop_purple副本.bmp"))
	    return(0);

	lpdds_temple_purple=DDraw_Create_Surface(640,480,0,-1);
	Scan_Image_Bitmap(&map_temple_purple,lpdds_temple_purple,640,480);
    if(!Unload_Bitmap_File(&map_temple_purple))
		return(0);/**/
////slider_up,slider_down的创建
	if(!Load_Bitmap_File(&map_slider_down,"images\\sliderdown.bmp"))
	    return(0);

	lpdds_slider_down=DDraw_Create_Surface(16,16,0,1);
	Scan_Image_Bitmap(&map_slider_down,lpdds_slider_down,16,16);
    if(!Unload_Bitmap_File(&map_slider_down))
		return(0);/**/
	if(!Load_Bitmap_File(&map_slider_up,"images\\sliderup.bmp"))
	    return(0);

	lpdds_slider_up=DDraw_Create_Surface(16,16,0,1);
	Scan_Image_Bitmap(&map_slider_up,lpdds_slider_up,16,16);
    if(!Unload_Bitmap_File(&map_slider_up))
		return(0);/**/
////menu_backtoisland
	if(!Load_Bitmap_File(&map_menu_backtoisland[0],"images\\backtoisland1.bmp"))
	    return(0);

	lpdds_menu_backtoisland[0]=DDraw_Create_Surface(136,60,0,1);
	Scan_Image_Bitmap(&map_menu_backtoisland[0],lpdds_menu_backtoisland[0],136,60);
    if(!Unload_Bitmap_File(&map_menu_backtoisland[0]))
		return(0);/**/	

	if(!Load_Bitmap_File(&map_menu_backtoisland[1],"images\\backtoisland2.bmp"))
	    return(0);

	lpdds_menu_backtoisland[1]=DDraw_Create_Surface(136,60,0,1);
	Scan_Image_Bitmap(&map_menu_backtoisland[1],lpdds_menu_backtoisland[1],136,60);
    if(!Unload_Bitmap_File(&map_menu_backtoisland[1]))
		return(0);/**/	
////menu_help的创建//////////////////////////////////////////////////////////////////////////
	if(!Load_Bitmap_File(&map_menu_help[0],"images\\help1.bmp"))
		return(0);
	lpdds_menu_help[0] = DDraw_Create_Surface(128,84,0,1);
	Scan_Image_Bitmap(&map_menu_help[0],lpdds_menu_help[0],128,84);/**/
   if(!Unload_Bitmap_File(&map_menu_help[0]))
		return(0);    
   //
	if(!Load_Bitmap_File(&map_menu_help[1],"images\\help2.bmp"))
		return(0);
	lpdds_menu_help[1] = DDraw_Create_Surface(128,84,0,1);
	Scan_Image_Bitmap(&map_menu_help[1],lpdds_menu_help[1],128,84);/**/
   if(!Unload_Bitmap_File(&map_menu_help[1]))
		return(0);   
////menu_aboutus的创建//////////////////////////////////////////////////////////////////////////
	if(!Load_Bitmap_File(&map_menu_aboutus[0],"images\\aboutus1.bmp"))
		return(0);
	lpdds_menu_aboutus[0] = DDraw_Create_Surface(144,44,0,1);
	Scan_Image_Bitmap(&map_menu_aboutus[0],lpdds_menu_aboutus[0],144,44);/**/
   if(!Unload_Bitmap_File(&map_menu_aboutus[0]))
		return(0);    
   //
	if(!Load_Bitmap_File(&map_menu_aboutus[1],"images\\aboutus2.bmp"))
		return(0);
	lpdds_menu_aboutus[1] = DDraw_Create_Surface(144,44,0,1);
	Scan_Image_Bitmap(&map_menu_aboutus[1],lpdds_menu_aboutus[1],144,44);/**/
   if(!Unload_Bitmap_File(&map_menu_aboutus[1]))
		return(0);   
////about us的创建//////////////////////////////////////////////////////////////////////////
 	if(!Load_Bitmap_File(&map_aboutus,"images\\aboutus.bmp"))
		return(0);
	lpdds_aboutus = DDraw_Create_Surface(SCREEN_WIDTH,SCREEN_HEIGHT,0,-1);
	Scan_Image_Bitmap(&map_aboutus,lpdds_aboutus,SCREEN_WIDTH,SCREEN_HEIGHT);/**/
   if(!Unload_Bitmap_File(&map_aboutus))
		return(0); 

   
////meun_play的创建//////////////////////////////////////////////////////////////////////////
	if(!Load_Bitmap_File(&map_menu_play,"images\\gameselectorbutton_play1.bmp"))
		return(0);
	lpdds_menu_play = DDraw_Create_Surface(116,120,0,1);
	Scan_Image_Bitmap(&map_menu_play,lpdds_menu_play,116,120);/**/
   if(!Unload_Bitmap_File(&map_menu_play))
		return(0);

////menu_quit的创建//////////////////////////////////////////////////////////////////////////
	if(!Load_Bitmap_File(&map_menu_quit,"images\\gameselectorbutton_quit1.bmp"))
		return(0);
	lpdds_menu_quit = DDraw_Create_Surface(108,40,0,1);
	Scan_Image_Bitmap(&map_menu_quit,lpdds_menu_quit,108,40);
   if(!Unload_Bitmap_File(&map_menu_quit))
		return(0);
////quit的创建//////////////////////////////////////////////////////////////////////////
    if(!Load_Bitmap_File(&map_quit,"images\\quit.bmp"))
		return(0);
	lpdds_quit = DDraw_Create_Surface(340,216,0,1);
	Scan_Image_Bitmap(&map_quit,lpdds_quit,340,216);
   if(!Unload_Bitmap_File(&map_quit))
		return(0);
////menu_backtotemple的创建//////////////////////////////////////////////////////////////////////////
    if(!Load_Bitmap_File(&map_menu_backtotemple[0],"images\\backtotemple1.bmp"))
		return(0);
	lpdds_menu_backtotemple[0] = DDraw_Create_Surface(144,64,0,1);
	Scan_Image_Bitmap(&map_menu_backtotemple[0],lpdds_menu_backtotemple[0],144,64);/**/
   if(!Unload_Bitmap_File(&map_menu_backtotemple[0]))
		return(0);
   if(!Load_Bitmap_File(&map_menu_backtotemple[1],"images\\backtotemple2.bmp"))
		return(0);
	lpdds_menu_backtotemple[1] = DDraw_Create_Surface(144,64,0,1);
	Scan_Image_Bitmap(&map_menu_backtotemple[1],lpdds_menu_backtotemple[1],144,64);/**/
   if(!Unload_Bitmap_File(&map_menu_backtotemple[1]))
		return(0);
////menu_backtomainmenu的创建//////////////////////////////////////////////////////////////////////////
    if(!Load_Bitmap_File(&map_menu_backtomainmenu[0],"images\\backtomainmenu1.bmp"))
		return(0);
	if(!Load_Bitmap_File(&map_menu_backtomainmenu[1],"images\\backtomainmenu2.bmp"))
		return(0);
	if(!Load_Bitmap_File(&map_menu_backtomainmenu[2],"images\\backtomainmenu3.bmp"))
		return(0);
	for(int i=0;i<3;i++)
	{
		lpdds_menu_backtomainmenu[i] = DDraw_Create_Surface(116,56,0,1);
		Scan_Image_Bitmap(&map_menu_backtomainmenu[i],lpdds_menu_backtomainmenu[i],116,56);/**/
		if(!Unload_Bitmap_File(&map_menu_backtomainmenu[i]))
			return(0);
	}
/////red_levels
	for(i=0;i<13;i++)
	{
		char str1[30]={"red_level\\"};
		char cnumber[3];
		if(i<9) 
		{ cnumber[0]=i+49;cnumber[1]='\0';
		}
		if(i>=9)
		{
			cnumber[0]='1';cnumber[1]=i-10+49;//查ASCII码表后得到
			cnumber[2]='\0';
		}
		char str3[]={".bmp"};
		strcat(str1,cnumber);
		strcat(str1,str3);
		if(!Load_Bitmap_File(&map_red_level[i],str1))
		 return(0);
	}
	for(i=0;i<13;i++)
	{
	lpdds_red_level[i] = DDraw_Create_Surface(16,16,0,0);
	Scan_Image_Bitmap(&map_red_level[i],lpdds_red_level[i],16,16);
   if(!Unload_Bitmap_File(&map_red_level[i]))
		return(0);
	}
////purple_level
	for(i=0;i<15;i++)
	{
		char str1[30]={"purple_level\\"};
		char cnumber[3];
		if(i<9) 
		{ cnumber[0]=i+49;cnumber[1]='\0';
		}
		if(i>=9)
		{
			cnumber[0]='1';cnumber[1]=i-10+49;//查ASCII码表后得到
			cnumber[2]='\0';
		}
		char str3[]={".bmp"};
		strcat(str1,cnumber);
		strcat(str1,str3);
		if(!Load_Bitmap_File(&map_purple_level[i],str1))
		 return(0);
	}
	for(i=0;i<15;i++)
	{
	lpdds_purple_level[i] = DDraw_Create_Surface(16,16,0,0);
	Scan_Image_Bitmap(&map_purple_level[i],lpdds_purple_level[i],16,16);
   if(!Unload_Bitmap_File(&map_purple_level[i]))
		return(0);
	}
////
	////blue_level
	for(i=0;i<18;i++)
	{
		char str1[30]={"blue_level\\"};
		char cnumber[3];
		if(i<9) 
		{ cnumber[0]=i+49;cnumber[1]='\0';
		}
		if(i>=9)
		{
			cnumber[0]='1';cnumber[1]=i-10+49;//查ASCII码表后得到
			cnumber[2]='\0';
		}
		char str3[]={".bmp"};
		strcat(str1,cnumber);
		strcat(str1,str3);
		if(!Load_Bitmap_File(&map_blue_level[i],str1))
		 return(0);
	}
	for(i=0;i<18;i++)
	{
	lpdds_blue_level[i] = DDraw_Create_Surface(16,16,0,0);
	Scan_Image_Bitmap(&map_blue_level[i],lpdds_blue_level[i],16,16);
   if(!Unload_Bitmap_File(&map_blue_level[i]))
		return(0);
	}
////yellow_level
	for(i=0;i<18;i++)
	{
		char str1[30]={"yellow_level\\"};
		char cnumber[3];
		if(i<9) 
		{ cnumber[0]=i+49;cnumber[1]='\0';
		}
		if(i>=9)
		{
			cnumber[0]='1';cnumber[1]=i-10+49;//查ASCII码表后得到
			cnumber[2]='\0';
		}
		char str3[]={".bmp"};
		strcat(str1,cnumber);
		strcat(str1,str3);
		if(!Load_Bitmap_File(&map_yellow_level[i],str1))
		 return(0);
	}
	for(i=0;i<18;i++)
	{
	lpdds_yellow_level[i] = DDraw_Create_Surface(16,16,0,0);
	Scan_Image_Bitmap(&map_yellow_level[i],lpdds_yellow_level[i],16,16);
   if(!Unload_Bitmap_File(&map_yellow_level[i]))
		return(0);
	}

//////DAVINCI///////////////////////////////////////////////////////////
    
	if(!Load_Bitmap_File(&map_justmove[Up],"images\\tilemaster_up.bmp"))return (0);
	if(!Load_Bitmap_File(&map_justmove[Down],"images\\tilemaster_down.bmp"))return(0);
	if(!Load_Bitmap_File(&map_justmove[Left],"images\\tilemaster_left.bmp"))return(0);
	if(!Load_Bitmap_File(&map_justmove[Right],"images\\tilemaster_right.bmp"))return(0);
	if(!Load_Bitmap_File(&map_justthrow[Up][0],"images\\tilemasterthrow_up1.bmp"))return(0);
	if(!Load_Bitmap_File(&map_justthrow[Up][1],"images\\tilemasterthrow_up2.bmp"))return(0);
	if(!Load_Bitmap_File(&map_justthrow[Down][0],"images\\tilemasterthrow_down1.bmp"))return(0);
	if(!Load_Bitmap_File(&map_justthrow[Down][1],"images\\tilemasterthrow_down2.bmp"))return(0);
	if(!Load_Bitmap_File(&map_justthrow[Right][0],"images\\tilemasterthrow_right1.bmp"))return(0);
	if(!Load_Bitmap_File(&map_justthrow[Right][1],"images\\tilemasterthrow_right2.bmp"))return(0);
	if(!Load_Bitmap_File(&map_justthrow[Left][0],"images\\tilemasterthrow_left1.bmp")) return(0);
	if(!Load_Bitmap_File(&map_justthrow[Left][1],"images\\tilemasterthrow_left2.bmp"))return(0);
	if(!Load_Bitmap_File(&map_personshadow,"images\\tilemaster_shadow.BMP"))return(0);
	if(!Load_Bitmap_File(&map_aimcursorblue,"images\\aim_cursor_blue.BMP"))return(0);
	if(!Load_Bitmap_File(&map_aimcursorred,"images\\aim_cursor_red.BMP"))return(0);
	//if(!Load_Bitmap_File(&map_levels_nil,"images\\red_level\\nil.BMP"))return(0);
	if(!Load_Bitmap_File(&map_tileblue[0],"images\\tileblue01.BMP"))return(0);
	if(!Load_Bitmap_File(&map_tileblue[1],"images\\tileblue02.BMP"))return(0);
	if(!Load_Bitmap_File(&map_tileblue[2],"images\\tileblue03.BMP"))return(0);
	if(!Load_Bitmap_File(&map_tileblue[3],"images\\tileblue04.BMP"))return(0);
	if(!Load_Bitmap_File(&map_tileblue[4],"images\\tileblue05.BMP"))return(0);
	if(!Load_Bitmap_File(&map_tilered[0],"images\\tilered01.BMP"))return(0);
	if(!Load_Bitmap_File(&map_tilered[1],"images\\tilered02.BMP"))return(0);
	if(!Load_Bitmap_File(&map_tilered[2],"images\\tilered03.BMP"))return(0);
	if(!Load_Bitmap_File(&map_tilered[3],"images\\tilered04.BMP"))return(0);
	if(!Load_Bitmap_File(&map_tilered[4],"images\\tilered05.BMP"))return(0);
	if(!Load_Bitmap_File(&map_tiledarkblue[0],"images\\tiledarkblue01.BMP"))return(0);
	if(!Load_Bitmap_File(&map_tiledarkblue[1],"images\\tiledarkblue02.BMP"))return(0);
	if(!Load_Bitmap_File(&map_tiledarkblue[2],"images\\tiledarkblue03.BMP"))return(0);
	if(!Load_Bitmap_File(&map_tiledarkblue[3],"images\\tiledarkblue04.BMP"))return(0);
	if(!Load_Bitmap_File(&map_tiledarkblue[4],"images\\tiledarkblue05.BMP"))return(0);
	if(!Load_Bitmap_File(&map_tiletrail_down,"images\\tiletrail_down.BMP"))return(0);
	if(!Load_Bitmap_File(&map_tiletrail_up,"images\\tiletrail_up.BMP"))return(0);
	if(!Load_Bitmap_File(&map_tiletrail_left,"images\\tiletrail_left.BMP"))return(0);
	if(!Load_Bitmap_File(&map_tiletrail_right,"images\\tiletrail_right.BMP"))return(0);
    if(!Load_Bitmap_File(&map_tile_want_tile,"images\\tileback_wanttile.BMP"))return(0);
	if(!Load_Bitmap_File(&map_aim_arrow[Up],"images\\aim_arrow_to_up.bmp"))return (0);
	if(!Load_Bitmap_File(&map_aim_arrow[Left],"images\\aim_arrow_to_left.bmp"))return (0);
	if(!Load_Bitmap_File(&map_aim_arrow[Down],"images\\aim_arrow_to_down.bmp"))return (0);
	if(!Load_Bitmap_File(&map_aim_arrow[Right],"images\\aim_arrow_to_right.bmp"))return (0);


////temple的创建//////////////////////////////////////////////////////////////////////////
 //1
	if(!Load_Bitmap_File(&map_templebacchus1,"images\\templebacchus1.bmp"))
		return(0);
	lpdds_templebacchus[0] = DDraw_Create_Surface(108,144,0,1);
	Scan_Image_Bitmap(&map_templebacchus1,lpdds_templebacchus[0],108,144);
   if(!Unload_Bitmap_File(&map_templebacchus1))
	return(0);    
 //
    if(!Load_Bitmap_File(&map_templebacchus2,"images\\templebacchus2.bmp"))
		return(0);
	lpdds_templebacchus[1] = DDraw_Create_Surface(108,144,0,1);
	Scan_Image_Bitmap(&map_templebacchus2,lpdds_templebacchus[1],108,144);
   if(!Unload_Bitmap_File(&map_templebacchus2))
		return(0);   
//2
   	if(!Load_Bitmap_File(&map_templecupid1,"images\\templecupid1.bmp"))
		return(0);
	lpdds_templecupid[0] = DDraw_Create_Surface(128,100,0,1);
	Scan_Image_Bitmap(&map_templecupid1,lpdds_templecupid[0],128,100);
   if(!Unload_Bitmap_File(&map_templecupid1))
	return(0);  

   //
if(!Load_Bitmap_File(&map_templecupid2,"images\\templecupid2.bmp"))
		return(0);
	lpdds_templecupid[1] = DDraw_Create_Surface(128,100,0,1);
	Scan_Image_Bitmap(&map_templecupid2,lpdds_templecupid[1],128,100);
   if(!Unload_Bitmap_File(&map_templecupid2))
	return(0);  
//3
    if(!Load_Bitmap_File(&map_templediane1,"images\\templediane1.bmp"))
		return(0);
	lpdds_templediane[0] = DDraw_Create_Surface(128,100,0,1);
	Scan_Image_Bitmap(&map_templediane1,lpdds_templediane[0],128,100);
   if(!Unload_Bitmap_File(&map_templediane1))
	return(0);  

   //
  if(!Load_Bitmap_File(&map_templediane2,"images\\templediane2.bmp"))
		return(0);
	lpdds_templediane[1] = DDraw_Create_Surface(128,100,0,1);
	Scan_Image_Bitmap(&map_templediane2,lpdds_templediane[1],128,100);
   if(!Unload_Bitmap_File(&map_templediane2))
	return(0);  
//4
    if(!Load_Bitmap_File(&map_templeflora1,"images\\templeflora1.bmp"))
	 return(0);
	lpdds_templeflora[0] = DDraw_Create_Surface(132,116,0,1);
	Scan_Image_Bitmap(&map_templeflora1,lpdds_templeflora[0],132,116);
   if(!Unload_Bitmap_File(&map_templeflora1))
	return(0); 
   //
   if(!Load_Bitmap_File(&map_templeflora2,"images\\templeflora2.bmp"))
	 return(0);
	lpdds_templeflora[1] = DDraw_Create_Surface(132,116,0,1);
	Scan_Image_Bitmap(&map_templeflora2,lpdds_templeflora[1],132,116);
   if(!Unload_Bitmap_File(&map_templeflora2))
	return(0); 
//5
   if(!Load_Bitmap_File(&map_templejupiter1,"images\\templejupiter1.bmp"))
	 return(0);
	lpdds_templejupiter[0] = DDraw_Create_Surface(184,104,0,1);
	Scan_Image_Bitmap(&map_templejupiter1,lpdds_templejupiter[0],184,104);
   if(!Unload_Bitmap_File(&map_templejupiter1))
	return(0); 
   //
      if(!Load_Bitmap_File(&map_templejupiter2,"images\\templejupiter2.bmp"))
	 return(0);
	lpdds_templejupiter[1] = DDraw_Create_Surface(184,104,0,1);
	Scan_Image_Bitmap(&map_templejupiter2,lpdds_templejupiter[1],184,104);
   if(!Unload_Bitmap_File(&map_templejupiter2))
	return(0); 
   


////开场时候HAIR动画的创建//////////////////////////////////////////////////////////////////////////
    if(!Load_Bitmap_File(&map_hair[0],"images\\hair1.bmp")) return(0);
    if(!Load_Bitmap_File(&map_hair[1],"images\\hair2.bmp")) return(0);
	if(!Load_Bitmap_File(&map_hair[2],"images\\hair3.bmp")) return(0);
	lpdds_hair[0]=DDraw_Create_Surface(128,128,0,1);
	lpdds_hair[1]=DDraw_Create_Surface(128,128,0,1);
	lpdds_hair[2]=DDraw_Create_Surface(128,128,0,1);

    for(i=0;i<3;i++)
	{
		Scan_Image_Bitmap(&map_hair[i],lpdds_hair[i],128,128);
		if(!Unload_Bitmap_File(&map_hair[i]))
			return(0);
	}
////开场时候SMILE动画的创建//////////////////////////////////////////////////////////////////////////
	if(!Load_Bitmap_File(&map_smile,"images\\smile.bmp"))return(0);
	lpdds_smile=DDraw_Create_Surface(72,76,0,0);
	Scan_Image_Bitmap(&map_smile,lpdds_smile,72,76);
	if(!Unload_Bitmap_File(&map_smile))
			return(0);
////神秘岛上火山动画的创建//////////////////////////////////////////////////////////////////////////
    if(!Load_Bitmap_File(&map_islandmapsmoke[0],"images\\islandmapsmoke1.bmp")) return(0);
    if(!Load_Bitmap_File(&map_islandmapsmoke[1],"images\\islandmapsmoke2.bmp")) return(0);
	if(!Load_Bitmap_File(&map_islandmapsmoke[2],"images\\islandmapsmoke3.bmp")) return(0);
	
    for(i=0;i<3;i++)
	{
		lpdds_islandmapsomke[i]=DDraw_Create_Surface(160,88,0,1);
		Scan_Image_Bitmap(&map_islandmapsmoke[i],lpdds_islandmapsomke[i],160,88);
		if(!Unload_Bitmap_File(&map_islandmapsmoke[i]))
			return(0);
	}



// return success or failure or your own return code here
return(1);

} // end Game_Init

//////////////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////

int Game_Shutdown(void *parms = NULL, int num_parms = 0)
{
// this is called after the game is exited and the main event
// loop while is exited, do all you cleanup and shutdown here

// kill all the surfaces
// now the primary surface

	if(lpddsback)
	{
	lpddsback->Release();
	lpddsback=NULL;
	}

	if (lpddsprimary)
   {
   lpddsprimary->Release();
   lpddsprimary = NULL;
   } // end if
if(lpdds_backtitle)
{
	lpdds_backtitle->Release();
	lpdds_backtitle=NULL;
}
if(lpdds_playfield)
{
	lpdds_playfield->Release();
	lpdds_playfield=NULL;
}
if(lpdds_gameselect)
{
	lpdds_gameselect->Release();
	lpdds_gameselect=NULL;
}
if(lpdds_island)
{
	lpdds_island->Release();
	lpdds_island=NULL;
}
if(lpdds_islandsky)
{
	lpdds_islandsky->Release();
	lpdds_islandsky=NULL;
}
if(lpdds_menu_play)
{
	lpdds_menu_play->Release();
	lpdds_menu_play=NULL;
}
if(lpdds_menu_option)
{
	lpdds_menu_option->Release();
	lpdds_menu_option=NULL;
}
if(lpdds_menu_quit)
{
	lpdds_menu_quit->Release();
	lpdds_menu_quit=NULL;
}
if(lpdds_quit)
{
	lpdds_quit->Release();
	lpdds_quit=NULL;
}
for(int i=0;i<2;i++)
	if(lpdds_menu_backtotemple[i])
	{
		lpdds_menu_backtotemple[i]->Release();
		lpdds_menu_backtotemple[i]=NULL;
	}
for(i=0;i<2;i++)
	if(lpdds_menu_backtoisland[i])
	{
		lpdds_menu_backtoisland[i]->Release();
		lpdds_menu_backtoisland[i]=NULL;
	}
for(i=0;i<3;i++)
{
	if(lpdds_menu_backtomainmenu[i])
	{
		lpdds_menu_backtomainmenu[i]->Release();
		lpdds_menu_backtomainmenu[i]=NULL;
	}
	if(lpdds_hair[i])
	{
		lpdds_hair[i]->Release();
		lpdds_hair[i]=NULL;
	}
	if(lpdds_islandmapsomke[i])
	{
		lpdds_islandmapsomke[i]->Release();
		lpdds_islandmapsomke[i]=NULL;
	}
	
}
for(i=0;i<13;i++)
{
	if(lpdds_red_level[i])
	{
		lpdds_red_level[i]->Release();
		lpdds_red_level[i]=NULL;
	}
}
for(i=0;i<15;i++)
{
	if(lpdds_purple_level[i])
	{
		lpdds_purple_level[i]->Release();
		lpdds_purple_level[i]=NULL;
	}
}
for(i=0;i<13;i++)
{
	if(lpdds_blue_level[i])
	{
		lpdds_blue_level[i]->Release();
		lpdds_blue_level[i]=NULL;
	}
}

if(lpdds_black)
{
	lpdds_black->Release() ;
	lpdds_black=NULL;
}
if(lpdds_smile)
{
	lpdds_smile->Release();
	lpdds_smile=NULL;
}
if(lpdds_cursor_pointer)
{ 
	lpdds_cursor_pointer->Release();
	lpdds_cursor_pointer=NULL;
}
// now blow away the IDirectDraw4 interface
if (lpdd)
   {
   lpdd->Release();
   lpdd = NULL;
   } // end if
// release the directsoundobject
if (lpds!=NULL)
   lpds->Release();
//声音的RELEASE
/*if (sound_fx[sound_menu_mouseover].dsbuffer)
   sound_fx[sound_id].dsbuffer->Release();*/

// return success or failure or your own return code here
return(1);

} // end Game_Shutdown

// WINMAIN ////////////////////////////////////////////////

int WINAPI WinMain(	HINSTANCE hinstance,
					HINSTANCE hprevinstance,
								LPSTR lpcmdline,
					int ncmdshow)
{

WNDCLASSEX winclass; // this will hold the class we create
HWND	   hwnd;	 // generic window handle
MSG		   msg;		 // generic message
HDC        hdc;      // graphics device context

// first fill in the window class stucture
winclass.cbSize         = sizeof(WNDCLASSEX);
winclass.style			= CS_DBLCLKS | CS_OWNDC | 
                          CS_HREDRAW | CS_VREDRAW;
winclass.lpfnWndProc	= WindowProc;
winclass.cbClsExtra		= 0;
winclass.cbWndExtra		= 0;
winclass.hInstance		= hinstance;
winclass.hIcon			= LoadIcon(hinstance,MAKEINTRESOURCE(huangicon));
winclass.hCursor		= LoadCursor(hinstance,MAKEINTRESOURCE(huangcursor));
winclass.hbrBackground	= (HBRUSH)GetStockObject(BLACK_BRUSH);
winclass.lpszMenuName	= NULL;
winclass.lpszClassName	= WINDOW_CLASS_NAME;
winclass.hIconSm        = LoadIcon(hinstance,MAKEINTRESOURCE(huangicon));


// save hinstance in global
main_hinstance = hinstance;

// register the window class
if (!RegisterClassEx(&winclass))
	return(0);

// create the window
if (!(hwnd = CreateWindowEx(NULL,                  // extended style
                            WINDOW_CLASS_NAME,     // class
						    "达芬奇密码之神秘岛", // tile
						    WS_POPUP | WS_VISIBLE,
					 	    0,0,	  // initial x,y
						    SCREEN_WIDTH,SCREEN_HEIGHT,  // initial width, height
						    NULL,	  // handle to parent 
						    NULL,	  // handle to menu
						    hinstance,// instance of this application
						    NULL)))	// extra creation parms
return(0);

// save main window handle
main_window_handle = hwnd;
ShowCursor(FALSE);
// initialize game here
Game_Init();
DInput_Init();
Dsound_Init();
CPerson DaVinci;//
// enter main event loop
while(TRUE)
	{
    // test if there is a message in queue, if so get it
	if (PeekMessage(&msg,NULL,0,0,PM_REMOVE))
	   { 
	   // test if this is a quit
       if (msg.message == WM_QUIT)
           break;
	
	   // translate any accelerator keys
	   TranslateMessage(&msg);

	   // send the message to the window proc
	   DispatchMessage(&msg);
	   } // end if

       // main game processing goes here
       Game_Main(DaVinci);//
       
	} // end while
DaVinci.~CPerson();//
// closedown game here
Game_Shutdown();

// return to Windows like this
return(msg.wParam);

} // end WinMain

///////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////

void _Gameselect()
{
	////Wave////
if(backmusic_option==SOUND_NULL)
{
	

    if((backmusic_option = DSound_Load_WAV("wave//main_music.wav"))!=-1)
	{
		sound_fx[backmusic_option].dsbuffer->SetVolume(-100);
        sound_fx[backmusic_option].dsbuffer->Play(0,0,DSBPLAY_LOOPING);
	}
	backmusic_option=SOUND_PLAYING;
}/**/

	//画背景图
	
    DDraw_Draw_Surface(lpdds_gameselect,0,0,SCREEN_WIDTH,SCREEN_HEIGHT, lpddsback,0);
	DDraw_Draw_Surface(lpdds_backtitle,0,0,SCREEN_WIDTH,SCREEN_HEIGHT,lpddsback,1);
	DDraw_Draw_Surface(lpdds_menu_help[0],425,233,128,84,lpddsback,1); 
	DDraw_Draw_Surface(lpdds_menu_aboutus[0],404,340,144,44,lpddsback,1);
	//画头发的动画
	static int index_of_hair=0;
	int temp_index_of_hair;
	temp_index_of_hair=floor(index_of_hair/5);
	if(temp_index_of_hair>2) temp_index_of_hair=4-temp_index_of_hair;
	DDraw_Draw_Surface(lpdds_hair[temp_index_of_hair],169,210,128,128,lpddsback,1);
    index_of_hair++;
	if(index_of_hair==20)index_of_hair=0;
	
	//检测鼠标，并做进一步的操作
	if(mouse_x>=400&&mouse_x<=500&&mouse_y>=80&&mouse_y<=194)//准备PLAY
	{
		if(sound_menu_mouseover==SOUND_NULL)
		{
			if((sound_menu_mouseover = DSound_Load_WAV("wave\\UI Menu Mouseover 02.wav"))!=-1)
                sound_fx[sound_menu_mouseover].dsbuffer->Play(0,0,0);
			sound_menu_mouseover=SOUND_PLAYING;
		}
		DDraw_Draw_Surface(lpdds_menu_play,375,65,116,120,lpddsback,1);//65
		DDraw_Draw_Surface(lpdds_smile,477,18,72,76,lpddsback,1);
		static bool switch_of_index_of_slipstate=FALSE;//用于延时切换
		static int index_of_flipstate=0;//用于延时切换
		if(mouse_state.rgbButtons[0] & 0x80) 
		{
			switch_of_index_of_slipstate=TRUE;
			if(sound_menu_click1==SOUND_NULL)
			{
			if(( sound_menu_click1= DSound_Load_WAV("wave\\UI Menu Click 01c.wav"))!=-1)
                sound_fx[sound_menu_click1].dsbuffer->Play(0,0,0);
			sound_menu_click1=SOUND_PLAYING;
			}////
		}//
		else sound_menu_click1=SOUND_NULL;
		if(index_of_flipstate==10) //看看时间是不是够了，如果够了就切换
		{gGame_state=Island;index_of_flipstate=0;switch_of_index_of_slipstate=FALSE;}
		/////
		if(switch_of_index_of_slipstate)index_of_flipstate++;
	}
	else if(mouse_x>=425&&mouse_x<=536&&mouse_y>=236&&mouse_y<=320)//准备打开Help选项
	{
		if(sound_menu_mouseover==SOUND_NULL)
		{
			if((sound_menu_mouseover = DSound_Load_WAV("wave\\UI Menu Mouseover 02.wav"))!=-1)
                sound_fx[sound_menu_mouseover].dsbuffer->Play(0,0,0);
			sound_menu_mouseover=SOUND_PLAYING;
		}
		DDraw_Draw_Surface(lpdds_menu_help[1],425,233,128,84,lpddsback,1);//65
		static bool switch_of_index_of_slipstate=FALSE;//用于延时切换
		static int index_of_flipstate=0;//用于延时切换
		if(mouse_state.rgbButtons[0] & 0x80) 
		{
			if(sound_menu_click1==SOUND_NULL)
			{
			if(( sound_menu_click1= DSound_Load_WAV("wave\\UI Menu Click 01c.wav"))!=-1)
                sound_fx[sound_menu_click1].dsbuffer->Play(0,0,0);
			sound_menu_click1=SOUND_PLAYING;
			}////
			switch_of_index_of_slipstate=TRUE;
		}
		else sound_menu_click1=SOUND_NULL;
		if(switch_of_index_of_slipstate) index_of_flipstate++;
		if(index_of_flipstate==10) 
		{
			index_of_flipstate=0;
			switch_of_index_of_slipstate=FALSE;
			gGame_state=Help;
		}
			
	}/**/
	else if(mouse_x>=404&&mouse_x<=548&&mouse_y>=340&&mouse_y<=388)//准备打开ABOUT US选项
	{
		if(sound_menu_mouseover==SOUND_NULL)
		{
			if((sound_menu_mouseover = DSound_Load_WAV("wave\\UI Menu Mouseover 02.wav"))!=-1)
                sound_fx[sound_menu_mouseover].dsbuffer->Play(0,0,0);
			sound_menu_mouseover=SOUND_PLAYING;
		}
	DDraw_Draw_Surface(lpdds_menu_aboutus[1],404,340,144,44,lpddsback,1);
		static bool switch_of_index_of_slipstate=FALSE;//用于延时切换
		static int index_of_flipstate=0;//用于延时切换
		if(mouse_state.rgbButtons[0] & 0x80) 
		{
			if(sound_menu_click1==SOUND_NULL)
			{
			if(( sound_menu_click1= DSound_Load_WAV("wave\\UI Menu Click 01c.wav"))!=-1)
                sound_fx[sound_menu_click1].dsbuffer->Play(0,0,0);
			sound_menu_click1=SOUND_PLAYING;
			}////
			switch_of_index_of_slipstate=TRUE;
		}
		else sound_menu_click1=SOUND_NULL;
		if(switch_of_index_of_slipstate) index_of_flipstate++;
		if(index_of_flipstate==10) 
		{
			index_of_flipstate=0;
			switch_of_index_of_slipstate=FALSE;
			gGame_state=AboutUs;
		}
			
	}/**/
	else if(mouse_x>=405&&mouse_x<=513&&mouse_y>=402&&mouse_y<=442)//准备打开QUIT选项
	{
		if(sound_menu_mouseover==SOUND_NULL)
		{
			if((sound_menu_mouseover = DSound_Load_WAV("wave\\UI Menu Mouseover 02.wav"))!=-1)
                sound_fx[sound_menu_mouseover].dsbuffer->Play(0,0,0);
			sound_menu_mouseover=SOUND_PLAYING;
		}
		DDraw_Draw_Surface(lpdds_menu_quit,404,399,108,40,lpddsback,1);
        if(mouse_state.rgbButtons[0] & 0x80)
		{
			if(sound_menu_click1==SOUND_NULL)
			{
			if(( sound_menu_click1= DSound_Load_WAV("wave\\UI Menu Click 01c.wav"))!=-1)
                sound_fx[sound_menu_click1].dsbuffer->Play(0,0,0);
			sound_menu_click1=SOUND_PLAYING;
			}////
			gGame_state=Quit;
		}
		else sound_menu_click1=SOUND_NULL;
	}
	else sound_menu_mouseover=SOUND_NULL;
}//Gameselect结束

void _Island(CPerson&DaVinci)
{
	//画背景图
    DDraw_Draw_Surface(lpdds_islandsky,0,0,640,120, lpddsback,0);
	DDraw_Draw_Surface(lpdds_island,0,119,640,360, lpddsback,0);
	DDraw_Draw_Surface(lpdds_menu_backtomainmenu[0],20,20,116,56,lpddsback,1);
	////
	DDraw_Draw_Surface(lpdds_templebacchus[0],530,305,108,144,lpddsback,1);
	DDraw_Draw_Surface(lpdds_templecupid[0],217,173,128,100,lpddsback,1);
	DDraw_Draw_Surface(lpdds_templeflora[0],324,338,132,116,lpddsback,1);
	DDraw_Draw_Surface(lpdds_templejupiter[0],267,46,184,104,lpddsback,1);
	//海上的temple
	static bool switch_of_index_of_slipstate=FALSE;//用于延时切换
	static int index_of_flipstate=0;//用于延时切换
	if(mouse_x>530&&mouse_x<638&&mouse_y>305&&mouse_y<449)
	{
		DDraw_Draw_Surface(lpdds_templebacchus[1],530,305,108,144,lpddsback,1);
		if(mouse_state.rgbButtons[0] & 0x80) 
		{
			switch_of_index_of_slipstate=TRUE;
			//gGame_state=Temple_blue;
		}
		if(switch_of_index_of_slipstate)index_of_flipstate++;
		if(index_of_flipstate==8) 
		{
			index_of_flipstate=0;
			switch_of_index_of_slipstate=FALSE;
			gGame_state=Temple_blue;
		}
	}
	//templecupid
    else if(mouse_x>217&&mouse_x<350&&mouse_y>173&&mouse_y<273)
	{
		DDraw_Draw_Surface(lpdds_templecupid[1],217,173,128,100,lpddsback,1);
		if(mouse_state.rgbButtons[0] & 0x80) 
		{
			switch_of_index_of_slipstate=TRUE;
			//gGame_state=Temple_purple;
		}
		if(switch_of_index_of_slipstate)index_of_flipstate++;
		if(index_of_flipstate==8) 
		{
			index_of_flipstate=0;
			switch_of_index_of_slipstate=FALSE;
			gGame_state=Temple_purple;
		}
	}
	//flower
	else if(mouse_x>324&&mouse_x<456&&mouse_y>338&&mouse_y<454)
	{
		DDraw_Draw_Surface(lpdds_templeflora[1],324,338,132,116,lpddsback,1);
		if(mouse_state.rgbButtons[0] & 0x80) 
		{
			switch_of_index_of_slipstate=TRUE;
			//gGame_state=Temple_red;
		}
		if(switch_of_index_of_slipstate) index_of_flipstate++;
		if(index_of_flipstate==8) 
		{
			
			index_of_flipstate=0;
			switch_of_index_of_slipstate=FALSE;
			gGame_state=Temple_red;
		}
	}
	//jupiter
	else if(mouse_x>267&&mouse_x<447&&mouse_y>46&&mouse_y<150)
	{
		DDraw_Draw_Surface(lpdds_templejupiter[1],267,46,184,104,lpddsback,1);
		if(mouse_state.rgbButtons[0] & 0x80) 
		{
			switch_of_index_of_slipstate=TRUE;
			//gGame_state=Temple_yellow;
		}
		if(switch_of_index_of_slipstate)index_of_flipstate++;
		if(index_of_flipstate==8) 
		{
			index_of_flipstate=0;
			switch_of_index_of_slipstate=FALSE;
			gGame_state=Temple_yellow;
		}
	}
	else sound_island_mouseover=SOUND_NULL;
	
	//画火山的动画
	static int index_of_smoke=0;
	int temp_index;
	temp_index=floor(index_of_smoke/7);
	if(temp_index>2) temp_index=4-temp_index;
	DDraw_Draw_Surface(lpdds_islandmapsomke[temp_index],454,0,160,88,lpddsback,1);
    index_of_smoke++;
	if(index_of_smoke==28)index_of_smoke=0;
	//检测鼠标，并做进一步的操作
	if(mouse_x>=20&&mouse_x<=164&&mouse_y>=20&&mouse_y<=84)
	{
		DDraw_Draw_Surface(lpdds_menu_backtomainmenu[1],20,20,116,56,lpddsback,1);//65
		if(mouse_state.rgbButtons[0] & 0x80) 
		{
			if(sound_menu_click1==SOUND_NULL)
			{
			if(( sound_menu_click1= DSound_Load_WAV("wave\\UI Menu Click 01c.wav"))!=-1)
                sound_fx[sound_menu_click1].dsbuffer->Play(0,0,0);
			sound_menu_click1=SOUND_PLAYING;
			}////
		    gGame_state=Gameseletct;
		}
		else sound_menu_click1=SOUND_NULL;
	}
}

void _Playfield(CPerson &DaVinci)
{
	//////////////////////////////////////////////////////////////////////////
	//画个鼠标来看图上的各点位置
	DDraw_Fill_Surface(lpdds_black,0);
	//画背景图
	DDraw_Draw_Surface(lpdds_playfield,0,0, SCREEN_WIDTH,SCREEN_HEIGHT, lpddsback,0);
	DDraw_Draw_Surface(lpdds_menu_backtotemple[0],20,20,144,64,lpddsback,1);
	
	if(mouse_x>=20&&mouse_x<=164&&mouse_y>=20&&mouse_y<=84)
	{
		if(sound_menu_mouseover==SOUND_NULL)
		{
			if((sound_menu_mouseover = DSound_Load_WAV("wave\\UI Menu Mouseover 02.wav"))!=-1)
                sound_fx[sound_menu_mouseover].dsbuffer->Play(0,0,0);
			sound_menu_mouseover=SOUND_PLAYING;
		}
		DDraw_Draw_Surface(lpdds_menu_backtotemple[1],20,20,144,64,lpddsback,1);//65
		static bool switch_of_index_of_slipstate=FALSE;//用于延时切换
		static int index_of_flipstate=0;//用于延时切换
		if(mouse_state.rgbButtons[0] & 0x80) 
		{
			switch_of_index_of_slipstate=TRUE;
			if(sound_menu_click1==SOUND_NULL)
			{
			if(( sound_menu_click1= DSound_Load_WAV("wave\\UI Menu Click 01c.wav"))!=-1)
                sound_fx[sound_menu_click1].dsbuffer->Play(0,0,0);
			sound_menu_click1=SOUND_PLAYING;
			}////
			
		}
		else sound_menu_click1=SOUND_NULL;
		if(switch_of_index_of_slipstate==TRUE)index_of_flipstate++;
		if(index_of_flipstate==10)
		{
			switch_of_index_of_slipstate=FALSE;
			index_of_flipstate=0;
			gGame_state=Temple_temp;//回到从前
		}
	}
	else sound_menu_mouseover=SOUND_NULL;
	//DaVinci.ImHere();
	DaVinci.GetMouseState();
	DaVinci.DDrawChessBoard();
	DaVinci.Throwabrick();
	DaVinci.Move_to_other_side();
	DaVinci.Move();
	DaVinci.If_I_Win();//
	
	
	Draw_Text_GDI(buffer,20,20,RGB(255,0,0),lpdds_black);
	DDraw_Draw_Surface(lpdds_black,0,0,640,480,lpddsback,1);
}

void _Quit()
{
	DDraw_Draw_Surface(lpdds_gameselect,0,0,SCREEN_WIDTH,SCREEN_HEIGHT,lpddsback,0);
	DDraw_Draw_Surface(lpdds_backtitle,0,0,SCREEN_WIDTH,SCREEN_HEIGHT,lpddsback,1);
	DDraw_Draw_Surface(lpdds_menu_help[0],425,233,128,84,lpddsback,1); 
	DDraw_Draw_Surface(lpdds_quit,150,132,340,216,lpddsback,1);	
	if(mouse_x>200&&mouse_x<310&&mouse_y>285&&mouse_y<310)//看是否要选择退出
	{
		if(sound_menu_mouseover==SOUND_NULL)
		{
			if((sound_menu_mouseover = DSound_Load_WAV("wave\\UI Menu Mouseover 02.wav"))!=-1)
                sound_fx[sound_menu_mouseover].dsbuffer->Play(0,0,0);
			sound_menu_mouseover=SOUND_PLAYING;
		}
		if(mouse_state.rgbButtons[0] & 0x80)//退出
		{
			if(sound_menu_click1==SOUND_NULL)
			{
			if(( sound_menu_click1= DSound_Load_WAV("wave\\UI Menu Click 01c.wav"))!=-1)
                sound_fx[sound_menu_click1].dsbuffer->Play(0,0,0);
			sound_menu_click1=SOUND_PLAYING;
			}////
			PostMessage(main_window_handle,WM_CLOSE,0,0);//
			window_closed = 1;//
		}
		else sound_menu_click1=SOUND_NULL;
	}
	else if(mouse_x>326&&mouse_x<430&&mouse_y>285&&mouse_y<310)//不选择退出
	{
		if(sound_menu_mouseover==SOUND_NULL)
		{
			if((sound_menu_mouseover = DSound_Load_WAV("wave\\UI Menu Mouseover 02.wav"))!=-1)
                sound_fx[sound_menu_mouseover].dsbuffer->Play(0,0,0);
			sound_menu_mouseover=SOUND_PLAYING;
		}
		if(mouse_state.rgbButtons[0] &0x80)
		{
			gGame_state=Gameseletct;
			if(sound_menu_click1==SOUND_NULL)
			{
			if(( sound_menu_click1= DSound_Load_WAV("wave\\UI Menu Click 01c.wav"))!=-1)
                sound_fx[sound_menu_click1].dsbuffer->Play(0,0,0);
			sound_menu_click1=SOUND_PLAYING;
			}////
		}
		else sound_menu_click1=SOUND_NULL;
	}
	else sound_menu_mouseover=SOUND_NULL;
}
                                                             

void _Temple_red(CPerson &DaVinci)
{
	Temple_temp=Temple_red;
	DDraw_Fill_Surface(lpdds_black,0);
	DDraw_Draw_Surface(lpdds_temple_red,0,0,SCREEN_WIDTH,SCREEN_HEIGHT,lpddsback,0);
	static int Page=1;
	int index_x=-1;int index_y=-1;
	int index_of_map;
if(Page==1)
{
	
	for(int i=0;i<9;i++)
	{
	DDraw_Draw_Surface_Scaled(lpdds_red_level[i],225+(i%3)*110,85+(i/3)*110,16,16,110,110,lpddsback,0);
	DDraw_Draw_Surface(lpdds_slider_up,556,85,16,16,lpddsback,1);
	DDraw_Draw_Surface(lpdds_slider_down,556,399,16,16,lpddsback,1);
	}
	if(mouse_x>=225&&mouse_x<555&&mouse_y>=85&&mouse_y<=415)
	{
		index_x=floor((mouse_x-225)/110);
		index_y=floor((mouse_y-85)/110);
	}
	if(index_x>=0&&index_x<3&&index_y>=0&&index_y<3)
	{
		index_of_map=index_x+index_y*3;
		//准备读入文件
		char str1[30]={"red_level\\"};
		char cnumber[3];
		if(index_of_map<9) 
		{ 
			cnumber[0]=index_of_map+49;cnumber[1]='\0';
		}
		if(index_of_map>=9)
		{
			cnumber[0]='1';cnumber[1]=index_of_map-10+49;
			cnumber[2]='\0';
		}
		char str3[]={".txt"};
		strcat(str1,cnumber);
		strcat(str1,str3);
		static bool switch_of_index_of_slipstate=FALSE;//用于延时切换
		static int index_of_flipstate=0;//用于延时切换
		if(mouse_state.rgbButtons[0] & 0x80)
		{
			gLevel_map_temp=lpdds_red_level[index_of_map];
			switch_of_index_of_slipstate=TRUE;
			DaVinci.Read_a_file(str1);
		}
		if(switch_of_index_of_slipstate) 
		{
			index_of_flipstate++;
		}
		if(index_of_flipstate==7)
		{
			gGame_state=Playfield;
			index_of_flipstate=0;
			switch_of_index_of_slipstate=FALSE;
		}
	}
	if(mouse_x>556&&mouse_x<572&&mouse_y>399&&mouse_y<415)
		if(mouse_state.rgbButtons[0]&0x80)
		Page=2;
}
if(Page==2)
{
	for(int i=9;i<13;i++)
	{
	DDraw_Draw_Surface_Scaled(lpdds_red_level[i],225+(i%3)*110,85+(i/3-3)*110,16,16,110,110,lpddsback,0);
	DDraw_Draw_Surface(lpdds_slider_up,556,85,16,16,lpddsback,1);
	DDraw_Draw_Surface(lpdds_slider_down,556,399,16,16,lpddsback,1);
	}
	if(mouse_x>=225&&mouse_x<555&&mouse_y>=85&&mouse_y<=415)
	{
	
		index_x=floor((mouse_x-225)/110);
		index_y=floor((mouse_y-85)/110);
	}
	if(index_x>=0&&index_x<3&&index_y>=0&&index_y<3)
	{
		index_of_map=index_x+index_y*3+9;
		//准备读入文件
		char str1[30]={"red_level\\"};
		char cnumber[3];
		if(index_of_map<9) 
		{ 
			cnumber[0]=index_of_map+49;cnumber[1]='\0';
		}
		if(index_of_map>=9)
		{
			cnumber[0]='1';cnumber[1]=index_of_map-10+49;
			cnumber[2]='\0';
		}
		char str3[]={".txt"};
		strcat(str1,cnumber);
		strcat(str1,str3);
		static bool switch_of_index_of_slipstate=FALSE;//用于延时切换
		static int index_of_flipstate=0;//用于延时切换
		if((mouse_state.rgbButtons[0] & 0x80)&&index_of_map<13)
		{
			gLevel_map_temp=lpdds_red_level[index_of_map];
			switch_of_index_of_slipstate=TRUE;
			DaVinci.Read_a_file(str1);
		}
		if(switch_of_index_of_slipstate) 
		{
			index_of_flipstate++;
		}
		if(index_of_flipstate==7)
		{
			gGame_state=Playfield;
			index_of_flipstate=0;
			switch_of_index_of_slipstate=FALSE;
		}
	}
	if(mouse_x>556&&mouse_x<572&&mouse_y>85&&mouse_y<101)
		if(mouse_state.rgbButtons[0]&0x80)
		Page=1;
}

	//准备返回
	DDraw_Draw_Surface(lpdds_menu_backtoisland[0],20,20,136,60,lpddsback,1);
	static bool switch_of_back_to_island=FALSE;
	static int index_of_back_to_island=0;
	if(mouse_x>20&&mouse_x<156&&mouse_y>20&&mouse_y<80)
	{

		DDraw_Draw_Surface(lpdds_menu_backtoisland[1],20,20,136,60,lpddsback,1);
		if(mouse_state.rgbButtons[0]&0x80)
		{
			if(sound_menu_click1==SOUND_NULL)
			{
			if(( sound_menu_click1= DSound_Load_WAV("wave\\UI Menu Click 01c.wav"))!=-1)
                sound_fx[sound_menu_click1].dsbuffer->Play(0,0,0);
			sound_menu_click1=SOUND_PLAYING;
			}////
			switch_of_back_to_island=TRUE;
		}
		else sound_menu_click1=SOUND_NULL;
	}
	if(switch_of_back_to_island)index_of_back_to_island++;
	if(index_of_back_to_island==8)
	{

		gGame_state=Island;
		switch_of_back_to_island=FALSE;
		index_of_back_to_island=0;
	}
}


void _Temple_yellow(CPerson &DaVinci)
{
	Temple_temp=Temple_yellow;
	DDraw_Fill_Surface(lpdds_black,0);
	DDraw_Draw_Surface(lpdds_temple_yellow,0,0,SCREEN_WIDTH,SCREEN_HEIGHT,lpddsback,0);
	static int Page=1;
	int index_x=-1;int index_y=-1;
	int index_of_map;
if(Page==1)
{
	
	for(int i=0;i<9;i++)
	{
	DDraw_Draw_Surface_Scaled(lpdds_yellow_level[i],225+(i%3)*110,85+(i/3)*110,16,16,110,110,lpddsback,0);
	DDraw_Draw_Surface(lpdds_slider_up,556,85,16,16,lpddsback,1);
	DDraw_Draw_Surface(lpdds_slider_down,556,399,16,16,lpddsback,1);
	}
	if(mouse_x>=225&&mouse_x<555&&mouse_y>=85&&mouse_y<=415)
	{
		index_x=floor((mouse_x-225)/110);
		index_y=floor((mouse_y-85)/110);
	}
	if(index_x>=0&&index_x<3&&index_y>=0&&index_y<3)
	{
		index_of_map=index_x+index_y*3;
		//准备读入文件
		char str1[30]={"yellow_level\\"};
		char cnumber[3];
		if(index_of_map<9) 
		{ 
			cnumber[0]=index_of_map+49;cnumber[1]='\0';
		}
		if(index_of_map>=9)
		{
			cnumber[0]='1';cnumber[1]=index_of_map-10+49;
			cnumber[2]='\0';
		}
		char str3[]={".txt"};
		strcat(str1,cnumber);
		strcat(str1,str3);
		static bool switch_of_index_of_slipstate=FALSE;//用于延时切换
		static int index_of_flipstate=0;//用于延时切换
		if(mouse_state.rgbButtons[0] & 0x80)
		{
			gLevel_map_temp=lpdds_yellow_level[index_of_map];
			switch_of_index_of_slipstate=TRUE;
			DaVinci.Read_a_file(str1);
		}
		if(switch_of_index_of_slipstate) 
		{
			index_of_flipstate++;
		}
		if(index_of_flipstate==7)
		{
			gGame_state=Playfield;
			index_of_flipstate=0;
			switch_of_index_of_slipstate=FALSE;
		}
	}
	if(mouse_x>556&&mouse_x<572&&mouse_y>399&&mouse_y<415)
		if(mouse_state.rgbButtons[0]&0x80)
		Page=2;
}
if(Page==2)
{
	for(int i=9;i<14;i++)
	{
	DDraw_Draw_Surface_Scaled(lpdds_yellow_level[i],225+(i%3)*110,85+(i/3-3)*110,16,16,110,110,lpddsback,0);
	DDraw_Draw_Surface(lpdds_slider_up,556,85,16,16,lpddsback,1);
	DDraw_Draw_Surface(lpdds_slider_down,556,399,16,16,lpddsback,1);
	}
	if(mouse_x>=225&&mouse_x<555&&mouse_y>=85&&mouse_y<=415)
	{
	
		index_x=floor((mouse_x-225)/110);
		index_y=floor((mouse_y-85)/110);
	}
	if(index_x>=0&&index_x<3&&index_y>=0&&index_y<3)
	{
		index_of_map=index_x+index_y*3+9;
		//准备读入文件
		char str1[30]={"yellow_level\\"};
		char cnumber[3];
		if(index_of_map<9) 
		{ 
			cnumber[0]=index_of_map+49;cnumber[1]='\0';
		}
		if(index_of_map>=9)
		{
			cnumber[0]='1';cnumber[1]=index_of_map-10+49;
			cnumber[2]='\0';
		}
		char str3[]={".txt"};
		strcat(str1,cnumber);
		strcat(str1,str3);
		static bool switch_of_index_of_slipstate=FALSE;//用于延时切换
		static int index_of_flipstate=0;//用于延时切换
		if((mouse_state.rgbButtons[0] & 0x80)&&index_of_map<14)
		{
			gLevel_map_temp=lpdds_yellow_level[index_of_map];
			switch_of_index_of_slipstate=TRUE;
			DaVinci.Read_a_file(str1);
		}
		if(switch_of_index_of_slipstate) 
		{
			index_of_flipstate++;
		}
		if(index_of_flipstate==7)
		{
			gGame_state=Playfield;
			index_of_flipstate=0;
			switch_of_index_of_slipstate=FALSE;
		}
	}
	if(mouse_x>556&&mouse_x<572&&mouse_y>85&&mouse_y<101)
		if(mouse_state.rgbButtons[0]&0x80)
		Page=1;
}

	//准备返回
	DDraw_Draw_Surface(lpdds_menu_backtoisland[0],20,20,136,60,lpddsback,1);
	static bool switch_of_back_to_island=FALSE;
	static int index_of_back_to_island=0;
	if(mouse_x>20&&mouse_x<156&&mouse_y>20&&mouse_y<80)
	{

		DDraw_Draw_Surface(lpdds_menu_backtoisland[1],20,20,136,60,lpddsback,1);
		if(mouse_state.rgbButtons[0]&0x80)
		{
			if(sound_menu_click1==SOUND_NULL)
			{
			if(( sound_menu_click1= DSound_Load_WAV("wave\\UI Menu Click 01c.wav"))!=-1)
                sound_fx[sound_menu_click1].dsbuffer->Play(0,0,0);
			sound_menu_click1=SOUND_PLAYING;
			}////
			switch_of_back_to_island=TRUE;
		}
		else sound_menu_click1=SOUND_NULL;
	}
	if(switch_of_back_to_island)index_of_back_to_island++;
	if(index_of_back_to_island==8)
	{

		gGame_state=Island;
		switch_of_back_to_island=FALSE;
		index_of_back_to_island=0;
	}
}


void _Temple_purple(CPerson &DaVinci)
{
	Temple_temp=Temple_purple;
	DDraw_Fill_Surface(lpdds_black,0);
	DDraw_Draw_Surface(lpdds_temple_purple,0,0,SCREEN_WIDTH,SCREEN_HEIGHT,lpddsback,0);
	static int Page=1;
	int index_x=-1;int index_y=-1;
	int index_of_map;
if(Page==1)
{
	
	for(int i=0;i<9;i++)
	{
	DDraw_Draw_Surface_Scaled(lpdds_purple_level[i],225+(i%3)*110,85+(i/3)*110,16,16,110,110,lpddsback,0);
	DDraw_Draw_Surface(lpdds_slider_up,556,85,16,16,lpddsback,1);
	DDraw_Draw_Surface(lpdds_slider_down,556,399,16,16,lpddsback,1);
	}
	if(mouse_x>=225&&mouse_x<555&&mouse_y>=85&&mouse_y<=415)
	{
		index_x=floor((mouse_x-225)/110);
		index_y=floor((mouse_y-85)/110);
	}
	if(index_x>=0&&index_x<3&&index_y>=0&&index_y<3)
	{
		index_of_map=index_x+index_y*3;
		//准备读入文件
		char str1[30]={"purple_level\\"};
		char cnumber[3];
		if(index_of_map<9) 
		{ 
			cnumber[0]=index_of_map+49;cnumber[1]='\0';
		}
		if(index_of_map>=9)
		{
			cnumber[0]='1';cnumber[1]=index_of_map-10+49;
			cnumber[2]='\0';
		}
		char str3[]={".txt"};
		strcat(str1,cnumber);
		strcat(str1,str3);
		static bool switch_of_index_of_slipstate=FALSE;//用于延时切换
		static int index_of_flipstate=0;//用于延时切换
		if(mouse_state.rgbButtons[0] & 0x80)
		{
			gLevel_map_temp=lpdds_purple_level[index_of_map];
			switch_of_index_of_slipstate=TRUE;
			DaVinci.Read_a_file(str1);
		}
		if(switch_of_index_of_slipstate) 
		{
			index_of_flipstate++;
		}
		if(index_of_flipstate==7)
		{
			gGame_state=Playfield;
			index_of_flipstate=0;
			switch_of_index_of_slipstate=FALSE;
		}
	}
	if(mouse_x>556&&mouse_x<572&&mouse_y>399&&mouse_y<415)
		if(mouse_state.rgbButtons[0]&0x80)
		Page=2;
}
if(Page==2)
{
	for(int i=9;i<15;i++)
	{
	DDraw_Draw_Surface_Scaled(lpdds_purple_level[i],225+(i%3)*110,85+(i/3-3)*110,16,16,110,110,lpddsback,0);
	DDraw_Draw_Surface(lpdds_slider_up,556,85,16,16,lpddsback,1);
	DDraw_Draw_Surface(lpdds_slider_down,556,399,16,16,lpddsback,1);
	}
	if(mouse_x>=225&&mouse_x<555&&mouse_y>=85&&mouse_y<=415)
	{
	
		index_x=floor((mouse_x-225)/110);
		index_y=floor((mouse_y-85)/110);
	}
	if(index_x>=0&&index_x<3&&index_y>=0&&index_y<3)
	{
		index_of_map=index_x+index_y*3+9;
		//准备读入文件
		char str1[30]={"purple_level\\"};
		char cnumber[3];
		if(index_of_map<9) 
		{ 
			cnumber[0]=index_of_map+49;cnumber[1]='\0';
		}
		if(index_of_map>=9)
		{
			cnumber[0]='1';cnumber[1]=index_of_map-10+49;
			cnumber[2]='\0';
		}
		char str3[]={".txt"};
		strcat(str1,cnumber);
		strcat(str1,str3);
		static bool switch_of_index_of_slipstate=FALSE;//用于延时切换
		static int index_of_flipstate=0;//用于延时切换
		if((mouse_state.rgbButtons[0] & 0x80)&&index_of_map<15)
		{
			gLevel_map_temp=lpdds_purple_level[index_of_map];
			switch_of_index_of_slipstate=TRUE;
			DaVinci.Read_a_file(str1);
		}
		if(switch_of_index_of_slipstate) 
		{
			index_of_flipstate++;
		}
		if(index_of_flipstate==7)
		{
			gGame_state=Playfield;
			index_of_flipstate=0;
			switch_of_index_of_slipstate=FALSE;
		}
	}
	if(mouse_x>556&&mouse_x<572&&mouse_y>85&&mouse_y<101)
		if(mouse_state.rgbButtons[0]&0x80)
		Page=1;
}

	//准备返回
	DDraw_Draw_Surface(lpdds_menu_backtoisland[0],20,20,136,60,lpddsback,1);
	static bool switch_of_back_to_island=FALSE;
	static int index_of_back_to_island=0;
	if(mouse_x>20&&mouse_x<156&&mouse_y>20&&mouse_y<80)
	{

		DDraw_Draw_Surface(lpdds_menu_backtoisland[1],20,20,136,60,lpddsback,1);
		if(mouse_state.rgbButtons[0]&0x80)
		{
			if(sound_menu_click1==SOUND_NULL)
			{
			if(( sound_menu_click1= DSound_Load_WAV("wave\\UI Menu Click 01c.wav"))!=-1)
                sound_fx[sound_menu_click1].dsbuffer->Play(0,0,0);
			sound_menu_click1=SOUND_PLAYING;
			}////
			switch_of_back_to_island=TRUE;
		}
		else sound_menu_click1=SOUND_NULL;
	}
	if(switch_of_back_to_island)index_of_back_to_island++;
	if(index_of_back_to_island==8)
	{

		gGame_state=Island;
		switch_of_back_to_island=FALSE;
		index_of_back_to_island=0;
	}
}

void _Temple_blue(CPerson &DaVinci)
{
	Temple_temp=Temple_blue;
	DDraw_Fill_Surface(lpdds_black,0);
	DDraw_Draw_Surface(lpdds_temple_blue,0,0,SCREEN_WIDTH,SCREEN_HEIGHT,lpddsback,0);
	static int Page=1;
	int index_x=-1;int index_y=-1;
	int index_of_map;
if(Page==1)
{
	
	for(int i=0;i<9;i++)
	{
	DDraw_Draw_Surface_Scaled(lpdds_blue_level[i],225+(i%3)*110,85+(i/3)*110,16,16,110,110,lpddsback,0);
	DDraw_Draw_Surface(lpdds_slider_up,556,85,16,16,lpddsback,1);
	DDraw_Draw_Surface(lpdds_slider_down,556,399,16,16,lpddsback,1);
	}
	if(mouse_x>=225&&mouse_x<555&&mouse_y>=85&&mouse_y<=415)
	{
		index_x=floor((mouse_x-225)/110);
		index_y=floor((mouse_y-85)/110);
	}
	if(index_x>=0&&index_x<3&&index_y>=0&&index_y<3)
	{
		index_of_map=index_x+index_y*3;
		//准备读入文件
		char str1[30]={"blue_level\\"};
		char cnumber[3];
		if(index_of_map<9) 
		{ 
			cnumber[0]=index_of_map+49;cnumber[1]='\0';
		}
		if(index_of_map>=9)
		{
			cnumber[0]='1';cnumber[1]=index_of_map-10+49;
			cnumber[2]='\0';
		}
		char str3[]={".txt"};
		strcat(str1,cnumber);
		strcat(str1,str3);
		static bool switch_of_index_of_slipstate=FALSE;//用于延时切换
		static int index_of_flipstate=0;//用于延时切换
		if(mouse_state.rgbButtons[0] & 0x80)
		{
			gLevel_map_temp=lpdds_blue_level[index_of_map];
			switch_of_index_of_slipstate=TRUE;
			DaVinci.Read_a_file(str1);
		}
		if(switch_of_index_of_slipstate) 
		{
			index_of_flipstate++;
		}
		if(index_of_flipstate==7)
		{
			gGame_state=Playfield;
			index_of_flipstate=0;
			switch_of_index_of_slipstate=FALSE;
		}
	}
	if(mouse_x>556&&mouse_x<572&&mouse_y>399&&mouse_y<415)
		if(mouse_state.rgbButtons[0]&0x80)
		Page=2;
}
if(Page==2)
{
	for(int i=9;i<18;i++)
	{
	DDraw_Draw_Surface_Scaled(lpdds_blue_level[i],225+(i%3)*110,85+(i/3-3)*110,16,16,110,110,lpddsback,0);
	DDraw_Draw_Surface(lpdds_slider_up,556,85,16,16,lpddsback,1);
	DDraw_Draw_Surface(lpdds_slider_down,556,399,16,16,lpddsback,1);
	}
	if(mouse_x>=225&&mouse_x<555&&mouse_y>=85&&mouse_y<=415)
	{
	
		index_x=floor((mouse_x-225)/110);
		index_y=floor((mouse_y-85)/110);
	}
	if(index_x>=0&&index_x<3&&index_y>=0&&index_y<3)
	{
		index_of_map=index_x+index_y*3+9;
		//准备读入文件
		char str1[30]={"blue_level\\"};
		char cnumber[3];
		if(index_of_map<9) 
		{ 
			cnumber[0]=index_of_map+49;cnumber[1]='\0';
		}
		if(index_of_map>=9)
		{
			cnumber[0]='1';cnumber[1]=index_of_map-10+49;
			cnumber[2]='\0';
		}
		char str3[]={".txt"};
		strcat(str1,cnumber);
		strcat(str1,str3);
		static bool switch_of_index_of_slipstate=FALSE;//用于延时切换
		static int index_of_flipstate=0;//用于延时切换
		if((mouse_state.rgbButtons[0] & 0x80)&&index_of_map<18)
		{
			gLevel_map_temp=lpdds_blue_level[index_of_map];
			switch_of_index_of_slipstate=TRUE;
			DaVinci.Read_a_file(str1);
		}
		if(switch_of_index_of_slipstate) 
		{
			index_of_flipstate++;
		}
		if(index_of_flipstate==7)
		{
			gGame_state=Playfield;
			index_of_flipstate=0;
			switch_of_index_of_slipstate=FALSE;
		}
	}
	if(mouse_x>556&&mouse_x<572&&mouse_y>85&&mouse_y<101)
		if(mouse_state.rgbButtons[0]&0x80)
		Page=1;
}
	//准备返回
	DDraw_Draw_Surface(lpdds_menu_backtoisland[0],20,20,136,60,lpddsback,1);
	static bool switch_of_back_to_island=FALSE;
	static int index_of_back_to_island=0;
	if(mouse_x>20&&mouse_x<156&&mouse_y>20&&mouse_y<80)
	{

		DDraw_Draw_Surface(lpdds_menu_backtoisland[1],20,20,136,60,lpddsback,1);
		if(mouse_state.rgbButtons[0]&0x80)
		{
			if(sound_menu_click1==SOUND_NULL)
			{
			if(( sound_menu_click1= DSound_Load_WAV("wave\\UI Menu Click 01c.wav"))!=-1)
                sound_fx[sound_menu_click1].dsbuffer->Play(0,0,0);
			sound_menu_click1=SOUND_PLAYING;
			}////
			switch_of_back_to_island=TRUE;
		}
		else sound_menu_click1=SOUND_NULL;
	}
	if(switch_of_back_to_island)index_of_back_to_island++;
	if(index_of_back_to_island==8)
	{

		gGame_state=Island;
		switch_of_back_to_island=FALSE;
		index_of_back_to_island=0;
	}
}

void _Help()
{
	//画背景图

	DDraw_Draw_Surface(lpdds_help,0,0,SCREEN_WIDTH,SCREEN_HEIGHT,lpddsback,0);
	DDraw_Draw_Surface(lpdds_menu_backtomainmenu[0],20,224,116,56,lpddsback,1);//65
	//检测鼠标，并做进一步的操作
	if(mouse_x>=0&&mouse_x<=144&&mouse_y>=224&&mouse_y<=280)
	{
		DDraw_Draw_Surface(lpdds_menu_backtomainmenu[1],20,224,116,56,lpddsback,1);//65
		if(mouse_state.rgbButtons[0] & 0x80) 
		{
			if(sound_menu_click1==SOUND_NULL)
			{
			if(( sound_menu_click1= DSound_Load_WAV("wave\\UI Menu Click 01c.wav"))!=-1)
                sound_fx[sound_menu_click1].dsbuffer->Play(0,0,0);
			sound_menu_click1=SOUND_PLAYING;
			}////
		    gGame_state=Gameseletct;
		}
		else sound_menu_click1=SOUND_NULL;
	}
}

void _AboutUs()
{
	//画背景图

	DDraw_Draw_Surface(lpdds_aboutus,0,0,SCREEN_WIDTH,SCREEN_HEIGHT,lpddsback,0);
	DDraw_Draw_Surface(lpdds_menu_backtomainmenu[0],400,0,116,56,lpddsback,1);//65
	//检测鼠标，并做进一步的操作
	if(mouse_x>=400&&mouse_x<=516&&mouse_y>=0&&mouse_y<=56)
	{
		DDraw_Draw_Surface(lpdds_menu_backtomainmenu[1],400,0,116,56,lpddsback,1);//65
		if(mouse_state.rgbButtons[0] & 0x80) 
		{
			if(sound_menu_click1==SOUND_NULL)
			{
			if(( sound_menu_click1= DSound_Load_WAV("wave\\UI Menu Click 01c.wav"))!=-1)
                sound_fx[sound_menu_click1].dsbuffer->Play(0,0,0);
			sound_menu_click1=SOUND_PLAYING;
			}////
		    gGame_state=Gameseletct;
		}
		else sound_menu_click1=SOUND_NULL;
	}
}