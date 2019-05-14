
#include "SDLWall.h"

namespace SDLPac {

	SDLWall::SDLWall(SDL_Renderer* gRenderer, int x, int y, int w, int h, int score) : Pac::staticEntity(x,y,score) {
		this->gTexture = NULL;
		this->gRenderer = gRenderer;
		this->rect = {round(x*w),round(y*h),w,h};

		//Load image at specified path
		SDL_Surface* loadedSurface = IMG_Load("wallTile.png");
		if( loadedSurface == NULL ) {
			std::cout << "Unable to load image %s! SDL_image Error: %s\n" << IMG_GetError() << std::endl;
		}
		else {
			//Create texture from surface pixels
			gTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
			if( gTexture == NULL ) {
				std::cout << gRenderer << std::endl;
				std::cout << "Unable to create texture from %s! SDL Error: %s\n" << SDL_GetError() << std::endl;
			}
		}
		//Get rid of old loaded surface
		SDL_FreeSurface(loadedSurface);
	}

	//visualizes wall
	void SDLWall::visualize() {
		SDL_RenderCopy(gRenderer, gTexture, NULL, &rect);
	}

	SDLWall::~SDLWall() {
		SDL_DestroyTexture(gTexture);
	}
}
