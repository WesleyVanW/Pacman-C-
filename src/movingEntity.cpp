#include "movingEntity.h"

namespace Pac {

	movingEntity::movingEntity(char direction, float speed, float x, float y) {
		this->direction = direction;
		this->savedDirection = direction;
		this->speed = speed;
		this->initSpeed = speed;
		this->positionX = x;
		this->positionY = y;
		this->startX = 0;
		this->startY = 0;
		this->positionCoord = new int[2];
		this->floatPosition = new float[2];
	}

	//Returns the position of this object based on going direction
	int* movingEntity::getPosition() {
		int getPositionX;
		int getPositionY;
		if(direction == 'l') {
			getPositionX = ceil(positionX);
			getPositionY = positionY;
		}
		else if(direction == 'u') {
			getPositionY = ceil(positionY);
			getPositionX = positionX;
		}
		else if(direction == 'r') {
			getPositionX = floor(positionX);
			getPositionY = positionY;
		}
		else if(direction == 'd') {
			getPositionY = floor(positionY);
			getPositionX = positionX;
		}
		else {
			getPositionX = positionX;
			getPositionY = positionY;
		}
		positionCoord[0] = getPositionX;
		positionCoord[1] = getPositionY;
		return positionCoord;
	}

	//returns the position of this object in floating
	float* movingEntity::getFloatPosition() {
		floatPosition[0] = positionX;
		floatPosition[1] = positionY;
		return floatPosition;
	}

	//returns true if this ojbject is fully contained in one tile on the map
	bool movingEntity::checkPosition(int mapWidth, int mapHeight) {
		if (positionX == floor(positionX) && positionY == floor(positionY) && positionX > 0 && positionX < mapWidth && positionY > 0 && positionY < mapHeight) {
			return true;
		}
		else {
			return false;
		}
	}
	//returns the direction of this object
	char movingEntity::getDirection() {
		return direction;
	}
	//reverses objects direction
	char movingEntity::getReversedDirection() {
		switch(direction) {
		case 'r' :
			return 'l';
			break;
		case 'l' :
			return 'r';
			break;
		case 'u' :
			return 'd';
			break;
		case 'd' :
			return 'u';
			break;
		default :
			return 'i';
			break;
		}
	}

	//moves the object when checking if it can change direction based by being fully contained on one tile on the map and checks for collection in its direction
	void movingEntity::move(Collision* c, int mapWidth, int mapHeight, bool frightened) {
		if(c->detectCollision(getPosition(), savedDirection) == false && direction != savedDirection) {
			if(checkPosition(mapWidth, mapHeight)) {
				this->direction = savedDirection;
				moveDirection(frightened);
			}
			else {
				moveDirection(frightened);
			}
		}
		else if (c->detectCollision(getPosition(), direction) == false) {
			moveDirection(frightened);
		}
		checkOutOfBounds(mapWidth, mapHeight);
	}

	//moves the object in set direction
	void movingEntity::moveDirection(bool frightened) {
		if (frightened == true) {
			speed = initSpeed/2;
		}
		if (frightened == false) {
			speed = initSpeed;
		}
		switch (direction) {
			case 'l' : // left
				positionX = positionX - speed;
				break;
			case 'd' :// down
				positionY = positionY + speed;
				break;
			case 'r' :  // right
				positionX = positionX + speed;
				break;
			case 'u' :  // up
				positionY = positionY - speed;
				break;
		}
	}

	void movingEntity::checkOutOfBounds(int mapWidth, int mapHeight) {
		positionCoord = getPosition();
		int getPositionX = positionCoord[0];
		int getPositionY = positionCoord[1];
		if (getPositionX < 0) {
			positionX = mapWidth;
		}
		if (getPositionX > mapWidth) {
			positionX = 0;
		}
		if (getPositionY < 0) {
			positionY = mapHeight;
		}
		if (getPositionY > mapHeight) {
			positionY = 0;
		}
	}

	//sets the direction if change is 180 degrees else the desired direction is saved
	void movingEntity::setDirection(char direction) {
		this->savedDirection = direction;
		if((direction == 'l' && savedDirection == 'r') || (direction == 'r' && savedDirection == 'l') || (direction == 'u' && savedDirection == 'd') || (direction == 'd' && savedDirection == 'u')) {
			this->direction = direction;
		}
	}

	//sets the location of this object
	void movingEntity::setLocation(int x, int y) {
		positionX = x;
		positionY = y;
		positionCoord[0] = x;
		positionCoord[1] = y;
	}

	//sets the start tile of this object
	void movingEntity::setStartTile(int x, int y) {
		startX = x;
		startY = y;
	}

	//moves object to starttile
	void movingEntity::moveToStartTile() {
		positionX = startX;
		positionY = startY;
	}

	//sets the speed on which this object shall move
	void movingEntity::setSpeed(float speed) {
		this->initSpeed = speed / 100.;
		this->speed = initSpeed;
	}

	void movingEntity::setGhostDirectionChase(Collision* c, Astar* as, int* pacPosition) {

	}

	void movingEntity::setGhostDirectionAmbush(Collision* c, Astar* as, int* pacPosition, char pacDirection) {

	}

	void movingEntity::setGhostDirectionHomeTile(Collision* c, Astar* as) {

	}
	bool movingEntity::isFrightened() {
		return false;
	}

	void movingEntity::setFrightened(int time) {

	}

	void movingEntity::clearFrightened() {

	}

	int movingEntity::getTimeFrightened() {
		return 0;
	}

	void movingEntity::checkStillFrightened() {

	}

	void movingEntity::setFrightenTime(int frightenTime) {

	}

	void movingEntity::setStartPos(int x, int y) {

	}

	void movingEntity::setHomeTile(int x, int y) {

	}

	void movingEntity::moveToStartPos() {

	}

	void movingEntity::moveToHomeTile() {

	}
	bool movingEntity::isMoving() {
		return false;
	}

	void movingEntity::setMoving() {

	}

	void movingEntity::clearMoving() {

	}

	bool movingEntity::alive() {
		return false;
	}

	int movingEntity::getLives() {
		return 0;
	}

	void movingEntity::setLives(int lives) {

	}

	void movingEntity::death() {

	}

	bool movingEntity::isEaten() {
		return false;
	}

	void movingEntity::setEaten() {

	}

	void movingEntity::clearEaten() {

	}
	movingEntity::~movingEntity() {
		delete positionCoord;
	}
}



