#include "ship.hpp"


CShip::CShip (short int initposx, short int initposy) {

	/* rectangles init */
	shiprect = new SDL_Rect {initposx, initposy, SHIP_SHAPE_W, SHIP_SHAPE_H};
	shiprectclr = new SDL_Rect {0, 0, SHIP_SHAPE_W + 10, SHIP_SHAPE_H + 10};
	flamerect = new SDL_Rect {initposx, (short int)(initposy+FLAME_SHAPE_H), FLAME_SHAPE_W, FLAME_SHAPE_H};

	/* load the ship sprite */
	shipsprite = IMG_Load(SHIP_SPRITE);

	/* load the flame sprites */
	flamespritebig = IMG_Load(FLAME_SPRITE_BIG);
	flamespritemid = IMG_Load(FLAME_SPRITE_MID);
	flamespritelow = IMG_Load(FLAME_SPRITE_LOW);

	/* eagle init */
	eagle = new CEagle ((float)initposx, (float)initposy);

	/* flame off*/
	drawflame = 0;
}

void CShip::update (unsigned int timedelta) {

	/* update eagle data */
	eagle->update(timedelta);
	
	/* apply new position to ship and flame rect */
	shiprect->x = (unsigned short)eagle->getPosx();
	shiprect->y = -(unsigned short)eagle->getPosy();
	flamerect->x = (unsigned short)eagle->getPosx();
	flamerect->y = -(unsigned short)eagle->getPosy()+FLAME_SHAPE_H;


	/* apply new rotation to ship surface */
	shiprotsprite = rotozoomSurface(shipsprite, -eagle->getRawAngDeg(), 1.0, 0);

	/* apply rotation to flame surface */
	switch (eagle->getMainEngineStatus()) {
		case MAX_MAIN_THRUST:
			flamerotsprite = rotozoomSurface(flamespritebig, -eagle->getRawAngDeg(), 1.0, 0);
			flamerect->x -= flamerotsprite->w/2 - flamespritebig->w/2;
			flamerect->y -= flamerotsprite->h/2 - flamespritebig->h/2;
			break;
		case MID_MAIN_THRUST:
			flamerotsprite = rotozoomSurface(flamespritemid, -eagle->getRawAngDeg(), 1.0, 0);
			flamerect->x -= flamerotsprite->w/2 - flamespritemid->w/2;
			flamerect->y -= flamerotsprite->h/2 - flamespritemid->h/2;
			break;
		case LOW_MAIN_THRUST:
			flamerotsprite = rotozoomSurface(flamespritelow, -eagle->getRawAngDeg(), 1.0, 0);
			flamerect->x -= flamerotsprite->w/2 - flamespritelow->w/2;
			flamerect->y -= flamerotsprite->h/2 - flamespritelow->h/2;
			break;
		default:
			break;
	}

	/* make the surfaces rotate around its center */
	shiprect->x -= shiprotsprite->w/2 - shipsprite->w/2;
	shiprect->y -= shiprotsprite->h/2 - shipsprite->h/2;
}

void CShip::clear(SDL_Surface *dst) {
	SDL_FillRect(dst, shiprect, SDL_MapRGB(dst->format, 0, 0, 0));
	SDL_FillRect(dst, flamerect, SDL_MapRGB(dst->format, 0, 0, 0));
}

void CShip::draw (SDL_Surface *dst) {
	if (drawflame = eagle->getMainEngineStatus()) {
		SDL_BlitSurface(flamerotsprite, NULL, dst, flamerect);
	}
	SDL_BlitSurface(shiprotsprite, NULL, dst, shiprect);
}
