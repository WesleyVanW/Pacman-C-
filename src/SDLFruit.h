#ifndef SDLFRUIT_H_
#define SDLFRUIT_H_

#include <SDL.h>
#include <SDL_Image.h>
#include "staticEntity.h"
#include <iostream>

namespace SDLPac {
	class SDLFruit : public Pac::staticEntity {
		public :
			SDLFruit(SDL_Renderer* gRenderer, int x, int y, int w, int h, int score);
			void visualize();
			int eaten();
			void clearEaten();
			virtual ~SDLFruit();
		private :
			SDL_Renderer* gRenderer;
			SDL_Texture* gTexture;
			SDL_Rect rect;
			int visualizeable;
	};
}

#endif /* SDLFRUIT_H_ */
