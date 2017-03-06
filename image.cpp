
#define WIN32_LEAN_AND_MEAN  // just say no to MFC

#include "include.h"

LPDIRECTDRAW7         lpdd        = NULL;    // dd object
LPDIRECTDRAWSURFACE7  lpddsprimary = NULL;   // dd primary surface
LPDIRECTDRAWSURFACE7  lpddsback    = NULL;   // dd back surface
LPDIRECTDRAWPALETTE   lpddpal      = NULL;   // a pointer to the created dd palette
LPDIRECTDRAWCLIPPER   lpddclipper  = NULL;   // dd clipper
PALETTEENTRY          palette[256];          // color palette
PALETTEENTRY          save_palette[256];     // used to save palettes
DDSURFACEDESC2        ddsd;                  // a direct draw surface description struct
DDBLTFX               ddbltfx;               // used to fill
DDSCAPS2              ddscaps;               // a direct draw surface capabilities struct
HRESULT               ddrval;                // result back from dd calls
DWORD                 start_clock_count = 0;                // holds the bitmap
LPDIRECTDRAWSURFACE7  lpdds_playfield = NULL;
LPDIRECTDRAWSURFACE7  lpdds_backtitle;
LPDIRECTDRAWSURFACE7  lpdds_gameselect = NULL;
LPDIRECTDRAWSURFACE7  lpdds_island = NULL;
LPDIRECTDRAWSURFACE7  lpdds_islandsky = NULL;
LPDIRECTDRAWSURFACE7  lpdds_menu_play = NULL;
LPDIRECTDRAWSURFACE7  lpdds_menu_option = NULL;
LPDIRECTDRAWSURFACE7  lpdds_menu_quit = NULL;
LPDIRECTDRAWSURFACE7  lpdds_menu_backtotemple[2];
LPDIRECTDRAWSURFACE7  lpdds_menu_backtomainmenu[3];
LPDIRECTDRAWSURFACE7  lpdds_hair[3];
LPDIRECTDRAWSURFACE7  lpdds_smile;
LPDIRECTDRAWSURFACE7  lpdds_islandmapsomke[3];
LPDIRECTDRAWSURFACE7  lpdds_black = NULL;
LPDIRECTDRAWSURFACE7  lpdds_cursor_pointer;
LPDIRECTDRAWSURFACE7  lpdds_quit;
LPDIRECTDRAWSURFACE7  lpdds_help=NULL;
LPDIRECTDRAWSURFACE7  lpdds_aboutus;

LPDIRECTDRAWSURFACE7 lpdds_menu_backtoisland[2];
//temple
//temple
LPDIRECTDRAWSURFACE7 lpdds_templebacchus[2];
LPDIRECTDRAWSURFACE7 lpdds_templecupid[2];
LPDIRECTDRAWSURFACE7 lpdds_templediane[2];
LPDIRECTDRAWSURFACE7 lpdds_templeflora[2];
LPDIRECTDRAWSURFACE7 lpdds_templejupiter[2];
LPDIRECTDRAWSURFACE7 lpdds_templeneptune[2];
LPDIRECTDRAWSURFACE7 lpdds_templeproserpine[2];
LPDIRECTDRAWSURFACE7 lpdds_templetutorial;
LPDIRECTDRAWSURFACE7 lpdds_templevulcan[2];
//temple_red,blue,yellow,purple
LPDIRECTDRAWSURFACE7 lpdds_temple_red;
LPDIRECTDRAWSURFACE7 lpdds_temple_yellow;
LPDIRECTDRAWSURFACE7 lpdds_temple_purple;
LPDIRECTDRAWSURFACE7 lpdds_temple_blue;
//temple_red_levels
LPDIRECTDRAWSURFACE7 lpdds_red_level[13];
//temple_purple_levels
LPDIRECTDRAWSURFACE7 lpdds_purple_level[15];
//
LPDIRECTDRAWSURFACE7 lpdds_blue_level[18];
//temple_yellow_levels
LPDIRECTDRAWSURFACE7 lpdds_yellow_level[18];
LPDIRECTDRAWSURFACE7 lpdds_slider_up;
LPDIRECTDRAWSURFACE7 lpdds_slider_down;
//
LPDIRECTDRAWSURFACE7  lpdds_menu_help[2];
LPDIRECTDRAWSURFACE7  lpdds_menu_aboutus[2];


BITMAP_FILE map_backtitle;
BITMAP_FILE map_gameselect;
BITMAP_FILE map_playfield;
BITMAP_FILE map_island[2];
BITMAP_FILE map_menu_play;
BITMAP_FILE map_menu_option;
BITMAP_FILE map_menu_quit;
BITMAP_FILE map_menu_backtotemple[2];
BITMAP_FILE map_menu_backtomainmenu[3];
BITMAP_FILE map_black;
BITMAP_FILE map_cursor_pointer;
BITMAP_FILE map_hair[3];
BITMAP_FILE map_smile;
BITMAP_FILE map_islandmapsmoke[3];
BITMAP_FILE map_quit;
//backtoisland
BITMAP_FILE map_menu_backtoisland[2];
//
BITMAP_FILE map_help;
BITMAP_FILE map_aboutus;
BITMAP_FILE map_menu_help[2];
BITMAP_FILE map_menu_aboutus[2];

//temple_red,purple,yellow,blue
BITMAP_FILE map_temple_red;
BITMAP_FILE map_temple_yellow;
BITMAP_FILE map_temple_blue;
BITMAP_FILE map_temple_purple;

//temp
BITMAP_FILE map_templebacchus1;//1
BITMAP_FILE map_templebacchus2;
BITMAP_FILE map_templecupid1;//2
BITMAP_FILE map_templecupid2;
BITMAP_FILE map_templediane1;//3
BITMAP_FILE map_templediane2;
BITMAP_FILE map_templeflora1;//4
BITMAP_FILE map_templeflora2;
BITMAP_FILE map_templejupiter1;//5
BITMAP_FILE map_templejupiter2;
BITMAP_FILE map_templeneptune1;//6
BITMAP_FILE map_templeneptune2;
BITMAP_FILE map_templeproserpine1;//7
BITMAP_FILE map_templeproserpine2;
BITMAP_FILE map_templetutorial;//8
BITMAP_FILE map_templevulcan1;//9
BITMAP_FILE map_templevulcan2;
//temple_red_levels
BITMAP_FILE map_red_level[13];
//temple_purple_level
BITMAP_FILE map_purple_level[15];
//temple_blue_level
BITMAP_FILE map_blue_level[18];
//
BITMAP_FILE map_yellow_level[18];
//slider_up,down
BITMAP_FILE map_slider_up;
BITMAP_FILE map_slider_down;
//DaVinci
BITMAP_FILE map_justmove[4];
BITMAP_FILE map_justthrow[4][2];
BITMAP_FILE map_personshadow;
BITMAP_FILE map_aimcursorblue;
BITMAP_FILE map_aimcursorred;
BITMAP_FILE map_levels_nil;
//bricks
BITMAP_FILE map_tileblue[5];
BITMAP_FILE map_tiledarkblue[5];
BITMAP_FILE map_tilered[5];
BITMAP_FILE map_tiletrail_down;
BITMAP_FILE map_tiletrail_up;
BITMAP_FILE map_tiletrail_left;
BITMAP_FILE map_tiletrail_right;
BITMAP_FILE map_tile_want_tile;

BITMAP_FILE map_aim_arrow[4];
//////////////////////////////////////////////////////////////////////////


// FUNCTIONS ////////////////////////////////////////////////

int Load_Bitmap_File(BITMAP_FILE_PTR bitmap, char *filename)
{
	// this function opens a bitmap file and loads the data into bitmap

	int file_handle,  // the file handle
		index;        // looping index

	UCHAR   *temp_buffer = NULL; // used to convert 24 bit images to 16 bit
	OFSTRUCT file_data;          // the file data information

	// open the file if it exists
	if ((file_handle = OpenFile(filename,&file_data,OF_READ))==-1)
		return(0);

	// now load the bitmap file header
	_lread(file_handle, &bitmap->bitmapfileheader,sizeof(BITMAPFILEHEADER));

	// test if this is a bitmap file
	if (bitmap->bitmapfileheader.bfType!=BITMAP_ID)
	{
		// close the file
		_lclose(file_handle);

		// return error
		return(0);
	} // end if

	// now we know this is a bitmap, so read in all the sections

	// first the bitmap infoheader

	// now load the bitmap file header
	_lread(file_handle, &bitmap->bitmapinfoheader,sizeof(BITMAPINFOHEADER));



	// finally the image data itself
	_lseek(file_handle,-(int)(bitmap->bitmapinfoheader.biSizeImage),SEEK_END);

	// now read in the image, if the image is 8 or 16 bit then simply read it
	// but if its 24 bit then read it into a temporary area and then convert
	// it to a 16 bit image


		// delete the last image if there was one
		if (bitmap->buffer)
			free(bitmap->buffer);

		// allocate the memory for the image
		if (!(bitmap->buffer = (UCHAR *)malloc(bitmap->bitmapinfoheader.biSizeImage)))
		{
			// close the file
			_lclose(file_handle);

			// return error
			return(0);
		} // end if

		// now read it in
		_lread(file_handle,bitmap->buffer,bitmap->bitmapinfoheader.biSizeImage);

	// close the file
	_lclose(file_handle);

	// flip the bitmap
	Flip_Bitmap(bitmap->buffer, 
		bitmap->bitmapinfoheader.biWidth*(bitmap->bitmapinfoheader.biBitCount/8), 
		bitmap->bitmapinfoheader.biHeight);

	// return success
	return(1);

} // end Load_Bitmap_File




int Unload_Bitmap_File(BITMAP_FILE_PTR bitmap)
{
	// this function releases all memory associated with "bitmap"
	if (bitmap->buffer)
	{
		// release memory
		free(bitmap->buffer);

		// reset pointer
		bitmap->buffer = NULL;

	} // end if

	// return success
	return(1);

} // end Unload_Bitmap_File




int Flip_Bitmap(UCHAR *image, int bytes_per_line, int height)
{
	// this function is used to flip bottom-up .BMP images

	UCHAR *buffer; // used to perform the image processing
	int index;     // looping index

	// allocate the temporary buffer
	if (!(buffer = (UCHAR *)malloc(bytes_per_line*height)))
		return(0);

	// copy image to work area
	memcpy(buffer,image,bytes_per_line*height);

	// flip vertically
	for (index=0; index < height; index++)
		memcpy(&image[((height-1) - index)*bytes_per_line],
		&buffer[index*bytes_per_line], bytes_per_line);

	// release the memory
	free(buffer);

	// return success
	return(1);

} // end Flip_Bitmap




LPDIRECTDRAWCLIPPER DDraw_Attach_Clipper(LPDIRECTDRAWSURFACE7 lpdds,
                                         int num_rects,
                                         LPRECT clip_list)
{
// this function creates a clipper from the sent clip list and attaches
// it to the sent surface

int index;                         // looping var
LPDIRECTDRAWCLIPPER lpddclipper;   // pointer to the newly created dd clipper
LPRGNDATA region_data;             // pointer to the region data that contains
                                   // the header and clip list

// first create the direct draw clipper
if (FAILED(lpdd->CreateClipper(0,&lpddclipper,NULL)))
   return(NULL);

// now create the clip list from the sent data

// first allocate memory for region data
region_data = (LPRGNDATA)malloc(sizeof(RGNDATAHEADER)+num_rects*sizeof(RECT));

// now copy the rects into region data
memcpy(region_data->Buffer, clip_list, sizeof(RECT)*num_rects);

// set up fields of header
region_data->rdh.dwSize          = sizeof(RGNDATAHEADER);
region_data->rdh.iType           = RDH_RECTANGLES;
region_data->rdh.nCount          = num_rects;
region_data->rdh.nRgnSize        = num_rects*sizeof(RECT);

region_data->rdh.rcBound.left    =  64000;
region_data->rdh.rcBound.top     =  64000;
region_data->rdh.rcBound.right   = -64000;
region_data->rdh.rcBound.bottom  = -64000;

// find bounds of all clipping regions
for (index=0; index<num_rects; index++)
    {
    // test if the next rectangle unioned with the current bound is larger
    if (clip_list[index].left < region_data->rdh.rcBound.left)
       region_data->rdh.rcBound.left = clip_list[index].left;

    if (clip_list[index].right > region_data->rdh.rcBound.right)
       region_data->rdh.rcBound.right = clip_list[index].right;

    if (clip_list[index].top < region_data->rdh.rcBound.top)
       region_data->rdh.rcBound.top = clip_list[index].top;

    if (clip_list[index].bottom > region_data->rdh.rcBound.bottom)
       region_data->rdh.rcBound.bottom = clip_list[index].bottom;

    } // end for index

// now we have computed the bounding rectangle region and set up the data
// now let's set the clipping list

if (FAILED(lpddclipper->SetClipList(region_data, 0)))
   {
   // release memory and return error
   free(region_data);
   return(NULL);
   } // end if

// now attach the clipper to the surface
if (FAILED(lpdds->SetClipper(lpddclipper)))
   {
   // release memory and return error
   free(region_data);
   return(NULL);
   } // end if

// all is well, so release memory and send back the pointer to the new clipper
free(region_data);
return(lpddclipper);

} // end DDraw_Attach_Clipper

///////////////////////////////////////////////////////////   

int DDraw_Fill_Surface(LPDIRECTDRAWSURFACE7 lpdds,int color)
{
DDBLTFX ddbltfx; // this contains the DDBLTFX structure

// clear out the structure and set the size field 
DDRAW_INIT_STRUCT(ddbltfx);

// set the dwfillcolor field to the desired color
ddbltfx.dwFillColor = color; 

// ready to blt to surface
lpdds->Blt(NULL,       // ptr to dest rectangle
           NULL,       // ptr to source surface, NA            
           NULL,       // ptr to source rectangle, NA
           DDBLT_COLORFILL | DDBLT_WAIT,   // fill and wait                   
           &ddbltfx);  // ptr to DDBLTFX structure

// return success
return(1);
} // end DDraw_Fill_Surface

int DDraw_Draw_Surface(LPDIRECTDRAWSURFACE7 source, // source surface to draw
                      int x, int y,                 // position to draw at
                      int width, int height,        // size of source surface
                      LPDIRECTDRAWSURFACE7 dest,    // surface to draw the surface on
                      int transparent = 1 )          // transparency flag
{
// draw the surface at the x,y defined by dest, note that we are sending
// the size of the surface, we could query for it, but that takes time
// basically, we are really lacking datastructure as this point, since
// you would create a datastructure that keep important info about the
// surface, so you did't have to query it from directdraw

RECT dest_rect,   // the destination rectangle
     source_rect; // the source rectangle                             

// fill in the destination rect
dest_rect.left   = x;
dest_rect.top    = y;
dest_rect.right  = x+width-1;
dest_rect.bottom = y+height-1;

// fill in the source rect
source_rect.left    = 0;
source_rect.top     = 0;
source_rect.right   = width-1;
source_rect.bottom  = height-1;

// test transparency flag

if (transparent)
   {
   // enable color key blit
   // blt to destination surface
   if (FAILED(dest->Blt(&dest_rect, source,
                     &source_rect,(DDBLT_WAIT | DDBLT_KEYSRC),
                     NULL)))
           return(0);

   } // end if
else
   {
   // perform blit without color key
   // blt to destination surface
   if (FAILED(dest->Blt(&dest_rect, source,
                     &source_rect,(DDBLT_WAIT),
                     NULL)))
           return(0);

   } // end if

// return success
return(1);

} // end DDraw_Draw_Surface

//////////////////////////////////////////////////////////////////////////
int DDraw_Draw_Surface_Scaled(LPDIRECTDRAWSURFACE7 source, // source surface to draw
                      int x, int y,                 // position to draw at
                      int width_src, int height_src,// size of source surface
                      int width_dest, int height_dest,// size of dest surface
                      LPDIRECTDRAWSURFACE7 dest,    // surface to draw the surface on
                      int transparent )          // transparency flag
{
// draw the surface at the x,y defined by dest, send both the original
// source size of surface, along with the desired size, if they are 
// different then directdraw will scale the bitmap for you
// note that we are sending
// the size of the surface, we could query for it, but that takes time
// basically, we are really lacking datastructure as this point, since
// you would create a datastructure that keep important info about the
// surface, so you did't have to query it from directdraw


RECT dest_rect,   // the destination rectangle
     source_rect; // the source rectangle                             

// fill in the destination rect
dest_rect.left   = x;
dest_rect.top    = y;
dest_rect.right  = x+width_dest-1;
dest_rect.bottom = y+height_dest-1;

// fill in the source rect
source_rect.left    = 0;
source_rect.top     = 0;
source_rect.right   = width_src-1;
source_rect.bottom  = height_src-1;

// test transparency flag

if (transparent)
   {
   // enable color key blit
   // blt to destination surface
   if (FAILED(dest->Blt(&dest_rect, source,
                     &source_rect,(DDBLT_WAIT | DDBLT_KEYSRC),
                     NULL)))
           return(0);

   } // end if
else
   {
   // perform blit without color key
   // blt to destination surface
   if (FAILED(dest->Blt(&dest_rect, source,
                     &source_rect,(DDBLT_WAIT),
                     NULL)))
           return(0);

   } // end if

// return success
return(1);

} // end DDraw_Draw_Surface_Scaled
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
int DDraw_Draw_Surface_Scaled_parts(LPDIRECTDRAWSURFACE7 source, // source surface to draw
                      int x, int y,                 // position to draw at
                      int src_rightx, int src_bottomy,// size of source surface
                      int width_dest, int height_dest,// size of dest surface
                      LPDIRECTDRAWSURFACE7 dest,    // surface to draw the surface on
                      int transparent )          // transparency flag
{
// draw the surface at the x,y defined by dest, send both the original
// source size of surface, along with the desired size, if they are 
// different then directdraw will scale the bitmap for you
// note that we are sending
// the size of the surface, we could query for it, but that takes time
// basically, we are really lacking datastructure as this point, since
// you would create a datastructure that keep important info about the
// surface, so you did't have to query it from directdraw


RECT dest_rect,   // the destination rectangle
     source_rect; // the source rectangle                             

// fill in the destination rect
dest_rect.left   = x;
dest_rect.top    = y;
dest_rect.right  = x+width_dest-1;
dest_rect.bottom = y+height_dest-1;

// fill in the source rect
source_rect.left    = 0;
source_rect.top     = 0;
source_rect.right   = src_rightx-1;
source_rect.bottom  = src_bottomy-1;

// test transparency flag

if (transparent)
   {
   // enable color key blit
   // blt to destination surface
   if (FAILED(dest->Blt(&dest_rect, source,
                     &source_rect,(DDBLT_WAIT | DDBLT_KEYSRC),
                     NULL)))
           return(0);

   } // end if
else
   {
   // perform blit without color key
   // blt to destination surface
   if (FAILED(dest->Blt(&dest_rect, source,
                     &source_rect,(DDBLT_WAIT),
                     NULL)))
           return(0);

   } // end if

// return success
return(1);

} // end DDraw_Draw_Surface_Scaled
//////////////////////////////////////////////////////////////////////////

int Scan_Image_Bitmap(BITMAP_FILE_PTR bitmap_scn,  
                      LPDIRECTDRAWSURFACE7 lpdds, 
                      int cx, int cy)
{
 
lpdds->Lock(NULL,
            &ddsd,
            DDLOCK_WAIT | DDLOCK_SURFACEMEMORYPTR,
            NULL);
//////////////////////////////////////////////////////////////////////////
USHORT *scanlpdds_buffer = (USHORT *)ddsd.lpSurface;    
for (int index_y = 0; index_y < cy; index_y++)
{
    for (int index_x = 0; index_x < cx; index_x++)
	{
        UCHAR blue  = (bitmap_scn->buffer[index_y*cx*3 + index_x*3 + 0]) >> 3,
              green = (bitmap_scn->buffer[index_y*cx*3 + index_x*3 + 1]) >> 2,
              red   = (bitmap_scn->buffer[index_y*cx*3 + index_x*3 + 2]) >> 3;
        USHORT pixel = _RGB16BIT565(red,green,blue);
        scanlpdds_buffer[index_x + (index_y*ddsd.lPitch >> 1)] = pixel;
	}
}
lpdds->Unlock(NULL);

// return success
return(1);

}

///////////////////////////////////////////////////////////////

LPDIRECTDRAWSURFACE7 DDraw_Create_Surface(int width, int height, int mem_flags, int color_key )
{
// this function creates an offscreen plain surface

DDSURFACEDESC2 ddsd;         // working description
LPDIRECTDRAWSURFACE7 lpdds;  // temporary surface
    
// set to access caps, width, and height
memset(&ddsd,0,sizeof(ddsd));
ddsd.dwSize  = sizeof(ddsd);
ddsd.dwFlags = DDSD_CAPS | DDSD_WIDTH | DDSD_HEIGHT;

// set dimensions of the new bitmap surface
ddsd.dwWidth  =  width;
ddsd.dwHeight =  height;

// set surface to offscreen plain
ddsd.ddsCaps.dwCaps = DDSCAPS_OFFSCREENPLAIN | DDSCAPS_VIDEOMEMORY;

// create the surface
if (FAILED(lpdd->CreateSurface(&ddsd,&lpdds,NULL)))
   return(NULL);

// test if user wants a color key
if (color_key >= 0)
   {
   	DDCOLORKEY color_key;
   color_key.dwColorSpaceLowValue  = _RGB16BIT565(0,0,0);
   color_key.dwColorSpaceHighValue = _RGB16BIT565(0,0,0);
   lpdds->SetColorKey(DDCKEY_SRCBLT, &color_key);
   } // end if

// return surface
return(lpdds);
} // end DDraw_Create_Surface

///////////////////////////////////////////////////////////////

LPDIRECTDRAWSURFACE7 DDraw_Create_Surface_nowhite(int width, int height, int mem_flags, int color_key )
{
// this function creates an offscreen plain surface

DDSURFACEDESC2 ddsd;         // working description
LPDIRECTDRAWSURFACE7 lpdds;  // temporary surface
    
// set to access caps, width, and height
memset(&ddsd,0,sizeof(ddsd));
ddsd.dwSize  = sizeof(ddsd);
ddsd.dwFlags = DDSD_CAPS | DDSD_WIDTH | DDSD_HEIGHT;

// set dimensions of the new bitmap surface
ddsd.dwWidth  =  width;
ddsd.dwHeight =  height;

// set surface to offscreen plain
ddsd.ddsCaps.dwCaps = DDSCAPS_OFFSCREENPLAIN | DDSCAPS_VIDEOMEMORY;

// create the surface
if (FAILED(lpdd->CreateSurface(&ddsd,&lpdds,NULL)))
   return(NULL);

// test if user wants a color key
if (color_key >= 0)
   {
   	DDCOLORKEY color_key;
   color_key.dwColorSpaceLowValue  = _RGB16BIT565(255,255,255);
   color_key.dwColorSpaceHighValue = _RGB16BIT565(255,255,255);
   lpdds->SetColorKey(DDCKEY_SRCBLT, &color_key);
   } // end if

// return surface
return(lpdds);
} // end DDraw_Create_Surface

int Draw_Line(int x0, int y0, // starting position 
                int x1, int y1, // ending position    // color index
                LPDIRECTDRAWSURFACE7 lpdds) // video buffer and memory pitch
{
// this function draws a line from xo,yo to x1,y1 using differential error
// terms (based on Bresenahams work)

DDSURFACEDESC2 ddsd;  //  direct draw surface description 


ddsd.dwSize = sizeof(ddsd);

// lock the display surface
lpdds->Lock(NULL,&ddsd,DDLOCK_WAIT | DDLOCK_SURFACEMEMORYPTR,NULL);




int dx,dy,dx2,dy2,x_inc,y_inc,error,index;          

int lpitch_2 = ddsd.lPitch >> 2; // USHORT strided lpitch

// pre-compute first pixel address in video buffer based on 16bit data
DWORD *vb_start2 = (DWORD *)ddsd.lpSurface + x0 + y0*lpitch_2;

// compute horizontal and vertical deltas
dx = x1-x0;
dy = y1-y0;

// test which direction the line is going in i.e. slope angle
if (dx>=0)
   {
   x_inc = 1;

   } // end if line is moving right
else
   {
   x_inc = -1;
   dx    = -dx;  // need absolute value

   } // end else moving left

// test y component of slope

if (dy>=0)
   {
   y_inc = lpitch_2;
   } // end if line is moving down
else
   {
   y_inc = -lpitch_2;
   dy    = -dy;  // need absolute value

   } // end else moving up

// compute (dx,dy) * 2
dx2 = dx << 1;
dy2 = dy << 1;

// now based on which delta is greater we can draw the line
if (dx > dy)
   {
   // initialize error term
   error = dy2 - dx; 

   // draw the line
   for (index=0; index <= dx; index++)
       {
       // set the pixel
       *vb_start2 = RGB(255,0,255);

       // test if error has overflowed
       if (error >= 0) 
          {
          error-=dx2;

          // move to next line
          vb_start2+=y_inc;

	   } // end if error overflowed

       // adjust the error term
       error+=dy2;

       // move to the next pixel
       vb_start2+=x_inc;

       } // end for

   } // end if |slope| <= 1
else
   {
   // initialize error term
   error = dx2 - dy; 

   // draw the line
   for (index=0; index <= dy; index++)
       {
       // set the pixel
       *vb_start2 = RGB(255,0,255);

       // test if error overflowed
       if (error >= 0)
          {
          error-=dy2;

          // move to next line
          vb_start2+=x_inc;

          } // end if error overflowed

       // adjust the error term
       error+=dx2;

       // move to the next pixel
       vb_start2+=y_inc;

       } // end for

   } // end else |slope| > 1
lpdds->Unlock(NULL);


// return success
return(1);

} // end Draw_Line16


///////////////////////////////////////////////////////////


int Draw_Text_GDI(char *text, int x,int y,COLORREF color, LPDIRECTDRAWSURFACE7 lpdds)
{
// this function draws the sent text on the sent surface 
// using color index as the color in the palette

HDC xdc; // the working dc

// get the dc from surface
if (FAILED(lpdds->GetDC(&xdc)))
   return(0);

// set the colors for the text up
SetTextColor(xdc,color);

// set background mode to transparent so black isn't copied
SetBkMode(xdc, TRANSPARENT);

// draw the text a
TextOut(xdc,x,y,text,strlen(text));

// release the dc
lpdds->ReleaseDC(xdc);

// return success
return(1);
} // end Draw_Text_GDI


LPDIRECTDRAWSURFACE7 Lpdds_Init(char *filename,int width,int height)
{
	LPDIRECTDRAWSURFACE7 lpdds_temp;
	BITMAP_FILE map_temp;
	if(!Load_Bitmap_File(&map_temp,filename))
		return(0);
	lpdds_temp = DDraw_Create_Surface(width,height,0,1);
	Scan_Image_Bitmap(&map_temp,lpdds_temp,width,height);/**/
   if(!Unload_Bitmap_File(&map_temp))
		return(0);
   return lpdds_temp;
}

