#ifndef SDLPACMAN_H_
#define SDLPACMAN_H_

#include <SDL.h>
#include <SDL_image.h>
#include "Pacman.h"

namespace SDLPac {
	class SDLPacman : public Pac::Pacman {
	public:
		SDLPacman(SDL_Renderer* gRenderer, SDL_Rect rect, char direction, float speed);
		virtual ~SDLPacman();
		void visualize();
		void setDimensions(int w, int h);

	private :
		SDL_Renderer* gRenderer;
		SDL_Texture* gTexture;
		SDL_Texture* gTexture2;
		SDL_Texture* renderTexture;
		SDL_Rect rect;
		int animationCount;
		int pacmanWidth;
		int pacmanHeight;
		int visPositionX;
		int visPositionY;
	};
}

#endif /* SDLPACMAN_H_ */
