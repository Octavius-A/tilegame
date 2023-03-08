#include "handleInputs.h"

InputState gInputState = {
	false
};

void updateInputState() {
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		switch (event.type) {
		case SDL_QUIT: gInputState.quit = true; break;
		case SDL_KEYDOWN:
			switch (event.key.keysym.sym) {
			case SDLK_q: gInputState.quit = true; break;
			case SDLK_r: gInputState.r = true; break;
			case SDLK_UP: gInputState.upArrow = true; break;
			case SDLK_DOWN: gInputState.downArrow = true; break;
			case SDLK_RIGHT: gInputState.rightArrow = true; break;
			case SDLK_LEFT: gInputState.leftArrow = true; break;
			default: break;
			}
		default: break;
		}
	}
}