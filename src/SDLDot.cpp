#include "SDLDot.h"

namespace SDLPac {

	SDLDot::SDLDot(SDL_Renderer* gRenderer, int x, int y, int w, int h, int score) : Pac::staticEntity(x,y,score) {
		this->gTexture = NULL;
		this->gRenderer = gRenderer;
		this->rect = {round((x*w)+w/4),round((y*h)+(h/4)),w/2,h/2};
		this->visualizeable = 1;

		//Load image at specified path
		SDL_Surface* loadedSurface = IMG_Load("dot.png");
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

	//visualizes dot if dot is visualizable
	void SDLDot::visualize() {
		if(visualizeable == 1) {
			SDL_RenderCopy(gRenderer, gTexture, NULL, &rect);
		}
	}

	//set dot as eaten and returns the score for eating this dot
	int SDLDot::eaten() {
		int score = getScore();
		setEaten();
		visualizeable = 0;
		return score;
	}

	//sets dot as eatable
	void SDLDot::clearEaten() {
		removeEaten();
		visualizeable = 1;
	}

	SDLDot::~SDLDot() {
		SDL_DestroyTexture(gTexture);
	}
}





