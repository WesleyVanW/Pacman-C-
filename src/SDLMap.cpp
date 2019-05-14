#include "SDLMap.h"

namespace SDLPac {


	SDLMap::SDLMap(SDL_Renderer* gRenderer, SDL_Window* gWindow, Pac::abstractFactory* h,Pac::movingEntity* p, Pac::movingEntity* b, Pac::movingEntity* n, Pac::movingEntity* in, Pac::movingEntity* c,Pac::Timer* t,std::string map, int tileWidth, int tileHeight) : Pac::Map(h,p,b,n,in,c,t,map, tileWidth, tileHeight){
		this->gRenderer = gRenderer;
		this->gWindow = gWindow;
		//Load image at specified path
		SDL_Surface* loadedSurface = IMG_Load("pacman.png");
		if( loadedSurface == NULL) {
			std::cout << "Unable to load image %s! SDL_image Error: %s\n" << IMG_GetError() << std::endl;
		}
		else {
			//Create texture from surface pixels
			this->gTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
			if( gTexture == NULL) {
				  std::cout << "Unable to create texture from %s! SDL Error: %s\n" << SDL_GetError() << std::endl;
			}
		}
		std::string text = "Score : " + std::to_string(score) ;
		textColor = {255,255,0};
		font = TTF_OpenFont("emulogic.ttf", 26);
		gTexture2 = NULL; // our font-texture
		// check to see that the font was loaded correctly
		if (font == NULL) {
			std::cout << "Failed the load the font!\n" << std::endl;
			std::cout << "SDL_TTF Error: " << TTF_GetError() << "\n" << std::endl;
		}
		else {
			// now create a surface from the font
			text_surface = TTF_RenderText_Solid(font, text.c_str(), textColor);
			// render the text surface
			if (text_surface == NULL) {
				std::cout << "Failed to render text surface!\n";
				std::cout<< "SDL_TTF Error: " << TTF_GetError() << "\n" << std::endl;
			}
			else {
				// create a texture from the surface
				gTexture2 = SDL_CreateTextureFromSurface(gRenderer, text_surface);

				if (gTexture2 == NULL) {
					std::cout << "Unable to create texture from rendered text!\n";
				}
			}
		}
		//Get rid of old loaded surface
		SDL_FreeSurface(loadedSurface);
		SDL_FreeSurface(text_surface);

	}

	/*
	 * Sets the SDL window size so that it will visualize the whole
	 * playing field.
	 */

	void SDLMap::setWindowSize() {
		SDL_SetWindowSize(gWindow, screenWidth, screenHeight + 2*tileHeight);
	}

	/*
	 * Loop through the different object arrays and visualize each object to render the map.
	 */

	void SDLMap::visualize() {
		for(int i=0; i<wallCount; i++) {
			wallObjects[i]->visualize();
		}
		for(int j=0; j<dotCount; j++) {
			dotObjects[j]->visualize();
		}
		for(int k=0; k<fruitCount; k++) {
			fruitObjects[k]->visualize();
		}
		visualizeLives();
		visualizeScore();
		visualizeLevel();
		visualizeTime();
	}

	//visualizes pacman lives remaining
	void SDLMap::visualizeLives() {
		if (p->getLives() > 0) {
			rect = {tileWidth,screenHeight + tileHeight/2,tileWidth,tileHeight};
			SDL_RenderCopy(gRenderer, gTexture, NULL, &rect);
		}
		if (p->getLives() > 1) {
			rect = {3*tileWidth,screenHeight + tileHeight/2,tileWidth,tileHeight};
			SDL_RenderCopy(gRenderer, gTexture, NULL, &rect);
		}
		if (p->getLives() > 2) {
			rect = {5*tileWidth,screenHeight + tileHeight/2,tileWidth,tileHeight};
			SDL_RenderCopy(gRenderer, gTexture, NULL, &rect);
		}
	}

	//visualizes current score
	void SDLMap::visualizeScore() {
		if (score > 1000000) {
			score = 0;
		}
		std::string text = "Score : " + std::to_string(score) ;
		//Get rid of old loaded surface
		SDL_FreeSurface(text_surface);

		// now create a surface from the font
		text_surface = TTF_RenderText_Solid(font, text.c_str(), textColor);
		// render the text surface
		if (text_surface == NULL) {
			std::cout << "Failed to render text surface!\n";
			std::cout<< "SDL_TTF Error: " << TTF_GetError() << "\n" << std::endl;
		}
		else {
			// create a texture from the surface
			gTexture2 = SDL_CreateTextureFromSurface(gRenderer, text_surface);
			if (gTexture2 == NULL) {
				std::cout << "Unable to create texture from rendered text!\n";
			}
			else {
				rect = {screenWidth/2+ 2*tileWidth,screenHeight,3*tileWidth,tileHeight};
				SDL_RenderCopy(gRenderer, gTexture2, NULL, &rect);
			}
		}
	}

	//visualizes current level
	void SDLMap::visualizeLevel() {
		std::string text = "Level : " + std::to_string(level) ;
		//Get rid of old loaded surface
		SDL_FreeSurface(text_surface);

		// now create a surface from the font
		text_surface = TTF_RenderText_Solid(font, text.c_str(), textColor);
		// render the text surface
		if (text_surface == NULL) {
			std::cout << "Failed to render text surface!\n";
			std::cout<< "SDL_TTF Error: " << TTF_GetError() << "\n" << std::endl;
		}
		else {
			// create a texture from the surface
			gTexture2 = SDL_CreateTextureFromSurface(gRenderer, text_surface);
			if (gTexture2 == NULL) {
				std::cout << "Unable to create texture from rendered text!\n";
			}
			else {
				rect = {screenWidth/2+ 2*tileWidth,screenHeight + tileHeight,3*tileWidth,tileHeight};
				SDL_RenderCopy(gRenderer, gTexture2, NULL, &rect);
			}
		}
	}

	//visualizes time playing
	void SDLMap::visualizeTime() {
		int seconds = t->getTimeInSeconds();
		int minutes = t->getTimeInMinutes();
		std::string text = std::to_string(minutes) + " : "  + std::to_string(seconds) ;
		//Get rid of old loaded surface
		SDL_FreeSurface(text_surface);

		// now create a surface from the font
		text_surface = TTF_RenderText_Solid(font, text.c_str(), textColor);
		// render the text surface
		if (text_surface == NULL) {
			std::cout << "Failed to render text surface!\n";
			std::cout<< "SDL_TTF Error: " << TTF_GetError() << "\n" << std::endl;
		}
		else {
			// create a texture from the surface
			gTexture2 = SDL_CreateTextureFromSurface(gRenderer, text_surface);
			if (gTexture2 == NULL) {
				std::cout << "Unable to create texture from rendered text!\n";
			}
			else {
				rect = {screenWidth/2+ 6*tileWidth,screenHeight + tileHeight/2,2*tileWidth,tileHeight};
				SDL_RenderCopy(gRenderer, gTexture2, NULL, &rect);
			}
		}
	}


	/*
	 * Destructor
	 */
	SDLMap::~SDLMap() {
		SDL_DestroyTexture(gTexture);
		SDL_DestroyTexture(gTexture2);
		delete font;
	}

}

