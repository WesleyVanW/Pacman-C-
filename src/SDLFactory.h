#ifndef SDLFACTORY_H_
#define SDLFACTORY_H_

#include <string>
#include "abstractFactory.h"
#include "SDLBlinky.h"
#include "SDLClyde.h"
#include "SDLPinky.h"
#include "SDLInky.h"
#include "SDLPacman.h"
#include "SDLButtonHandler.h"
#include "SDLMap.h"
#include "SDLDot.h"
#include "SDLFruit.h"
#include "SDLWall.h"
#include "SDLTimer.h"
#include <iostream>

namespace SDLPac {
	class SDLFactory : public Pac::abstractFactory {
	public :
		virtual ~SDLFactory();
		bool createRenderer();
		void clearRenderer();
		void setRenderer();
		void closeRenderer();
		Pac::movingEntity* createBlinky(Pac::Timer* t);
		Pac::movingEntity* createClyde(Pac::Timer* t);
		Pac::movingEntity* createPinky(Pac::Timer* t);
		Pac::movingEntity* createInky(Pac::Timer* t);
		Pac::movingEntity* createPacman();
		Pac::abstractButtonHandler* createHandler();
		Pac::Map* createMap(Pac::abstractFactory* h,Pac::movingEntity* p, Pac::movingEntity* b, Pac::movingEntity* n, Pac::movingEntity* in, Pac::movingEntity* c, Pac::Timer* t, Pac::Config* con);
		Pac::staticEntity* createDot(int x, int y,int w, int h, int score);
		Pac::staticEntity* createFruit(int x, int y, int w, int h, int score);
		Pac::staticEntity* createWall(int x, int y, int w, int h);
		Pac::Collision* createCollision(Pac::Map* m);
		Pac::Astar* createAstar(Pac::Map* m);
		Pac::Timer* createTimer();
		Pac::Config* createConfig(Pac::movingEntity* p, Pac::movingEntity* b, Pac::movingEntity* i, Pac::movingEntity* n, Pac::movingEntity* c);
	private :
		SDL_Window* gWindow = NULL; //The window we'll be rendering to
		SDL_Renderer* gRenderer = NULL; //The window renderer

	};
}


#endif /* SDLFACTORY_H_ */
