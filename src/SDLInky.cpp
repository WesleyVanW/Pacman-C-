#include "SDLInky.h"

namespace SDLPac {

	SDLInky::SDLInky(SDL_Renderer* gRenderer, SDL_Rect rect, char direction, float speed, int homeTileX, int homeTileY, int startPosX, int startPosY, Pac::Timer* t) : Pac::Ghost(direction, speed, rect.x/rect.w, rect.y/rect.h, homeTileX, homeTileY, startPosX, startPosY, t) {
		this->gRenderer = gRenderer;
		this->rect = rect;
		this->ghostWidth = 0;
		this->ghostHeight = 0;
		this->visPositionX = 0;
		this->visPositionY = 0;
		this->animationCount = 0;

		//Load image at specified path
		SDL_Surface* loadedSurface = IMG_Load("inky.png");
		SDL_Surface* loadedSurface2 = IMG_Load("frightened.png");
		SDL_Surface* loadedSurface3 = IMG_Load("eyes.png");
		if( loadedSurface == NULL || loadedSurface2 == NULL || loadedSurface3 == NULL ) {
			std::cout << "Unable to load image %s! SDL_image Error: %s\n" << IMG_GetError() << std::endl;
		}
		else {
			//Create texture from surface pixels
			this->gTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
			this->gTexture2 = SDL_CreateTextureFromSurface(gRenderer, loadedSurface2);
			this->gTexture3 = SDL_CreateTextureFromSurface(gRenderer, loadedSurface3);
			if( gTexture == NULL || gTexture2 == NULL || gTexture3 == NULL) {
				std::cout << gRenderer << std::endl;
				std::cout << "Unable to create texture from %s! SDL Error: %s\n" << SDL_GetError() << std::endl;
			}
		}
		this->renderTexture = gTexture;
		//Get rid of old loaded surface
		SDL_FreeSurface(loadedSurface);
		SDL_FreeSurface(loadedSurface2);
		SDL_FreeSurface(loadedSurface3);
	}

	//visualizes inky
	void SDLInky::visualize() {
		visPositionX = round(positionX*ghostWidth);
		visPositionY = round(positionY*ghostHeight);
		rect = {visPositionX,visPositionY,ghostWidth,ghostHeight};
		if(frightened && !eaten) {
			renderTexture = gTexture2;
			if (getTimeFrightened() > ((frightenTime)/2)) {
				blink(renderTexture);
			}
		}
		else if (frightened && eaten){
			renderTexture = gTexture3;
			if (getTimeFrightened() > ((frightenTime)/2)) {
				blink(renderTexture);
			}
		}
		else {
			renderTexture = gTexture;
		}
		SDL_RenderCopy(gRenderer, renderTexture, NULL, &rect);
	}

	//makes inky blink when almost done being frightened
	void SDLInky::blink(SDL_Texture* thisTexture) {
		if(renderTexture == thisTexture && animationCount%5 == 0) {
			renderTexture = gTexture;
			animationCount = 0;
		}
		else {
			renderTexture = thisTexture;
		}
		animationCount += 1;

	}

	//sets the width and height of inky
	void SDLInky::setDimensions(int w, int h) {
		ghostWidth = w;
		ghostHeight = h;
	}

	SDLInky::~SDLInky() {
		SDL_DestroyTexture(gTexture);
		SDL_DestroyTexture(gTexture2);
		SDL_DestroyTexture(gTexture3);
		SDL_DestroyTexture(renderTexture);
	}

}
