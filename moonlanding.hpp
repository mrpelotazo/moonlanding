#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include <time.h>
#include "ship.hpp"

#define SHIP_SURFACE_W 1024
#define SHIP_SURFACE_H 768 
#define INFO_SURFACE_W SHIP_SURFACE_W
#define INFO_SURFACE_H 100
#define SCREEN_W SHIP_SURFACE_W
#define SCREEN_H (SHIP_SURFACE_H + INFO_SURFACE_H)
#define STAR_NUM 500
#define STAR_COLOR 0x606060
#define MAX_PEAKS_PER_SIDE 5
#define MAX_PEAKS MAX_PEAKS_PER_SIDE * 2 + 10 
#define MAX_GRND_H SCREEN_H/2
#define MIN_GRND_H SCREEN_H/2
#define LAND_POS_W SHIP_SHAPE_W + 20
#define FONT_PATH "/usr/share/fonts/TTF/DejaVuSansMono.ttf"
#define FONT_SIZE 17

/* Initializes SDL video and a screen */
SDL_Surface *initScreen();

/* Initializes a surface with the given rect properties */
SDL_Surface *initSurface(SDL_Rect r);

/* creates a stars background on the given surface */
void drawStars(SDL_Surface *s);

/* Initializes the font */
TTF_Font *initFont();

/* Clear a surface */
int clearSurface(SDL_Surface *ps);

/* the event handler */
void eventHandler(SDL_Event e, CShip s, unsigned short *r);

/* generate stars */
void genStars(int slx[], int sly[]);

/* draw stars */
void drawStars(SDL_Surface *dst, int slx[], int sly[]);

/* generate ground */
void genGround(int glx[], int gly[], int *length);

/* draw ground */
void drawGround(SDL_Surface *dst, int glx[], int gly[], int length);

/* Shows the eagle information on the given surface */
void showShipInfo(SDL_Surface *ps, CShip s, TTF_Font *pf, SDL_Color c);

/* Update the screen surface. Blit the other surfaces into the screen */
void updateScreen(SDL_Surface *dst, SDL_Surface *ss, SDL_Surface *is,SDL_Surface *bs, SDL_Rect *sr, SDL_Rect *ir, SDL_Rect *br);
