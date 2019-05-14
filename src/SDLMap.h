#ifndef SDLMAP_H_
#define SDLMAP_H_

#include <SDL.h>
#include <SDL_Image.h>
#include <SDL_ttf.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "Map.h"

namespace SDLPac {
	class SDLMap : public Pac::Map {
		public :
			SDLMap(SDL_Renderer* gRenderer,SDL_Window* gWindow,Pac::abstractFactory* h,Pac::movingEntity* p,Pac::movingEntity* b, Pac::movingEntity* n, Pac::movingEntity* in, Pac::movingEntity* c,Pac::Timer* t, std::string map, int tileWidth, int tileHeight);
			void visualize();
			void visualizeLives();
			void visualizeScore();
			void visualizeLevel();
			void visualizeTime();
			void setWindowSize();
			virtual ~SDLMap();
		private :
			SDL_Renderer* gRenderer;
			SDL_Window* gWindow;
			SDL_Texture* gTexture;
			SDL_Texture* gTexture2;
			SDL_Rect rect;
			SDL_Color textColor;
			TTF_Font* font;
			SDL_Surface* text_surface ;
};
}

#endif /* SDLMAP_H_ */
