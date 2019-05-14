#ifndef GAME_H_
#define GAME_H_

#include "AbstractFactory.h"
#include "Map.h"
#include <iostream>

namespace Pac {
	class Game {
		public :
			Game(abstractFactory* f);
			void start();
			void playGame(movingEntity* b, movingEntity* n, movingEntity* i, movingEntity* c, movingEntity* p, abstractButtonHandler* h, Map* m, Collision* col, Astar* as, Timer* t, Config* con);
			bool initGame();
			void closeGame();
			virtual ~Game();
		protected :
			abstractFactory* factory;
			movingEntity* b;
			movingEntity* n;
			movingEntity* i;
			movingEntity* c;
			movingEntity* p;
			abstractButtonHandler* h;
			Map* m;
			Collision* col;
			Astar* as;
			Timer* t;
			Config* config;
			int gameover = 0;
			int huntTime;
			int homeTime;
	};
}


#endif /* GAME_H_ */
