#include "Pacman.h"

namespace Pac {

	Pacman::Pacman(char direction, float speed, float x, float y) : movingEntity(direction, speed, x, y)  {
		this->moving = false;
		this->lives = 3;
	}

	//returns if pacman is moving
	bool Pacman::isMoving() {
		return moving;
	}

	//set pacman as moving
	void Pacman::setMoving() {
		this->moving = true;
	}

	//clears pacman moving
	void Pacman::clearMoving() {
		this->moving = false;
		savedDirection = 'i';
		direction = 'i';
	}

	//check if pacman still has lives
	bool Pacman::alive() {
		if (lives > 0) {
			return true;
		}
		else {
			return false;
		}
	}

	//returns pacman lives
	int Pacman::getLives() {
		return lives;
	}

	//set pacman lives
	void Pacman::setLives(int lives) {
		this->lives = lives;
	}
	//substract life from pacman
	void Pacman::death() {
		lives = lives - 1;
	}

	Pacman::~Pacman() {

	}

}


