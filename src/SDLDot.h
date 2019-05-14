#ifndef SDLDOT_H_
#define SDLDOT_H_

#include <SDL.h>
#include <SDL_Image.h>
#include <iostream>
#include "staticEntity.h"

namespace SDLPac {
	class SDLDot : public Pac::staticEntity {
		public :
			SDLDot(SDL_Renderer* gRenderer, int x, int y, int w, int h, int score) ;
			void visualize();
			int eaten();
			void clearEaten();
			virtual ~SDLDot();
		private :
			SDL_Renderer* gRenderer;
			SDL_Texture* gTexture;
			SDL_Rect rect;
			int visualizeable;
	};
}



#endif /* SDLDOT_H_ */
