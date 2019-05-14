#include "Ghost.h"

namespace Pac {

	Ghost::Ghost(char direction, float speed, float x, float y, int homeTileX, int homeTileY, int startPosX, int startPosY, Timer* t) : movingEntity(direction, speed, x, y) {
		this->frightened = false;
		this->timeStartFrightened = 0;
		this->frightenTime = 0;
		this->homeTileX = homeTileX;
		this->homeTileY = homeTileY;
		this->startPosX = startPosX;
		this->startPosY = startPosY;
		this->wasAlreadyFrightened = false;
		this->eaten = false;
		this->t = t;
	}

	//Sets the direction of the ghosts to chase pacman (=destination = pacmans current position
	//if frightened ghost shall move to base and immediatly revert its current direction
	//if base is reached ghost will not be frightened anymore
	void Ghost::setGhostDirectionChase(Collision* c, Astar* as, int* pacPosition) {
		positionCoord = getPosition();
		//std::cout << "(" << positionCoord[1] << "," << positionCoord[0] << ")" << " + " << direction << std::endl;
		//std::cout << "Pac(" << pacPosition[0] << "," << pacPosition[1] << ") Ghost(" << positionCoord[0] << "," << positionCoord[1] << ")" << std::endl;
		if (!frightened && positionX == floor(positionX) && positionY == floor(positionY)) {
			checkStillFrightened();
			savedDirection = as->aStarSearch({positionCoord[1],positionCoord[0]},{pacPosition[1],pacPosition[0]}, savedDirection);
		}
		if (frightened && positionX == floor(positionX) && positionY == floor(positionY)) {
			checkStillFrightened();
			if (wasAlreadyFrightened == false) {
				savedDirection = getReversedDirection();
			}
			if (wasAlreadyFrightened == true) {
				savedDirection = as->aStarSearch({positionCoord[1],positionCoord[0]},{startPosY,startPosX}, savedDirection);
				if(as->reachedDestination({positionCoord[1],positionCoord[0]},{startPosY,startPosX}) == true) {
					clearFrightened();
					clearEaten();
				}
			}
			wasAlreadyFrightened = true;
		}
	}


	//Sets the direction of the ghosts to chase pacman (=destination = pacmans next intersection based on current position
	//if frightened ghost shall move to base and immediatly revert its current direction
	//if base is reached ghost will not be frightened anymore
	void Ghost::setGhostDirectionAmbush(Collision* c, Astar* as, int* pacPosition, char pacDirection) {
		positionCoord = getPosition();
		//std::cout << "(" << positionCoord[1] << "," << positionCoord[0] << ")" << " + " << direction << std::endl;
		//std::cout << "Pac(" << pacPosition[0] << "," << pacPosition[1] << ") Ghost(" << positionCoord[0] << "," << positionCoord[1] << ")" << std::endl;
		if (!frightened && positionX == floor(positionX) && positionY == floor(positionY)) {
			checkStillFrightened();
			Pair destinationPair = as->aStarSearchNextIntersection({pacPosition[1],pacPosition[0]},pacDirection);
			if (destinationPair.first != 0 && destinationPair.second != 0) {
				savedDirection = as->aStarSearch({positionCoord[1],positionCoord[0]},destinationPair, savedDirection);
			}
		}
		if (frightened && positionX == floor(positionX) && positionY == floor(positionY)) {
			checkStillFrightened();
			if (wasAlreadyFrightened == false) {
				savedDirection = getReversedDirection();
			}
			if (wasAlreadyFrightened == true) {
				savedDirection = as->aStarSearch({positionCoord[1],positionCoord[0]},{startPosY,startPosX}, savedDirection);
				if(as->reachedDestination({positionCoord[1],positionCoord[0]},{startPosY,startPosX}) == true) {
					clearFrightened();
					clearEaten();
				}
			}
			wasAlreadyFrightened = true;
		}
	}

	//Sets the direction of the ghosts to move to hometile
	//if frightened ghost shall move to base and immediatly revert its current direction
	//if base is reached ghost will not be frightened anymore
	void Ghost::setGhostDirectionHomeTile(Collision* c,Astar* as) {
		positionCoord = getPosition();
		//std::cout << "(" << positionCoord[1] << "," << positionCoord[0] << ")" << " + " << direction << std::endl;
		//std::cout << "Pac(" << pacPosition[0] << "," << pacPosition[1] << ") Ghost(" << positionCoord[0] << "," << positionCoord[1] << ")" << std::endl;
		if (!frightened && positionX == floor(positionX) && positionY == floor(positionY)) {
			checkStillFrightened();
			savedDirection = as->aStarSearch({positionCoord[1],positionCoord[0]},{homeTileY,homeTileX}, savedDirection);
		}
		if (frightened && positionX == floor(positionX) && positionY == floor(positionY)) {
			checkStillFrightened();
			if (wasAlreadyFrightened == false) {
				savedDirection = getReversedDirection();
			}
			if (wasAlreadyFrightened == true) {
				savedDirection = as->aStarSearch({positionCoord[1],positionCoord[0]},{startPosY,startPosX}, savedDirection);
				if(as->reachedDestination({positionCoord[1],positionCoord[0]},{startPosY,startPosX}) == true) {
					clearFrightened();
					clearEaten();
				}
			}
			wasAlreadyFrightened = true;
		}
	}

	//return if ghost is frightened
	bool Ghost::isFrightened() {
		return frightened;
	}

	//set ghost as frightened
	void Ghost::setFrightened(int time) {
		frightened = true;
		wasAlreadyFrightened = false;
		timeStartFrightened = time;
	}

	//set ghost as not frightened
	void Ghost::clearFrightened() {
		frightened = false;
		wasAlreadyFrightened = false;
		clearEaten();
	}

	//check if ghosts should still be frightened in respect to the frightentime
	void Ghost::checkStillFrightened() {
		if (getTimeFrightened() >= frightenTime) {
			clearFrightened();
		}
	}
	//get duration of ghost being frightened
	int Ghost::getTimeFrightened() {
		return 60*t->getTimeInMinutes() + t->getTimeInSeconds() - timeStartFrightened;
	}

	//set how long ghost should be frightened
	void Ghost::setFrightenTime(int frightenTime) {
		this->frightenTime = frightenTime;
	}

	//set start position outside of base where ghost shall be teleported to in case of start moving pacman
	void Ghost::setStartPos(int x, int y) {
		startPosX = x;
		startPosY = y;
	}

	//set ghost hometile
	void Ghost::setHomeTile(int x, int y) {
		homeTileX = x;
		homeTileY = y;
	}

	//teleport ghost to starting position
	void Ghost::moveToStartPos() {
		positionX = startPosX;
		positionY = startPosY;
	}

	//returns if pacman has eaten ghost
	bool Ghost::isEaten() {
		return eaten;
	}

	//set ghost as eaten
	void Ghost::setEaten() {
		eaten = true;
	}

	//set ghost as not eaten
	void Ghost::clearEaten() {
		eaten = false;
	}
	Ghost::~Ghost() {
		delete t;
	}

}


