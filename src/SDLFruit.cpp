#include "SDLFruit.h"

namespace SDLPac {

	SDLFruit::SDLFruit(SDL_Renderer* gRenderer, int x, int y, int w, int h, int score) : Pac::staticEntity(x, y, score) {
		this->gTexture = NULL;
		this->gRenderer = gRenderer;
		this->rect = {round(x*w),round(y*h),w,h};
		this->visualizeable = 1;

		//Load image at specified path
		SDL_Surface* loadedSurface = IMG_Load("fruit.png");
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

	//visualizes fruit
	void SDLFruit::visualize() {
		if(visualizeable == 1) {
			SDL_RenderCopy(gRenderer, gTexture, NULL, &rect);
		}
	}

	//sets fruit as eaten and returns the score for eating this fruit
	int SDLFruit::eaten() {
		int score = getScore();
		setEaten();
		visualizeable = 0;
		return score;
	}

	//sets fruit as eatable
	void SDLFruit::clearEaten() {
		removeEaten();
		visualizeable = 1;
	}

	SDLFruit::~SDLFruit() {
		SDL_DestroyTexture(gTexture);
	}
}




