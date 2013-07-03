#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_gfxPrimitives.h>
#include <SDL/SDL_rotozoom.h>
#include "eagle.hpp"

/* constants */
#define SHIP_SHAPE_W         60
#define SHIP_SHAPE_H         180
#define CLEAR_SURFACE_OFFSET 10

/* sprites paths */
#define SHIP_SPRITE_NO_FLAME  "sprites/ship_no_flame.png"
#define SHIP_SPRITE_BIG_FLAME "sprites/ship_big_flame.png"
#define SHIP_SPRITE_MID_FLAME "sprites/ship_mid_flame.png"
#define SHIP_SPRITE_LOW_FLAME "sprites/ship_low_flame.png"


/* the ship class holding its drawing surface and position/size rect
 * it also holds a CEagle object with the internal ship logic.
 */
class CShip {

	public:
		CShip (short int initposx, short int initposy);
		void update (unsigned int timedelta);
		void draw (SDL_Surface *dst);
		void clear (SDL_Surface *dst);
		CEagle *eagle;

	private:
		SDL_Surface *ssprite;          /* the current active sprite */
		SDL_Surface *ssprite_noflame;  /* the ship sprites */
		SDL_Surface *ssprite_bigflame;
		SDL_Surface *ssprite_midflame;    
		SDL_Surface *ssprite_lowflame;  
		SDL_Surface *shiprotsprite;    /* the rotated ship sprite */
		SDL_Rect *shiprect;            /* rect with ship sprite position and size */
		SDL_Rect *shiprectclr;         /* rect to clear the ship shape */	
};
