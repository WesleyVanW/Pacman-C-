#ifndef SDLPINKY_H_
#define SDLPINKY_H_

#include <SDL.h>
#include <SDL_image.h>
#include "Ghost.h"

namespace SDLPac {
	class SDLPinky : public Pac::Ghost{
	public:
		SDLPinky(SDL_Renderer* gRenderer, SDL_Rect rect, char direction, float speed, int homeTileX, int homeTileY, int startPosX, int startPosY, Pac::Timer* t);
		virtual ~SDLPinky();
		void visualize();
		void blink(SDL_Texture* thisTexture);
		void setDimensions(int w, int h);

	private :
		SDL_Renderer* gRenderer;
		SDL_Texture* gTexture;
		SDL_Texture* gTexture2;
		SDL_Texture* gTexture3;
		SDL_Texture* renderTexture;
		SDL_Rect rect;
		int ghostWidth;
		int ghostHeight;
		int visPositionX;
		int visPositionY;
		int animationCount;
	};
}



#endif /* SDLPINKY_H_ */
