#ifndef PACMAN_H_
#define PACMAN_H_

#include "movingEntity.h"

namespace Pac {
	class Pacman : public movingEntity {
	public:
		Pacman(char direction, float speed, float x, float y);
		bool isMoving();
		void setMoving();
		void clearMoving();
		bool alive();
		int getLives();
		void setLives(int lives);
		void death();
		Pacman();
		virtual ~Pacman();
	protected:
		bool moving;
		int lives;
	};
}



#endif /* PACMAN_H_ */
