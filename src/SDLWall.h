#ifndef SDLWALL_H_
#define SDLWALL_H_

#include <SDL.h>
#include <SDL_Image.h>
#include <iostream>
#include "staticEntity.h"

namespace SDLPac {
	class SDLWall : public Pac::staticEntity {
		public :
			SDLWall(SDL_Renderer* gRenderer, int x, int y, int w, int h, int score);
			void visualize();
			virtual ~SDLWall();
		private :
			SDL_Renderer* gRenderer;
			SDL_Texture* gTexture;
			SDL_Rect rect;
	};
}


#endif /* SDLWALL_H_ */
