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

void drawStars(SDL_Surface *s) {
	int posx, posy;
	int starposxlist[STAR_NUM];
	int starposylist[STAR_NUM];
	time_t timer;

	srand ((unsigned int)time(&timer));
    
	for (int i=0; i<STAR_NUM; i++) {
		starposxlist[i] = rand() % s->w;
		starposylist[i] = rand() % s->h;
	}

	SDL_LockSurface(s);

	for (int i=0; i<STAR_NUM; i++) {
		posx = starposxlist[i];
		posy = starposylist[i];
		int bpp = s->format->BytesPerPixel;
		Uint8 *p = (Uint8 *)s->pixels + posy * s->pitch + posx * bpp;
		*(Uint32 *)p = STAR_COLOR;
	}

	SDL_UnlockSurface(s);
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

void showShipInfo(SDL_Surface *ps, CShip s, TTF_Font *pf, SDL_Color c) {

	char *paux;
	char buff[100];
	char shipinfostr[200];
	SDL_Surface *textsurf;
	s.eagle->getShipInfoStr(shipinfostr);
	SDL_Rect dstrect = {0, 0, 0, 0};
	paux = strtok(shipinfostr, "\n");
	clearSurface(ps);
	while (paux != NULL) {
		strcpy(buff, paux);
		paux = strtok(NULL,"\n");
		textsurf = TTF_RenderText_Solid(pf, buff, c);
		SDL_BlitSurface(textsurf, NULL, ps, &dstrect);
		dstrect.y += textsurf->h;
	}
}

void updateScreen(SDL_Surface *dst, SDL_Surface *ss, SDL_Surface *is,SDL_Surface *bs, SDL_Rect *sr, SDL_Rect *ir, SDL_Rect *br) {
	SDL_BlitSurface(bs, NULL, dst, br);
	SDL_BlitSurface(ss, NULL, dst, sr);
	SDL_BlitSurface(is, NULL, dst, ir);
}
