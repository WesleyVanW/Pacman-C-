#ifndef MAP_H_
#define MAP_H_

#include <string>
#include <iostream>
#include <fstream>
#include <math.h>
#include "movingEntity.h"
#include "staticEntity.h"
#include "abstractFactory.h"

namespace Pac {
	class Map {
		public:
			Map(abstractFactory* h, movingEntity* p, movingEntity* b, movingEntity* n, movingEntity* in, movingEntity* c, Timer* t, std::string map, int tileWidth, int tileHeight);
			void setMap(std::string map);
			bool getDimensions();
			bool makeMap();
			void makeMapObjects();
			int getElementAtPosition(int x, int y);
			int getDotCount(int x, int y);
			int getFruitCount(int x, int y);
			int** getMapLayout();
			int getWidth();
			int getHeight();
			bool updateMap();
			void restart();
			void addGhostPoints();
			virtual ~Map();
			virtual void visualize() = 0;
			virtual void visualizeLives() = 0;
			virtual void visualizeScore() = 0;
			virtual void visualizeLevel() = 0;
			virtual void visualizeTime() = 0;
			virtual void setWindowSize() = 0;
		protected :
			abstractFactory* h;
			movingEntity* p;
			movingEntity* b;
			movingEntity* n;
			movingEntity* in;
			movingEntity* c;
			Timer* t;
			std::string map;
			int** mapLayout;
			staticEntity** wallObjects;
			staticEntity** dotObjects;
			staticEntity** fruitObjects;
			int tileWidth;
			int tileHeight;
			int mapWidth;
			int mapHeight;
			int screenWidth;
			int screenHeight;
			int wallCount;
			int dotCount;
			int fruitCount;
			int* positionArray;
			int pacmanX;
			int pacmanY;
			int score;
			int level;
			int eatenFruit;
			int eatenDot;
	};
}

#endif /* MAP_H_ */
