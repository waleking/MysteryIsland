extern LPDIRECTINPUT8        lpdi     ;    // dinput object
extern LPDIRECTINPUTDEVICE8  lpdikey  ;    // dinput keyboard
extern LPDIRECTINPUTDEVICE8  lpdimouse;    // dinput mouse

extern UCHAR        keyboard_state[256];
extern DIMOUSESTATE mouse_state;         // contains state of mouse
extern int mouse_x, mouse_y;             // used to track mouse
int DInput_Init();