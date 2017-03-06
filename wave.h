//22050HZ 8bits
#define SOUND_NULL     0 
#define SOUND_LOADED   1
#define SOUND_PLAYING  2
#define SOUND_STOPPED  3
#define MAX_SOUNDS     256
#define DSBCAPS_CTRLDEFAULT (DSBCAPS_CTRLFREQUENCY | DSBCAPS_CTRLPAN | DSBCAPS_CTRLVOLUME )



typedef struct pcm_sound_typ
	{
	LPDIRECTSOUNDBUFFER dsbuffer;   // the ds buffer containing the sound
	int state;                      // state of the sound
	int rate;                       // playback rate
	int size;                       // size of sound
	int id;                         // id number of the sound
	} pcm_sound, *pcm_sound_ptr;



extern LPDIRECTSOUND		lpds;           // directsound interface pointer
extern DSBUFFERDESC		dsbd;           // directsound description
extern DSCAPS				dscaps;         // directsound caps
extern HRESULT				dsresult;       // general directsound result
extern DSBCAPS             dsbcaps;        // directsound buffer caps

extern LPDIRECTSOUNDBUFFER	lpdsbprimary,    // you won't need this normally
                    lpdsbsecondary;  // the sound buffers

extern WAVEFORMATEX        pcmwf;          // generic waveformat structure

extern pcm_sound			sound_fx[MAX_SOUNDS];    // the array of secondary sound buffers
extern int face;
extern int option;
extern int ground;
extern int oversound;
extern int work;


int DSound_Load_WAV(char *filename, int control_flags = DSBCAPS_CTRLDEFAULT);
int Dsound_Init();