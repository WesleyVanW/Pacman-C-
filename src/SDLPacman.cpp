#include "SDLPacman.h"
#include <iostream>

namespace SDLPac {

	SDLPacman::SDLPacman(SDL_Renderer* gRenderer, SDL_Rect rect, char direction, float speed) : Pac::Pacman(direction, speed, rect.x/rect.w, rect.y/rect.h) {
		this->gTexture = NULL;
		this->gRenderer = gRenderer;
		this->rect = rect;
		this->animationCount = 0;
		this->pacmanWidth = 0;
		this->pacmanHeight = 0;
		this->visPositionX = 0;
		this->visPositionY = 0;

		//Load image at specified path
		SDL_Surface* loadedSurface = IMG_Load("pacman.png");
		SDL_Surface* loadedSurface2 = IMG_Load("pacman_open.png");
		if( loadedSurface == NULL || loadedSurface2 == NULL ) {
			std::cout << "Unable to load image %s! SDL_image Error: %s\n" << IMG_GetError() << std::endl;
		}
		else {
			//Create texture from surface pixels
			this->gTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
			this->gTexture2 = SDL_CreateTextureFromSurface(gRenderer, loadedSurface2);
			if( gTexture == NULL || gTexture2 == NULL) {
				std::cout << "Unable to create texture from %s! SDL Error: %s\n" << SDL_GetError() << std::endl;
			}
		}
		this->renderTexture = gTexture2;
		//Get rid of old loaded surface
		SDL_FreeSurface(loadedSurface);
		SDL_FreeSurface(loadedSurface2);
	}

	//visualizes pacman
	void SDLPacman::visualize() {
		if(renderTexture == gTexture && animationCount%5 == 0) {
			renderTexture = gTexture2;
			animationCount = 0;
		}
		else {
			renderTexture = gTexture;
		}
		visPositionX = round(positionX*pacmanWidth);
		visPositionY = round(positionY*pacmanHeight);
		rect = {visPositionX,visPositionY,pacmanWidth,pacmanHeight};
		switch (direction) {
			case 'l' :
				SDL_RenderCopyEx(gRenderer, renderTexture, NULL, &rect, 0, NULL, SDL_FLIP_HORIZONTAL);
				break;
			case 'r' :
				SDL_RenderCopyEx(gRenderer, renderTexture, NULL, &rect, 0, NULL, SDL_FLIP_NONE);
				break;
			case 'u' :
				SDL_RenderCopyEx(gRenderer, renderTexture, NULL, &rect, -90, NULL, SDL_FLIP_NONE);
				break;
			case 'd' :
				SDL_RenderCopyEx(gRenderer, renderTexture, NULL, &rect, 90, NULL, SDL_FLIP_NONE);
				break;
			case 'i' :
				SDL_RenderCopy(gRenderer, renderTexture, NULL, &rect);
				break;
		}
		animationCount += 1;
	}

	//sets pacman width and height
	void SDLPacman::setDimensions(int w, int h) {
		pacmanWidth = w;
		pacmanHeight = h;
	}

	SDLPacman::~SDLPacman() {
			SDL_DestroyTexture(gTexture);
			SDL_DestroyTexture(gTexture2);
			SDL_DestroyTexture(renderTexture);
	}




}


