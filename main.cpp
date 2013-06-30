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
	int starlistx[STAR_NUM];
	int starlisty[STAR_NUM];
	int grndlistx[MAX_PEAKS];
	int grndlisty[MAX_PEAKS];
	int grndlistlength;
	TTF_Font *font;
	char shipinfostr[200];
	char buff[100];
	unsigned int timedelta, oldtime, currenttime;
	short text_posx = 0, text_posy = 670;
	unsigned short running = 1;


	/* initialize screen, surfaces and fonts */
	if ((screen = initScreen()) == NULL) {
		printf("%s\n", SDL_GetError());
		SDL_Quit();
		return -1;
	}

	if ((infosurface = initSurface(inforect)) == NULL) {
		printf("%s\n", SDL_GetError());
		SDL_Quit();
		return -1;
	}

	if ((clearSurface(screen)) != 0) {
		printf("%s\n", SDL_GetError());
		SDL_Quit();
		return -1;
	}

	if ((clearSurface(infosurface)) != 0) {
	  	printf("%s\n", SDL_GetError());
		SDL_Quit();
		return -1;
	}

	if ((font = initFont()) == NULL) {
		printf("%s\n", SDL_GetError());
		SDL_Quit();
		return -1;
	}

	/* draw the stars an the background surface */
	genStars(starlistx, starlisty);
	drawStars(screen, starlistx, starlisty);

	/* draw the ground */
	genGround(grndlistx, grndlisty, &grndlistlength);
	drawGround(screen, grndlistx, grndlisty, grndlistlength);

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

		/* redraw the ship on the screen */
		ship.clear(screen);
		drawStars(screen, starlistx, starlisty);
		drawGround(screen, grndlistx, grndlisty, grndlistlength);
		ship.draw(screen);

		/* blit ship info on the screen */
		//showShipInfo(infosurface, ship, font, textcolor);

		/* draw surfaces into screen surface */
//		updateScreen(screen, shipsurface, infosurface, backsurface, &shiprect, &inforect, &backrect);

		SDL_Flip(screen);
	}

	/* free surfaces and quit SDL */
	SDL_FreeSurface(screen);
	SDL_FreeSurface(infosurface);
	SDL_Quit();
}
