#include "SDLButtonHandler.h"

namespace SDLPac {

	SDLButtonHandler::~SDLButtonHandler() {
	}

	//reads arrow input and returns a direction as a char
	char SDLButtonHandler::eventCheck() {
		SDL_Event event;
		char returnChar = 'x';
		while( SDL_PollEvent( &event ) ){
			switch( event.type ){
				case SDL_KEYDOWN:
					switch( event.key.keysym.sym ){
						case SDLK_UP:
							returnChar = 'u';
							break;
						case SDLK_DOWN:
							returnChar = 'd';
							break;
						case SDLK_LEFT:
							returnChar = 'l';
							break;
						case SDLK_RIGHT:
							returnChar = 'r';
							break;
						case SDLK_ESCAPE:
							returnChar = 'q';
							break;
						default:
							break;
					}
					break;
				case SDL_QUIT:
					returnChar = 'q';
					break;
		   }
	   }
	   return returnChar;
	}
}








