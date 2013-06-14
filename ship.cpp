#include "ship.hpp"


CShip::CShip (short int initposx, short int initposy) {

	/* rectangles init */
	shiprect = new SDL_Rect {0, 0, SHIP_SHAPE_W, SHIP_SHAPE_H};
	flamerect = new SDL_Rect {0, SHIP_SHAPE_H-FLAME_OVERLAP, FLAME_SHAPE_W, FLAME_SHAPE_H};
	rect = new SDL_Rect {initposx, initposy, SHIP_SHAPE_W, SHIP_SHAPE_H + FLAME_SHAPE_H};
	oldrect = new SDL_Rect {initposx, initposy, SHIP_SHAPE_W, SHIP_SHAPE_H};

	/* ship surface init */
	shipsurface = SDL_CreateRGBSurface(0, shiprect->w, shiprect->h, 32, 0, 0, 0, 0);
	SDL_FillRect(shipsurface, NULL, SDL_MapRGBA(shipsurface->format, 0, 0, 1, 0));
	aapolygonRGBA(shipsurface, shapevertx, shapeverty, 4, 255, 255, 255, 255);

	/* flame surface under the ship init */
	flamesurface = SDL_CreateRGBSurface(0, flamerect->w, flamerect->h, 32, 0, 0, 0, 0);
	SDL_FillRect(flamesurface, NULL, SDL_MapRGBA(flamesurface->format, 0, 0, 1, 0));
	aatrigonRGBA(flamesurface, 5, 0, flamerect->w-5, 0, flamerect->w / 2, flamerect->h, 255,0,0,255);

	/* the final surface will contain shipsurface + flamesurface */
	surface = SDL_CreateRGBSurface(0, rect->w, rect->h, 32, 0, 0, 0, 0);
	SDL_FillRect(surface, NULL, SDL_MapRGBA(surface->format, 0, 0, 1, 0));

	/* surface for clearing the final surface (is a little bit bigger) */
	clearsurface = SDL_CreateRGBSurface(0, rect->w + CLEAR_SURFACE_OFFSET, rect->h + CLEAR_SURFACE_OFFSET, 32, 0, 0, 0, 0);
	SDL_FillRect(clearsurface, NULL, SDL_MapRGBA(clearsurface->format, 0, 0, 1, 0));

	/* eagle init */
	eagle = new CEagle ((float)initposx, (float)initposy);
}

CShip::~CShip() {
//	SDL_FreeSurface(shipsurface);
//	SDL_FreeSurface(flamesurface);
//	SDL_FreeSurface(surface);
//	SDL_FreeSurface(rotsurface);
//	SDL_FreeSurface(clearsurface);
//	SDL_FreeSurface(rotclearsurface);
}

void CShip::update (unsigned int timedelta) {

	/* save the old position for clearing the surface */
	oldrect->x = rect->x;
	oldrect->y = rect->y;

	/* offset the oldrect to avoid trailing pixels */
	/* this will affect the blitting of the clearing surface */
	oldrect->x -= CLEAR_SURFACE_OFFSET / 2;
	oldrect->y -= CLEAR_SURFACE_OFFSET / 2;

	/* rotate clear surface before with old angle */
	rotclearsurface = rotozoomSurface(clearsurface, -eagle->getRawAngDeg(), 1.0, 0);

	/* update eagle data */
	eagle->update(timedelta);
	drawflame = eagle->getMainEngineStatus();

	/* reblit the total surface */
	SDL_BlitSurface(clearsurface, NULL, surface, NULL);
    if (drawflame) {
		SDL_BlitSurface(flamesurface, NULL, surface, flamerect);
	}
	SDL_BlitSurface(shipsurface, NULL, surface, shiprect);

	/* apply new position to total surface */
	rect->x = (unsigned short)eagle->getPosx();
	rect->y = -(unsigned short)eagle->getPosy();


	/* apply new rotation to the total surface */
	rotsurface = rotozoomSurface(surface, -eagle->getRawAngDeg(), 1.0, 0);

	/* make the surface rotate around its center */
	rect->x -= rotsurface->w/2 - surface->w/2;
	rect->y -= rotsurface->h/2 - surface->h/2;
}

void CShip::draw (SDL_Surface *dstsurface) {
	SDL_BlitSurface(rotclearsurface, NULL, dstsurface, oldrect);
	SDL_BlitSurface(rotsurface, NULL, dstsurface, rect);
}
