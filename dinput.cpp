#include "include.h"

LPDIRECTINPUT8        lpdi      = NULL;    // dinput object
LPDIRECTINPUTDEVICE8  lpdikey   = NULL;    // dinput keyboard
LPDIRECTINPUTDEVICE8  lpdimouse = NULL;    // dinput mouse
UCHAR        keyboard_state[256];
DIMOUSESTATE mouse_state;         // contains state of mouse
int mouse_x, mouse_y;             // used to track mouse

extern HINSTANCE main_hinstance ;
extern HWND main_window_handle  ;

int DInput_Init()
{
	if (DirectInput8Create(main_hinstance,DIRECTINPUT_VERSION,IID_IDirectInput8, (void **)&lpdi,NULL)!=DI_OK)
      return(0);

	// create a keyboard device  //////////////////////////////////
	if (lpdi->CreateDevice(GUID_SysKeyboard, &lpdikey, NULL)!=DI_OK)
	   return(0);
    if (lpdi->CreateDevice(GUID_SysMouse, &lpdimouse, NULL)!=DI_OK)
	   return(0);

	// set cooperation level
	if (lpdikey->SetCooperativeLevel(main_window_handle, 
					 DISCL_NONEXCLUSIVE | DISCL_BACKGROUND)!=DI_OK)
		return(0);
if (lpdimouse->SetCooperativeLevel(main_window_handle, 
					 DISCL_NONEXCLUSIVE | DISCL_BACKGROUND)!=DI_OK)
		return(0);
	// set data format
	if (lpdikey->SetDataFormat(&c_dfDIKeyboard)!=DI_OK)
	   return(0);
if (lpdimouse->SetDataFormat(&c_dfDIMouse)!=DI_OK)
	   return(0);
	// acquire the keyboard
	if (lpdikey->Acquire()!=DI_OK)
	   return(0);
	if (lpdimouse->Acquire()!=DI_OK)
	   return(0);
	return 1;
}