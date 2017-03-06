#define WINDOW_CLASS_NAME "WINCLASS1"

// default screen size
#define SCREEN_WIDTH    640  // size of screen
#define SCREEN_HEIGHT   480
#define SCREEN_BPP      16   // bits per pixel
#define DDRAW_INIT_STRUCT(ddstruct) { memset(&ddstruct,0,sizeof(ddstruct)); ddstruct.dwSize=sizeof(ddstruct); }
#define _RGB32BIT(a,r,g,b) ((b) + ((g) << 8) + ((r) << 16) + ((a) << 24))

// this builds a 16 bit color value in 5.6.5 format (green dominate mode)
#define _RGB16BIT565(r,g,b) ((b & 31) + ((g & 63) << 5) + ((r & 31) << 11))

#define BITMAP_ID            0x4D42 // universal id for a bitmap


typedef struct BITMAP_FILE_TAG
{
	BITMAPFILEHEADER bitmapfileheader;  // this contains the bitmapfile header
	BITMAPINFOHEADER bitmapinfoheader;  // this is all the info including the palette
	PALETTEENTRY     palette[256];      // we will store the palette here
	UCHAR            *buffer;           // this is a pointer to the data

} BITMAP_FILE, *BITMAP_FILE_PTR;


extern HWND      main_window_handle;
extern LPDIRECTDRAW7         lpdd        ;    // dd object
extern LPDIRECTDRAWSURFACE7  lpddsprimary ;   // dd primary surface
extern LPDIRECTDRAWSURFACE7  lpddsback    ;   // dd back surface
extern LPDIRECTDRAWPALETTE   lpddpal      ;   // a pointer to the created dd palette
extern LPDIRECTDRAWCLIPPER   lpddclipper  ;   // dd clipper
extern PALETTEENTRY          palette[256];          // color palette
extern PALETTEENTRY          save_palette[256];     // used to save palettes
extern DDSURFACEDESC2        ddsd;                  // a direct draw surface description struct
extern DDBLTFX               ddbltfx;               // used to fill
extern DDSCAPS2              ddscaps;               // a direct draw surface capabilities struct
extern HRESULT               ddrval;                // result back from dd calls
extern DWORD                 start_clock_count ; // used for timing
extern LPDIRECTDRAWSURFACE7  lpdds_playfield;
extern LPDIRECTDRAWSURFACE7  lpdds_backtitle;
extern LPDIRECTDRAWSURFACE7  lpdds_gameselect;
extern LPDIRECTDRAWSURFACE7  lpdds_island ;
extern LPDIRECTDRAWSURFACE7  lpdds_islandsky ;
extern LPDIRECTDRAWSURFACE7  lpdds_menu_play;
extern LPDIRECTDRAWSURFACE7  lpdds_menu_option;
extern LPDIRECTDRAWSURFACE7  lpdds_menu_quit;
extern LPDIRECTDRAWSURFACE7  lpdds_quit;
extern LPDIRECTDRAWSURFACE7  lpdds_menu_backtotemple[2];
extern LPDIRECTDRAWSURFACE7  lpdds_menu_backtomainmenu[3];
extern LPDIRECTDRAWSURFACE7  lpdds_black;
extern LPDIRECTDRAWSURFACE7  lpdds_hair[3];
extern LPDIRECTDRAWSURFACE7  lpdds_smile;
extern LPDIRECTDRAWSURFACE7  lpdds_islandmapsomke[3];
extern LPDIRECTDRAWSURFACE7  lpdds_cursor_pointer;
//temple
extern LPDIRECTDRAWSURFACE7 lpdds_templebacchus[2];
extern LPDIRECTDRAWSURFACE7 lpdds_templecupid[2];
extern LPDIRECTDRAWSURFACE7 lpdds_templediane[2];
extern LPDIRECTDRAWSURFACE7 lpdds_templeflora[2];
extern LPDIRECTDRAWSURFACE7 lpdds_templejupiter[2];
extern LPDIRECTDRAWSURFACE7 lpdds_templeneptune[2];
extern LPDIRECTDRAWSURFACE7 lpdds_templeproserpine[2];
extern LPDIRECTDRAWSURFACE7 lpdds_templetutorial;
extern LPDIRECTDRAWSURFACE7 lpdds_templevulcan[2];
//temple_red,yellow,blue,purple
extern LPDIRECTDRAWSURFACE7 lpdds_temple_red;
extern LPDIRECTDRAWSURFACE7 lpdds_temple_yellow;
extern LPDIRECTDRAWSURFACE7 lpdds_temple_purple;
extern LPDIRECTDRAWSURFACE7 lpdds_temple_blue;
//temple_red_levels
extern LPDIRECTDRAWSURFACE7 lpdds_red_level[13];
//
extern LPDIRECTDRAWSURFACE7 lpdds_purple_level[15];
//
extern LPDIRECTDRAWSURFACE7 lpdds_blue_level[18];
//
extern LPDIRECTDRAWSURFACE7 lpdds_yellow_level[18];

extern LPDIRECTDRAWSURFACE7 lpdds_slider_up;
extern LPDIRECTDRAWSURFACE7 lpdds_slider_down;
//
extern LPDIRECTDRAWSURFACE7 lpdds_menu_backtoisland[2];
//
extern LPDIRECTDRAWSURFACE7  lpdds_help;
extern LPDIRECTDRAWSURFACE7  lpdds_aboutus;
extern LPDIRECTDRAWSURFACE7  lpdds_menu_help[2];
extern LPDIRECTDRAWSURFACE7  lpdds_menu_aboutus[2];

extern BITMAP_FILE map_backtitle;
extern BITMAP_FILE map_gameselect;
extern BITMAP_FILE map_playfield;
extern BITMAP_FILE map_island[2];
extern BITMAP_FILE map_menu_play;
extern BITMAP_FILE map_menu_option;
extern BITMAP_FILE map_menu_quit;
extern BITMAP_FILE map_quit;
extern BITMAP_FILE map_menu_backtotemple[2];
extern BITMAP_FILE map_menu_backtomainmenu[3];
extern BITMAP_FILE map_menu_backtoisland[2];
extern BITMAP_FILE map_black;
extern BITMAP_FILE map_cursor_pointer;
extern BITMAP_FILE map_hair[3];
extern BITMAP_FILE map_smile;
//temple
extern BITMAP_FILE map_templebacchus1;//1 
extern BITMAP_FILE map_templebacchus2;
extern BITMAP_FILE map_templecupid1;//2 
extern BITMAP_FILE map_templecupid2;
extern BITMAP_FILE map_templediane1;//3 
extern BITMAP_FILE map_templediane2;
extern BITMAP_FILE map_templeflora1;//4 
extern BITMAP_FILE map_templeflora2;
extern BITMAP_FILE map_templejupiter1;//5 
extern BITMAP_FILE map_templejupiter2;
extern BITMAP_FILE map_templeneptune1;//6
extern BITMAP_FILE map_templeneptune2;
extern BITMAP_FILE map_templeproserpine1;//7
extern BITMAP_FILE map_templeproserpine2;
extern BITMAP_FILE map_templetutorial;//8 
extern BITMAP_FILE map_templevulcan1;//9 
extern BITMAP_FILE map_templevulcan2;
//temple_red,yellow,blue,purple
extern BITMAP_FILE map_temple_red;
extern BITMAP_FILE map_temple_yellow;
extern BITMAP_FILE map_temple_blue;
extern BITMAP_FILE map_temple_purple;
//temple_red_levels
extern BITMAP_FILE map_red_level[13];
//temple_purple_levels
extern BITMAP_FILE map_purple_level[15];
extern BITMAP_FILE map_blue_level[18];
extern BITMAP_FILE map_yellow_level[18];
extern BITMAP_FILE map_slider_up;
extern BITMAP_FILE map_slider_down;
//
extern BITMAP_FILE map_help;
extern BITMAP_FILE map_aboutus;
extern BITMAP_FILE map_menu_help[2];
extern BITMAP_FILE map_menu_aboutus[2];


//DaVinci
extern BITMAP_FILE map_islandmapsmoke[3];
extern BITMAP_FILE map_justmove[4];
extern BITMAP_FILE map_justthrow[4][2];
extern BITMAP_FILE map_personshadow;
extern LPDIRECTDRAWSURFACE7  lpddspicture ;
extern BITMAP_FILE map_aimcursorblue;
extern BITMAP_FILE map_aimcursorred;
extern BITMAP_FILE map_levels_nil;
//bricks
extern BITMAP_FILE map_tileblue[5];
extern BITMAP_FILE map_tiledarkblue[5];
extern BITMAP_FILE map_tilered[5];
//bricks trials
extern BITMAP_FILE map_tiletrail_down;
extern BITMAP_FILE map_tiletrail_up;
extern BITMAP_FILE map_tiletrail_left;
extern BITMAP_FILE map_tiletrail_right;
extern BITMAP_FILE map_tile_want_tile;
extern BITMAP_FILE map_aim_arrow[4];
//STRUCT//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////


int Flip_Bitmap(UCHAR *image, int bytes_per_line, int height);//后备缓冲与主表面的切换

int Load_Bitmap_File(BITMAP_FILE_PTR bitmap, char *filename);//读入一个位图

int Unload_Bitmap_File(BITMAP_FILE_PTR bitmap);//卸载一个位图

LPDIRECTDRAWCLIPPER DDraw_Attach_Clipper(LPDIRECTDRAWSURFACE7 lpdds,int num_rects,LPRECT clip_list);//创建一个裁剪区，只用在GAME_INIT()中

int DDraw_Fill_Surface(LPDIRECTDRAWSURFACE7 lpdds,int color);//向表面中填充背景色

int DDraw_Draw_Surface(LPDIRECTDRAWSURFACE7 source, int x, int y,int width, int height,        // size of source surface
                      LPDIRECTDRAWSURFACE7 dest, int transparent ) ;         // transpa//从一个表面到另一个表面绘图

int Scan_Image_Bitmap(BITMAP_FILE_PTR bitmap_scn,LPDIRECTDRAWSURFACE7 lpdds, int cx, int cy);//提取位图

LPDIRECTDRAWSURFACE7 DDraw_Create_Surface(int width, int height, int mem_flags, int color_key = 0);//创建一个离屏表面

LPDIRECTDRAWSURFACE7 DDraw_Create_Surface_nowhite(int width, int height, int mem_flags, int color_key = 0);

int Draw_Line(int x0, int y0,int x1, int y1, LPDIRECTDRAWSURFACE7 lpdds);

int Draw_Text_GDI(char *text, int x,int y,COLORREF color, LPDIRECTDRAWSURFACE7 lpdds);

LPDIRECTDRAWSURFACE7 Lpdds_Init(char *filename,int width,int height);

int DDraw_Draw_Surface_Scaled(LPDIRECTDRAWSURFACE7 source, int x, int y,                 
							 int width_src, int height_src,int width_dest, int height_dest,
						     LPDIRECTDRAWSURFACE7 dest,int transparent = 1) ;         


int DDraw_Draw_Surface_Scaled_parts(LPDIRECTDRAWSURFACE7 source, // source surface to draw
                      int x, int y,                 // position to draw at
                      int src_rightx, int src_bottomy,// size of source surface
                      int width_dest, int height_dest,// size of dest surface
                      LPDIRECTDRAWSURFACE7 dest,    // surface to draw the surface on
                      int transparent=1 )   ;       // transparency flag     
