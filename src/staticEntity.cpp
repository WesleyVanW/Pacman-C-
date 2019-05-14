#include "staticEntity.h"

namespace Pac {

	staticEntity::staticEntity(int x, int y, int score) {
		this->positionX = x;
		this->positionY = y;
		this->score = score;
		if(score > 0) {
			eatable = true;
		}
		else {
			eatable = false;
		}
	}

	//returns the score if object is eatable
	int staticEntity::getScore() {
		if (eatable) {
			return score;
		}
		else {
			return 0;
		}
	}

	//sets this object as eaten
	void staticEntity::setEaten() {
		eatable = false;
	}

	//sets this object as eatable
	void staticEntity::removeEaten() {
		eatable = true;
	}

	int staticEntity::eaten() {
		return 0;
	}

	void staticEntity::clearEaten() {

	}

	staticEntity::~staticEntity() {

	}

}




