#ifndef STATICENTITY_H_
#define STATICENTITY_H_

#include <math.h>

namespace Pac {
	class staticEntity {
		public :
			staticEntity(int x, int y, int score);
			int getScore();
			void setEaten();
			void removeEaten();
			virtual void visualize() = 0;
			virtual int eaten();
			virtual void clearEaten();
			virtual ~staticEntity();
		protected :
			int positionX;
			int positionY;
			int score;
			bool eatable;
	};
}



#endif /* STATICENTITY_H_ */
