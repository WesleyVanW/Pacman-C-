#include "Collision.h"

namespace Pac {

	Collision::Collision(int** mapLayout, int mapHeight) {
		this->mapLayout = mapLayout;
		this->positionX = 0;
		this->positionY = 0;
		this->mapHeight = 0;
	}

	//detects collision based on position and going direction
	//returns true if collision detected else false
	bool Collision::detectCollision(int* position, char direction) {
		positionX = position[0];
		positionY = position[1];
		switch (direction) {
			case 'l' :
				if(mapLayout[positionY][positionX-1] == 1 || mapLayout[positionY][positionX-1] == 7) {
					return true;
				}
				else {
					return false;
				}
				break;
			case 'r' :
				if(mapLayout[positionY][positionX+1] == 1 || mapLayout[positionY][positionX+1] == 7) {
					return true;
				}
				else {
					return false;
				}
				break;
			case 'u' :
				if(mapLayout[positionY-1][positionX] == 1 || mapLayout[positionY-1][positionX] == 7) {
					return true;
				}
				else {
					return false;
				}
				break;
			case 'd' :
				if(mapLayout[positionY+1][positionX] == 1 || mapLayout[positionY+1][positionX] == 7) {
					return true;
				}
				else {
					return false;
				}
				break;
			default:
				return false;
				break;
		}
	}

	//Returns true if collision based on current position of pacman and ghost is detected else false
	bool Collision::detectEncounter(float* pacPosition, float* ghostPosition) {
		float pacPositionX = pacPosition[0];
		float pacPositionY = pacPosition[1];
		float ghostPositionX = ghostPosition[0];
		float ghostPositionY = ghostPosition[1];
		//std::cout << pacPosition[0] << " " << pacPosition[1] << " " << ghostPosition[0] << " " << ghostPosition[1] << std::endl;
		if(pacPositionX - ghostPositionX < 0 && pacPositionX - ghostPositionX > -1 && pacPositionY - ghostPositionY == 0) {
			return true;
		}
		else if(pacPositionX - ghostPositionX < 0 && pacPositionX - ghostPositionX > -1 && pacPositionY - ghostPositionY == 0) {
			return true;
		}
		else if(pacPositionY - ghostPositionY > 0 && pacPositionY - ghostPositionY < 1 && pacPositionX - ghostPositionX == 0) {
			return true;
		}
		else if(pacPositionY - ghostPositionY > 0 && pacPositionY - ghostPositionY < 1 && pacPositionX - ghostPositionX == 0) {
			return true;
		}
		else {
			return false;
		}

	}

	Collision::~Collision() {
		for(int i = 0; i < mapHeight; i++) {
				delete [] mapLayout[i];
		}
		delete [] mapLayout;
	}

}


