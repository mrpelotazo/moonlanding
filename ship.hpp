#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_gfxPrimitives.h>
#include <SDL/SDL_rotozoom.h>
#include "eagle.hpp"

/* constants */
#define SHIP_SHAPE_W         60
#define SHIP_SHAPE_H         80
#define FLAME_SHAPE_W        SHIP_SHAPE_W
#define FLAME_SHAPE_H        60
#define FLAME_OVERLAP        10
#define CLEAR_SURFACE_OFFSET 10

/* sprites paths */
#define SHIP_SPRITE        "sprites/ship.png"
#define FLAME_SPRITE_BIG   "sprites/flame_big.png"
#define FLAME_SPRITE_MID   "sprites/flame_mid.png"
#define FLAME_SPRITE_LOW   "sprites/flame_low.png"

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
		SDL_Surface *shipsprite;       /* the ship sprite */
		SDL_Surface *flamespritebig;   /* the flame sprites */
		SDL_Surface *flamespritemid;    
		SDL_Surface *flamespritelow;  
		SDL_Surface *shiprotsprite;    /* the rotated ship surface */
		SDL_Surface *flamerotsprite;   /* the rotated flame surface */
		SDL_Rect *shiprect;            /* rect with ship sprite position and size */
		SDL_Rect *shiprectclr;         /* rect to clear the ship shape */
		SDL_Rect *flamerect;           /* rect with flame sprite position and size */

		/* draw the flame? */
		unsigned short drawflame; /* 1-> yes, 0->no */
};
