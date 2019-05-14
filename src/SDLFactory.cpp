#include "SDLFactory.h"

namespace SDLPac {

	//creates the window and renderer in which the game shall be visualized
	bool SDLFactory::createRenderer() {
		//Initialization flag
		bool success = true;
		//Initialize SDL
		if( SDL_Init( SDL_INIT_EVERYTHING) < 0) {
			std::cout << "SDL could not initialize! SDL_Error: %s\n" << SDL_GetError();
			success = false;
		}
		if (TTF_Init() < 0) {
			std::cout << "TTF could not initialize! TTF_Error: %s\n" << TTF_GetError();
			success = false;
		}
		else {
			//Create window
			gWindow = SDL_CreateWindow( "Pacman", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, SDL_WINDOW_SHOWN );
			if( gWindow == NULL ) {
				std::cout << "Window could not be created! SDL_Error: %s\n" << SDL_GetError();
				success = false;
			}

			else {
				//Create renderer for window
				gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED );
				if( gRenderer == NULL ) {
						std::cout << "Renderer could not be created! SDL Error: %s\n" << SDL_GetError() << std::endl;
						success = false;
				}
				else {
					//Initialize renderer color - black
					SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 255 );

					//Initialize PNG loading
					int imgFlags = IMG_INIT_PNG;
					if( !( IMG_Init( imgFlags ) & imgFlags ) ) {
						std::cout << "SDL_image could not initialize! SDL_image Error: %s\n" << IMG_GetError() << std::endl;
						success = false;
					}
				}
			}
		}
		return success;
	}

	//Clears the renderer
	void SDLFactory::clearRenderer() {
		//Clear screen
		SDL_RenderClear( gRenderer );
	}

	//Pushes the renderer to the screen
	void SDLFactory::setRenderer() {
		//Update screen
		SDL_RenderPresent(gRenderer);
		SDL_Delay(50);
	}

	//closes the renderer and deletes the subsystems
	void SDLFactory::closeRenderer() {
		//Destroy window
		SDL_DestroyRenderer( gRenderer );
		SDL_DestroyWindow( gWindow );
		gWindow = NULL;
		gRenderer = NULL;

		//Quit SDL subsystems
		IMG_Quit();
		TTF_Quit();
		SDL_Quit();
	}

	//creates blinky
	Pac::movingEntity* SDLFactory::createBlinky(Pac::Timer* t) {
		SDL_Rect rect = {10,10,10,10}; //initial measurements and location (will be overwritten by Map)
		return new SDLBlinky(gRenderer, rect, 'i', 0, 0, 0, 10, 10,t);
	}

	//creates clyde
	Pac::movingEntity* SDLFactory::createClyde(Pac::Timer* t) {
		SDL_Rect rect = {10,10,10,10}; //initial measurements and location (will be overwritten by Map)
		return new SDLClyde(gRenderer, rect, 'i', 0.25, 0, 0, 10, 10,t);

	}

	//creates pinky
	Pac::movingEntity* SDLFactory::createPinky(Pac::Timer* t) {
		SDL_Rect rect = {10,10,10,10}; //initial measurements and location (will be overwritten by Map)
		return new SDLPinky(gRenderer, rect, 'i', 0.25, 0, 0, 10, 10,t);
	}

	//creates nky
	Pac::movingEntity* SDLFactory::createInky(Pac::Timer* t) {
		SDL_Rect rect = {10,10,10,10}; //initial measurements and location (will be overwritten by Map)
		return new SDLInky(gRenderer, rect, 'i', 0.25, 0, 0, 10, 10,t);
	}

	//creates pacman
	Pac::movingEntity* SDLFactory::createPacman() {
		SDL_Rect rect = {50,10,10,10}; //initial measurements and location (will be overwritten by Map)
		//return new SDLPacman(gRenderer, rect, 'i', 0.250);
		return new SDLPacman(gRenderer, rect, 'i', 0.25);
	}

	//creates buttonhandler
	Pac::abstractButtonHandler* SDLFactory::createHandler() {
		return new SDLButtonHandler();
	}

	//creates map
	Pac::Map* SDLFactory::createMap(Pac::abstractFactory* h,Pac::movingEntity* p, Pac::movingEntity* b, Pac::movingEntity* n, Pac::movingEntity* in, Pac::movingEntity* c, Pac::Timer* t, Pac::Config* con) {
		std::string map = con->getMapnaam();
		int tileWidth = con->getTileWidth();
		int tileHeight = con->getTileHeight();
		return new SDLMap(gRenderer,gWindow,h,p, b, n, in, c,t,map,tileWidth,tileHeight);
	}

	//creates fruit
	Pac::staticEntity* SDLFactory::createFruit(int x, int y, int w, int h, int score) {
		return new SDLFruit(gRenderer, x, y, w, h, score);
	}

	//creates dot
	Pac::staticEntity* SDLFactory::createDot(int x, int y, int w, int h, int score) {
		return new SDLDot(gRenderer, x, y, w, h, score);
	}

	//creates wall
	Pac::staticEntity* SDLFactory::createWall(int x, int y, int w, int h) {
		return new SDLWall(gRenderer, x, y, w, h, 0);
	}

	//creates collision
	Pac::Collision* SDLFactory::createCollision(Pac::Map* m) {
		int** mapLayout = m->getMapLayout();
		return new Pac::Collision(mapLayout, m->getHeight());
	}

	Pac::Astar* SDLFactory::createAstar(Pac::Map* m) {
		int** mapLayout = m->getMapLayout();
		int mapWidth = m->getWidth();
		int mapHeight = m->getHeight();
		return new Pac::Astar(mapLayout,mapWidth, mapHeight);
	}

	//creates timer
	Pac::Timer* SDLFactory::createTimer() {
		return new SDLTimer();
	}

	//creates config
	Pac::Config* SDLFactory::createConfig(Pac::movingEntity* p, Pac::movingEntity* b, Pac::movingEntity* i, Pac::movingEntity* n, Pac::movingEntity* c) {
		return new Pac::Config(p, b, i, n, c);
	}

	SDLFactory::~SDLFactory() {
		delete gRenderer;
		delete gWindow;
	}

}
