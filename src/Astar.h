#ifndef ASTAR_H_
#define ASTAR_H_

#include<bits/stdc++.h>
#include <utility>

#define ROW 20
#define COL 19

namespace Pac {
	// Creating a shortcut for int, int pair type
	typedef std::pair<int, int> Pair;

	// Creating a shortcut for pair<int, pair<int, int>> type
	typedef std::pair<double, std::pair<int, int>> pPair;

	// A structure to hold the neccesary parameters
	struct cell {
		// Row and Column index of its parent
		// Note that 0 <= i <= ROW-1 & 0 <= j <= COL-1
		int parent_i, parent_j;
    	// f = g + h
    	double f, g, h;
	};

	class Astar {
		public :
			Astar(int** map,int mapWidth, int mapHeight);
			bool isValid(int row, int col);
			bool isUnBlocked(int row, int col);
			bool isDestination(int row, int col, Pair dest);
			bool isDestinationIntersection(int row, int col);
			double calculateHValue(int row, int col, Pair dest);
			char tracePath(cell cellDetails[][COL], Pair dest, char currentDirection);
			char aStarSearch(Pair src, Pair dest, char currentDirection);
			Pair aStarSearchNextIntersection(Pair src, char currentDirection);
			char getDirectionBetweenPairs(Pair s, Pair e, char currentDirection);
			bool reachedDestination(Pair src, Pair dest);
			virtual ~Astar();
		private :
			int** grid;
			int mapWidth;
			int mapHeight;
	};

}



#endif /* ASTAR_H_ */
