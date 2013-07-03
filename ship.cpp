#include "ship.hpp"


CShip::CShip (short int initposx, short int initposy) {

	/* rectangles init */
	shiprect = new SDL_Rect {initposx, initposy, SHIP_SHAPE_W, SHIP_SHAPE_H};
	shiprectclr = new SDL_Rect {0, 0, SHIP_SHAPE_W + 10, SHIP_SHAPE_H + 10};

	/* load the ship sprites */
	ssprite_noflame = IMG_Load(SHIP_SPRITE_NO_FLAME);
	ssprite_bigflame = IMG_Load(SHIP_SPRITE_BIG_FLAME);
	ssprite_midflame = IMG_Load(SHIP_SPRITE_MID_FLAME);
	ssprite_lowflame = IMG_Load(SHIP_SPRITE_LOW_FLAME);
	
	/* the current ship sprite */
	ssprite = ssprite_noflame;
	
	/* eagle init */
	eagle = new CEagle ((float)initposx, (float)initposy);
}

void CShip::update (unsigned int timedelta) {

	/* update eagle data */
	eagle->update(timedelta);
	
	/* apply new position to ship and flame rect */
	shiprect->x = (unsigned short)eagle->getPosx();
	shiprect->y = -(unsigned short)eagle->getPosy();

	/* set the current active sprite */
	switch (eagle->getMainEngineStatus()) {
		case OFF_MAIN_THRUST:
			ssprite = ssprite_noflame;
			break;
		case MAX_MAIN_THRUST:
			ssprite = ssprite_bigflame;
			break;
		case MID_MAIN_THRUST:
			ssprite = ssprite_midflame;
			break;
		case LOW_MAIN_THRUST:
			ssprite = ssprite_lowflame;
			break;
		default:
			break;
	}
	
	/* apply new rotation to ship surface */
	shiprotsprite = rotozoomSurface(ssprite, -eagle->getRawAngDeg(), 1.0, 0);
	
	/* make the surfaces rotate around its center */
	shiprect->x -= shiprotsprite->w/2 - ssprite->w/2;
	shiprect->y -= shiprotsprite->h/2 - ssprite->h/2;
}

void CShip::clear(SDL_Surface *dst) {
	SDL_FillRect(dst, shiprect, SDL_MapRGB(dst->format, 0, 0, 0));
}

void CShip::draw (SDL_Surface *dst) {
	SDL_BlitSurface(shiprotsprite, NULL, dst, shiprect);
}
