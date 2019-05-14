#ifndef ABSTRACTFACTORY_H_
#define ABSTRACTFACTORY_H_

#include "abstractButtonHandler.h"
#include "movingEntity.h"
#include "staticEntity.h"
#include "Collision.h"
#include "Astar.h"
#include "Timer.h"
#include "Config.h"


namespace Pac {
	class Map;
	class abstractFactory {
	public:
		abstractFactory();
		virtual bool createRenderer() = 0;
		virtual void clearRenderer() = 0;
		virtual void setRenderer() = 0;
		virtual void closeRenderer() = 0;
		virtual movingEntity* createBlinky(Timer* t) = 0;
		virtual movingEntity* createClyde(Timer *t) = 0;
		virtual movingEntity* createPinky(Timer *t) = 0;
		virtual movingEntity* createInky(Timer *t) = 0;
		virtual movingEntity* createPacman() = 0;
		virtual abstractButtonHandler* createHandler() = 0;
		virtual Map* createMap(abstractFactory* h, movingEntity* p, movingEntity* b, movingEntity* n, movingEntity* in, movingEntity* c, Timer* t, Config* con) = 0;
		virtual staticEntity* createDot(int x, int y, int w, int h, int score) = 0;
		virtual staticEntity* createFruit(int x, int y, int w, int h, int score) = 0;
		virtual staticEntity* createWall(int x, int y, int w, int h) = 0;
		virtual Collision* createCollision(Map* m) = 0;
		virtual Astar* createAstar(Map* m) = 0;
		virtual Timer* createTimer() = 0;
		virtual Config* createConfig(movingEntity* p, movingEntity* b, movingEntity* i, movingEntity* n, movingEntity* c) = 0;
		virtual ~abstractFactory();
	};
}


#endif /* ABSTRACTFACTORY_H_ */
