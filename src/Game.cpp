#include "Game.h"

namespace Pac {

	Game::Game(Pac::abstractFactory* f) {
		this-> b = NULL;
		this-> n = NULL;
		this-> i = NULL;
		this-> c = NULL;
		this-> p = NULL;
		this-> h = NULL;
		this-> m = NULL;
		this-> col = NULL;
		this-> as = NULL;
		this-> t = NULL;
		this-> config = NULL;
		this->factory = f;
		this->homeTime = 0;
		this->huntTime = 0;
	}

	//Gameloop
	void Game::playGame(movingEntity* b, movingEntity* n, movingEntity* i, movingEntity* c, movingEntity* p, abstractButtonHandler* h, Map* m, Collision* col, Astar* as, Timer* t, Config* con) {
		char checkEvent;
		int iterator = 0;
		bool moveToHomeTile = true;
		int startTime = 0;
		int currentTime = 0;
		homeTime = con->getHometime();
		huntTime = con->getHunttime();
		while(gameover != 1) {
			/* look for an event */
			checkEvent = h->eventCheck();
			if(checkEvent == 'q' || p->alive() == false) {
				gameover = 1;
				closeGame();
			}
			else {
				factory->clearRenderer();

				//Set direction of pacman according to button pressed
				//If pacman first starts moving teleport ghost to starting position
				//start timer if timer isn't running and initiate ghosts to move to hometile
				if(checkEvent != 'x') {
					iterator += 1;
					p->setDirection(checkEvent);
					if(iterator==1) {
						p->setMoving();
						b->moveToStartPos();
						n->moveToStartPos();
						i->moveToStartPos();
						c->moveToStartPos();
						if(!t->getRunning()) {
							t->startTimer();
							moveToHomeTile = true;
							startTime = t->getTimeInSeconds() + 60*t->getTimeInMinutes();
						}
					}
				}
				//if ghost should move to hometile set direction accordingly
				if(p->isMoving() && moveToHomeTile == true) {
					b->setGhostDirectionHomeTile(col,as);
					n->setGhostDirectionHomeTile(col,as);
					i->setGhostDirectionHomeTile(col,as);
					c->setGhostDirectionHomeTile(col,as);
				}
				//if ghost should chase or ambush pacman set direction accordingly
				if(p->isMoving() && moveToHomeTile == false) {
					b->setGhostDirectionChase(col,as,p->getPosition());
					n->setGhostDirectionAmbush(col,as,p->getPosition(),p->getDirection());
					i->setGhostDirectionChase(col,as,p->getPosition());
					c->setGhostDirectionAmbush(col,as,p->getPosition(),p->getDirection());
				}

				currentTime = t->getTimeInSeconds() + 60*t->getTimeInMinutes();
				//check if ghost should move to hometile or to pacman according to measured time and its settings
				if(moveToHomeTile) {
					if (currentTime - startTime > homeTime) {
						startTime = currentTime;
						moveToHomeTile = false;
					}
				}
				if(!moveToHomeTile) {
					if (currentTime - startTime > huntTime) {
						startTime = currentTime;
						moveToHomeTile = true;
					}
				}
				//move pacman and ghosts
				p->move(col,m->getWidth(), m->getHeight(),p->isFrightened());
				b->move(col,m->getWidth(), m->getHeight(),b->isFrightened());
				n->move(col,m->getWidth(), m->getHeight(),n->isFrightened());
				i->move(col,m->getWidth(), m->getHeight(),i->isFrightened());
				c->move(col,m->getWidth(), m->getHeight(),c->isFrightened());

				//checks if pacman is on dot or fruit which can be eaten and add score accordingly
				//if no more dots and fruits to eat this goes to new level where all dots and fruits will be shown again
				//ghosts move to base and pacman to its starting position without moving
				if (m->updateMap() == true) {
					iterator = 0;
				}

				//Handle encounter between ghost and pacman by either adding points if ghost is frightened
				//and not already eaten or substract life from pacman and move to starting position and stop the timer
				if(col->detectEncounter(p->getFloatPosition(), b->getFloatPosition())) {
					if (b->isFrightened() && !b->isEaten()) {
						b->setEaten();
						m->addGhostPoints();
					}
					else if(!b->isFrightened()) {
						p->death();
						m->restart();
						t->stopTimer();
						iterator = 0;
					}
				}

				if(col->detectEncounter(p->getFloatPosition(), n->getFloatPosition())) {
					if (n->isFrightened() && !n->isEaten()) {
						n->setEaten();
						m->addGhostPoints();
					}
					else if(!n->isFrightened()) {
						p->death();
						m->restart();
						t->stopTimer();
						iterator = 0;
					}
				}

				if(col->detectEncounter(p->getFloatPosition(), i->getFloatPosition())) {
					if (i->isFrightened() && !i->isEaten()) {
						i->setEaten();
						m->addGhostPoints();
					}
					else if(!i->isFrightened()) {
						p->death();
						m->restart();
						t->stopTimer();
						iterator = 0;
					}
				}

				if(col->detectEncounter(p->getFloatPosition(), c->getFloatPosition())) {
					if (c->isFrightened() && !c->isEaten()) {
						c->setEaten();
						m->addGhostPoints();
					}
					else if(!c->isFrightened()){
						p->death();
						m->restart();
						t->stopTimer();
						iterator = 0;
					}
				}

				//visualize objects

				//Render texture to screen
				m->visualize();
				b->visualize();
				n->visualize();
				i->visualize();
				c->visualize();
				p->visualize();

				factory->setRenderer();
			}
		}
	}

	bool Game::initGame() {
		return factory->createRenderer();
	}

	void Game::closeGame() {
		factory->clearRenderer();
	}

	void Game::start() {
		if(initGame() == true) {
			t = factory->createTimer();
			//std::cout << "t" << std::endl;
			b = factory->createBlinky(t);
			//std::cout << "b" << std::endl;
			n = factory->createPinky(t);
			//std::cout << "n" << std::endl;
			i = factory->createInky(t);
			//std::cout << "i" << std::endl;
			c = factory->createClyde(t);
			//std::cout << "c" << std::endl;
			p = factory->createPacman();
			//std::cout << "p" << std::endl;
			h = factory->createHandler();
			//std::cout << "h" << std::endl;
			config = factory->createConfig(p,b,i,n,c);
			//std::cout << "config" << std::endl;
			if (config->loadConfig()) {
				m = factory->createMap(factory,p,b, n, i, c,t, config);
				m->setWindowSize();
				//std::cout << "m" << std::endl;
				col = factory->createCollision(m);
				//std::cout << "col" << std::endl;
				as = factory->createAstar(m);
				//std::cout << "as" << std::endl;
				playGame(b, n, i, c, p, h, m, col, as, t, config);
			}
		}
	}

	Game::~Game() {
		delete b;
		delete p;
		delete h;
		delete m;
		delete c;
		delete as;
		delete t;
		delete config;
		delete factory;
	}
}






