#include <string>
#include <SDL/SDL.h>
#include "moonlanding.hpp"

using namespace std;

int main(int argc, char *argv[]) {

	CShip ship(400, 0);
	SDL_Event event;
	SDL_Surface *screen, *shipsurface, *infosurface, *backsurface;
	SDL_Color textcolor = {255, 255, 255};
	SDL_Rect shiprect = {0, 0, SHIP_SURFACE_W, SHIP_SURFACE_H};
	SDL_Rect inforect = {0, SHIP_SURFACE_H, INFO_SURFACE_W, INFO_SURFACE_H};
	SDL_Rect backrect = {0, 0, SHIP_SURFACE_W, SHIP_SURFACE_H};

	TTF_Font *font;
	char shipinfostr[200];
	char buff[100];
	unsigned int timedelta, oldtime, currenttime;
	short text_posx = 0, text_posy = 670;
	unsigned short running = 1;


	/* initialize screen, surfaces and fonts */
	if ((screen = initScreen()) == NULL) {
		SDL_Quit();
		return -1;
	}

	if ((shipsurface = initSurface(shiprect)) == NULL) {
		SDL_Quit();
		return -1;
	}

	if ((infosurface = initSurface(inforect)) == NULL) {
		SDL_Quit();
		return -1;
	}

	if ((backsurface = initSurface(backrect)) == NULL) {
		SDL_Quit();
		return -1;
	}

	if ((clearSurface(screen)) != 0) {
		SDL_Quit();
		return -1;
	}

	if ((clearSurface(shipsurface)) != 0) {
		SDL_Quit();
		return -1;
	}

	if ((clearSurface(infosurface)) != 0) {
		SDL_Quit();
		return -1;
	}

	if ((clearSurface(backsurface)) != 0) {
		SDL_Quit();
		return -1;
	}

	if ((font = initFont()) == NULL) {
		SDL_Quit();
		return -1;
	}

	/* draw the stars an the background surface */
	drawStars(backsurface);

	currenttime = SDL_GetTicks();

	/* Main loop */
	while (running) {

		/* Update time delta */
		oldtime = currenttime;
		currenttime = SDL_GetTicks();
		timedelta = currenttime - oldtime;

		/* process event from keyboard */
		if (SDL_PollEvent(&event)) {
			eventHandler(event, ship, &running);
		}

		/* update ship data */
		ship.update(timedelta);

		/* draw the ship into the screen surface */
		ship.draw(shipsurface);

		/* blit ship info on the screen */
		showShipInfo(infosurface, ship, font, textcolor);

		/* draw surfaces into screen surface */
		updateScreen(screen, shipsurface, infosurface, backsurface, &shiprect, &inforect, &backrect);

		SDL_Flip(screen);
	}

	/* free surfaces and quit SDL */
	SDL_FreeSurface(screen);
	SDL_FreeSurface(shipsurface);
	SDL_FreeSurface(infosurface);
	SDL_FreeSurface(backsurface);
	SDL_Quit();
}
