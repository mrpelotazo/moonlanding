#include "moonlanding.hpp"

SDL_Surface *initScreen() {
	if(SDL_Init(SDL_INIT_VIDEO) < 0) {
		return NULL;
	}
	
	return SDL_SetVideoMode(SCREEN_W, SCREEN_H, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
}

TTF_Font *initFont() {
	if (TTF_Init() != 0) {
		return NULL;
	}

	return TTF_OpenFont(FONT_PATH, FONT_SIZE);
}

SDL_Surface *initSurface(SDL_Rect r) {
	return SDL_CreateRGBSurface(SDL_HWSURFACE, r.w, r.h, 32, 0, 0, 0, 0);
}

void genStars(int slx[], int sly[]) {
	time_t timer;

	srand ((unsigned int)time(&timer));
    
	for (int i=0; i<STAR_NUM; i++) {
		slx[i] = rand() % SCREEN_W;
		sly[i] = rand() % SCREEN_H;
	}
}

void drawStars(SDL_Surface *s, int slx[], int sly[]) {
	int posx, posy;

	SDL_LockSurface(s);

	for (int i=0; i<STAR_NUM; i++) {
		posx = slx[i];
		posy = sly[i];
		int bpp = s->format->BytesPerPixel;
		Uint8 *p = (Uint8 *)s->pixels + posy * s->pitch + posx * bpp;
		*(Uint32 *)p = STAR_COLOR;
	}

	SDL_UnlockSurface(s);
}

void genGround(int glx[], int gly[], int *length) {
	/* generate the x list */
	int last_x = 0;
	int x_aux;
	int pos = 0;

	srand(time(NULL));

	glx[pos] = 0;
	pos++;

	while ((last_x < (SCREEN_W / 2) - 1) && (pos < MAX_PEAKS_PER_SIDE)) {
		x_aux = rand() % (SCREEN_W / 2);

		while (x_aux <= last_x) {
			x_aux = rand() % (SCREEN_W / 2);
		}

		glx[pos] = x_aux;
		last_x = x_aux;
		pos++;
	}

	glx[pos] = last_x + LAND_POS_W;
	int land_posx_in_list = pos - 1;
	last_x = last_x + LAND_POS_W;
	pos++;

	while ((last_x < SCREEN_W - 1) && (pos < MAX_PEAKS_PER_SIDE * 2 + 2)) {
		x_aux = rand() % (SCREEN_W);

		while (x_aux <= last_x) {
			x_aux = rand() % (SCREEN_W);
		}

		glx[pos] = x_aux;
		last_x = x_aux;
		pos++;
	}

	glx[pos] = SCREEN_W;
	pos++;
	int x_elems_num = pos;
	/* generate the y list
	 * the number of peak elements depends on the previously generated x
	 * position elements */
	for (int i=0; i<=land_posx_in_list; i++) {
		gly[i] = (rand() % MIN_GRND_H) + MAX_GRND_H;
	}

	gly[land_posx_in_list + 1] = gly[land_posx_in_list];

	for (int i=land_posx_in_list + 2 ; i<x_elems_num; i++) {
		gly[i] = (rand() % MIN_GRND_H) + MAX_GRND_H;
	}

	/* return the list length */
	*length = x_elems_num;
}

void drawGround(SDL_Surface *dst, int glx[], int gly[], int length) {
	for (int i=0; i<length-2; i++) {
		lineRGBA(dst, glx[i], gly[i], glx[i+1], gly[i+1],255,255,255,255);
	}
}

int clearSurface(SDL_Surface *ps) {
	return SDL_FillRect(ps, NULL, SDL_MapRGBA(ps->format, 0, 0, 0, 0));
}

void eventHandler(SDL_Event e, CShip s, unsigned short *r) {
	switch (e.type) {
		case SDL_KEYDOWN:
			switch (e.key.keysym.sym) {
				case SDLK_LEFT:
					s.eagle->actRotLeft();
					break;

				case SDLK_RIGHT:
					s.eagle->actRotRight();
					break;

				case SDLK_1:
					s.eagle->actMainEngine(0);
					break;

				case SDLK_2:
					s.eagle->actMainEngine(1);
					break;

				case SDLK_3:
					s.eagle->actMainEngine(2);
					break;

				case SDLK_q:
					*r = 0;
					break;

				default:
					break;
			}
			break;

		case SDL_KEYUP:
			switch (e.key.keysym.sym) {
				case SDLK_LEFT:
					s.eagle->deactRotLeft();
					break;

				case SDLK_RIGHT:
					s.eagle->deactRotRight();
					break;

				case SDLK_1: case SDLK_2: case SDLK_3:
					s.eagle->deactMainEngine();
					break;

				default:
					break;
			}
			break;
					
		default:
			break;
	}
}

void showShipInfo(SDL_Surface *dst, CShip s, TTF_Font *pf, SDL_Color c) {

	char *paux;
	char buff[100];
	char shipinfostr[200];
	SDL_Surface *textsurf;
	s.eagle->getShipInfoStr(shipinfostr);
	SDL_Rect dstrect = {0, 0, 0, 0};
	paux = strtok(shipinfostr, "\n");
	clearSurface(dst);
	while (paux != NULL) {
		strcpy(buff, paux);
		paux = strtok(NULL,"\n");
		textsurf = TTF_RenderText_Solid(pf, buff, c);
		SDL_BlitSurface(textsurf, NULL, dst, &dstrect);
		dstrect.y += textsurf->h;
	}
}

void updateScreen(SDL_Surface *dst, SDL_Surface *ss, SDL_Surface *is, SDL_Rect *sr, SDL_Rect *ir) {
	SDL_BlitSurface(ss, NULL, dst, sr);
	SDL_BlitSurface(is, NULL, dst, ir);
}
