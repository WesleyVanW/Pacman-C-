#ifndef COLLISION_H_
#define COLLISION_H_

#include <iostream>

namespace Pac {
	class Collision {
	public :
		Collision(int** mapLayout, int mapHeight);
		bool detectCollision(int* position, char direction);
		bool detectEncounter(float* pacPosition, float* ghostPosition);
		virtual ~Collision();
	private :
		int** mapLayout;
		int positionX;
		int positionY;
		int mapHeight;
	};
}



#endif /* COLLISION_H_ */
