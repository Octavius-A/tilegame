#include "handleInputs.h"

InputState gInputState = { false };

void updateInputState() {
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		switch (event.type) {
		case SDL_QUIT: gInputState.quit = true; break;
		case SDL_KEYDOWN:
			switch (event.key.keysym.sym) {
			//case SDLK_q:		gInputState.quit = true; break;
			case SDLK_r:		gInputState.r = true; break;
			case SDLK_UP:		gInputState.upArrow = true; break;
			case SDLK_DOWN:		gInputState.downArrow = true; break;
			case SDLK_RIGHT:	gInputState.rightArrow = true; break;
			case SDLK_LEFT:		gInputState.leftArrow = true; break;
			case SDLK_ESCAPE:	gInputState.esc = true; break;
			case SDLK_RETURN:	gInputState.rtrn = true; break;
			case SDLK_h:		gInputState.h = true; break;
			case SDLK_j:		gInputState.j = true; break;
			case SDLK_k:		gInputState.k = true; break;
			case SDLK_l:		gInputState.l = true; break;
			case SDLK_y:		gInputState.y = true; break;
			case SDLK_u:		gInputState.u = true; break;
			case SDLK_b:		gInputState.b = true; break;
			case SDLK_n:		gInputState.n = true; break;
			default: break;
			} break;
		case SDL_KEYUP:
			switch (event.key.keysym.sym) {
			case SDLK_r:		gInputState.r = false; break;
			case SDLK_UP:		gInputState.upArrow = false; break;
			case SDLK_DOWN:		gInputState.downArrow = false; break;
			case SDLK_RIGHT:	gInputState.rightArrow = false; break;
			case SDLK_LEFT:		gInputState.leftArrow = false; break;
			case SDLK_ESCAPE:	gInputState.esc = false; break;
			case SDLK_RETURN:	gInputState.rtrn = false; break;
			case SDLK_h:		gInputState.h = false; break;
			case SDLK_j:		gInputState.j = false; break;
			case SDLK_k:		gInputState.k = false; break;
			case SDLK_l:		gInputState.l = false; break;
			case SDLK_y:		gInputState.y = false; break;
			case SDLK_u:		gInputState.u = false; break;
			case SDLK_b:		gInputState.b = false; break;
			case SDLK_n:	gInputState.n = false; break;
			default: break;
			} break;
		default: break;
		}
	}
}