#include <SDL/SDL.h>
#include <SDL/SDL_gfxPrimitives.h>
#include <SDL/SDL_rotozoom.h>
#include "eagle.hpp"

#define SHIP_SHAPE_W 60
#define SHIP_SHAPE_H 80
#define FLAME_SHAPE_W SHIP_SHAPE_W
#define FLAME_SHAPE_H 60
#define FLAME_OVERLAP 10
#define CLEAR_SURFACE_OFFSET 10

/* the ship class holding its drawing surface and position/size rect
* it also holds a CEagle object with the internal ship logic.
*/
class CShip {

	public:
		CShip (short int initposx, short int initposy);
		~CShip();
		void update (unsigned int timedelta);
		void draw (SDL_Surface *dstsurface);
		CEagle *eagle;

	private:
		/* shipsurface + flamesurface are drawed into surface
		* the surface rect is the shiprect and the flamerect under
		* it
		*/
		SDL_Surface *shipsurface;     /* for the ship shape */
		SDL_Surface *flamesurface;    /* for the flame */
		SDL_Surface *surface;         /* ship + flame */
		SDL_Surface *rotsurface;      /* ship + flame both rotated */
		SDL_Surface *clearsurface;    /* clear ship + flame */
		SDL_Surface *rotclearsurface; /* clear rotated ship + flame */
		SDL_Rect *shiprect;           /* ship surface rect within the total surface rect */
		SDL_Rect *flamerect;          /* flame surface rect within the total surface rect */
		SDL_Rect *rect;               /* the total surface rect */
		SDL_Rect *oldrect;            /* holds the last total rect for clearing it */

		/* draw the flame? */
		unsigned short drawflame = 0;

		/* the ship shape is defined as an array of vertex */
		const short int shapevertx[4] = {1, SHIP_SHAPE_W / 2, SHIP_SHAPE_W - 1, SHIP_SHAPE_W / 2};
		const short int shapeverty[4] = {SHIP_SHAPE_H - 1, 1, SHIP_SHAPE_H - 1, SHIP_SHAPE_H - 8};
};
