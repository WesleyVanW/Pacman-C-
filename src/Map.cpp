#include "Map.h"

namespace Pac {

	Map::Map(abstractFactory* h,movingEntity* p,movingEntity* b, movingEntity* n, movingEntity* in, movingEntity* c,Timer* t, std::string map, int tileWidth, int tileHeight) {
		this->h = h;
		this->p = p;
		this->b = b;
		this->n = n;
		this->in = in;
		this->c = c;
		this->t = t;
		this->map = map;
		this->tileWidth = tileWidth;
		this->tileHeight = tileHeight;
		this->wallCount = 0;
		this->dotCount = 0;
		this->fruitCount = 0;
		this->positionArray = new int[2];
		this->score = 0;
		this->level = 1;
		this->eatenFruit = 0;
		this->eatenDot = 0;
		int init = getDimensions();
		int init2 = 0;
		if(init == 1) {
			//std::cout<< "making maplayout" << std::endl;
			mapLayout = new int*[mapHeight];
			for(int i = 0; i < mapHeight; i++) {
				mapLayout[i] = new int[mapWidth];
			}
			//std::cout<< mapHeight << " " << mapWidth << std::endl;
			//std::cout<< "finished maplayout" << std::endl;
			init2 = makeMap();
			if(init2 == 1) {
				//std::cout << "making map objects" << std::endl;
				//std::cout<< tileWidth << " " << tileHeight << std::endl;
				//std::cout<< wallCount << " " << dotCount << " " << fruitCount << std::endl;
				makeMapObjects();
				//std::cout << "finished map objects" << std::endl;
			}
			if(init2 == 0) {
				std::cout << "Error! Could not create mapLayout." << std::endl;
			}
		}
		if(init == 0){
			std::cout << "Error! Could not get dimensions and initialize mapLayout." << std::endl;
		}
	}

	void Map::setMap(std::string map) {
		this->map = map;
	}

	/*
	 * Reads the map txt file and returns the width and height for the dynamic array
	 * in which the map will be saved + calculates the needed width and height of the SDL window.
	*/
	bool Map::getDimensions() {
		std::string line;
		std::ifstream inData ;
		inData.open(map);
		int lastWidth = 0;
		int i = 0;
		int close = 0;
		mapWidth = 0;
		mapHeight = 0;
		screenWidth = 0;
		screenHeight = 0;
		if (inData.fail()) {
			return 0;
		}
		else {
			while(!inData.eof() && close != 1) {
				getline(inData,line);
				mapHeight += 1;
				if(i==0) {
					mapWidth = line.length();
					lastWidth = mapWidth;
				}
				else {
					mapWidth = line.length();
					if (mapWidth != lastWidth) {
						std::cout << "Error! Invalid map measurements." << std::endl;
						mapWidth = 0;
						mapHeight = 0;
						screenWidth = 0;
						screenHeight = 0;
						close = 1;
						return 0;
					}
				}
				i = 1;
			}
			inData.close();
			screenWidth = mapWidth * tileWidth;
			screenHeight = mapHeight * tileHeight;
			return 1;
		}
	}

	/*
	 * Reads the map txt file again and stores its elements in
	 * the earlier initialised dynamic array aswell as
	 * keeping count of the different elements it stores.
	 * Also sets the correct starting position for the ghosts and pacman in the maze.
	 */
	bool Map::makeMap() {
		int lineNumber = -1;
		std::string line;
		std::ifstream inData ;
		inData.open(map);
		if (inData.fail()) {
			return 0;
		}
		else {
			while(!inData.eof()) {
				getline(inData,line);
				lineNumber += 1;
				for(int i=0; i < line.size(); i++) {
					if (line[i] == '1') {			  //Wall
						mapLayout[lineNumber][i] = 1;
						wallCount += 1;
					}
					if (line[i] == '2') {			  //Dot
						mapLayout[lineNumber][i] = 2;
						dotCount += 1;
					}
					if (line[i] == '3') {			  //Fruit
						mapLayout[lineNumber][i] = 3;
						fruitCount += 1;
					}
					if (line[i] == '0') {			  //Empty
						mapLayout[lineNumber][i] = 0;
					}
					if (line[i] == 'P') {
						mapLayout[lineNumber][i] = 5; //Pacman
					}
					if (line[i] == 'B') {			  //Blinky
						mapLayout[lineNumber][i] = 6;
					}
					if (line[i] == 'I') {			  //Inky
						mapLayout[lineNumber][i] = 7;
					}
					if (line[i] == 'N') {			  //Pinky
						mapLayout[lineNumber][i] = 8;
					}
					if (line[i] == 'C') {			  //Clyde
						mapLayout[lineNumber][i] = 9;
					}
					if (line[i] == 'H') {			  //Hometile for ghosts
						mapLayout[lineNumber][i] = 4;
					}
				}
			}
			inData.close();
		}
		return 1;
	}

	/*
	 * Depending on the position in the 2D dynamic array and its value
	 * we will create the correct object at the correct position aswell as
	 * store them in their respective dynamic arrays of objects with the correct length
	 * to maximize memory allocation.
	 */
	void Map::makeMapObjects() {
		wallObjects = new Pac::staticEntity*[wallCount];
		dotObjects = new Pac::staticEntity*[dotCount];
		fruitObjects = new Pac::staticEntity*[fruitCount];
		int w = 0, d=0, f=0;
		//std::cout << mapHeight << " " << mapWidth << " " << tileWidth << " " << tileHeight << std::endl;
		for(int i=0; i<mapHeight;i++) {
			for (int j=0;j<mapWidth;j++) {
				if (mapLayout[i][j] == 1) {
					wallObjects[w] = h->createWall(j,i,tileWidth,tileHeight);
					w += 1;
				}
				if (mapLayout[i][j] == 2) {
					dotObjects[d] = h->createDot(j,i,tileWidth,tileHeight,20);
					d += 1;
				}
				if (mapLayout[i][j] == 3) {
					fruitObjects[f] = h->createFruit(j,i,tileWidth,tileHeight,100);
					f += 1;
				}
				if (mapLayout[i][j] == 5) {
					p->setLocation(j,i);
					p->setStartTile(j,i);
					p->setDimensions(tileWidth, tileHeight);
					pacmanX = j;
					pacmanY = i;
				}
				if (mapLayout[i][j] == 6) {
					b->setLocation(j,i);
					b->setStartTile(j,i);
					b->setDimensions(tileWidth, tileHeight);
				}
				if (mapLayout[i][j] == 7) {
					in->setLocation(j,i);
					in->setStartTile(j,i);
					in->setDimensions(tileWidth, tileHeight);
				}
				if (mapLayout[i][j] == 8) {
					n->setLocation(j,i);
					n->setStartTile(j,i);
					n->setDimensions(tileWidth, tileHeight);
				}
				if (mapLayout[i][j] == 9) {
					c->setLocation(j,i);
					c->setStartTile(j,i);
					c->setDimensions(tileWidth, tileHeight);
				}
				if (mapLayout[i][j] == 4) {
					b->setStartPos(j,i);
					in->setStartPos(j,i);
					c->setStartPos(j,i);
					n->setStartPos(j,i);
				}
			}
		}
	}

	//get count of dot in maze starting from top left
	int Map::getDotCount(int x, int y) {
		int nbOfDot = 0;
		int found = 0;
		for(int i=0; i<mapHeight && found == 0;i++) {
				for (int j=0;j<mapWidth && found == 0;j++) {
					if (mapLayout[i][j] == 2) {
						nbOfDot += 1;
					}
					if(j == x && i == y) {
						found = 1;
					}
				}
		}
		return nbOfDot-1; //array starts at 0 not at 1.
	}
	//get count of fruit in maze starting from top left
	int Map::getFruitCount(int x, int y) {
		int nbOfFruit = 0;
		int found = 0;
		for(int i=0; i<mapHeight && found == 0;i++) {
				for (int j=0;j<mapWidth && found == 0;j++) {
					if (mapLayout[i][j] == 3) {
						nbOfFruit += 1;
					}
					if(j == x && i == y) {
						found = 1;
					}
				}
		}
		return nbOfFruit-1;
	}

	//returns int refering to element at this position
	int Map::getElementAtPosition(int x, int y) {
		return mapLayout[y][x];
	}

	//returns a pointer to dynamic array containing map
	int** Map::getMapLayout() {
		return mapLayout;
	}

	//returns the map width
	int Map::getWidth() {
		return mapWidth;
	}

	//returns the map height
	int Map::getHeight() {
		return mapHeight;
	}

	//checks if pacman is on dot or fruit which can be eaten and add score accordingly
	//if no more dots and fruits to eat this goes to new level where all dots and fruits will be shown again
	//ghosts move to base and pacman to its starting position without moving
	bool Map::updateMap() {
		positionArray = p->getPosition();
		pacmanX = positionArray[0];
		pacmanY = positionArray[1];
		int elementAtPosition = getElementAtPosition(pacmanX,pacmanY);
		int count = 0;
		int addScore = 0;
		switch ( elementAtPosition ) {
			case 2: //dot
				count = getDotCount(pacmanX,pacmanY);
				addScore = dotObjects[count]->eaten();
				if(addScore > 0) {
					eatenDot += 1;
				}
				break;
			case 3: //fruit
				count = getFruitCount(pacmanX,pacmanY);
				addScore = fruitObjects[count]->eaten();
				if(addScore > 0) {
					eatenFruit += 1;
					int time = 60*t->getTimeInMinutes() + t->getTimeInSeconds();
					b->setFrightened(time);
					n->setFrightened(time);
					in->setFrightened(time);
					c->setFrightened(time);
				}
				break;
		}
		score += addScore;
		if(eatenFruit == fruitCount && eatenDot == dotCount) {
			level += 1;
			eatenFruit = 0;
			eatenDot = 0;
			for(int i = 0; i< dotCount; i++) {
				dotObjects[i]->clearEaten();
			}
			for(int j= 0; j< fruitCount; j++) {
				fruitObjects[j]->clearEaten();
			}
			restart();
			return true;
		}
		else {
			return false;
		}
	}

	//move pacman and ghosts to starting position and clears ghosts frightened state and set objects to not moving
	void Map::restart() {
		p->moveToStartTile();
		p->clearMoving();
		b->moveToStartTile();
		b->clearFrightened();
		b->setDirection('i');
		n->moveToStartTile();
		n->clearFrightened();
		n->setDirection('i');
		in->moveToStartTile();
		in->clearFrightened();
		in->setDirection('i');
		c->moveToStartTile();
		c->clearFrightened();
		c->setDirection('i');
	}

	//add points to the score for when a ghost has been eaten
	void Map::addGhostPoints() {
		score = score + 1000;
	}

	Map::~Map() {
		for(int i = 0; i < mapHeight; i++) {
			delete [] mapLayout[i];
		}
		delete [] mapLayout;
		for (int j = 0; j < wallCount; j++) {
			delete [] wallObjects[j];
		}
		for (int k = 0; k < dotCount; k++) {
			delete [] dotObjects[k];
		}
		for (int l = 0; l < fruitCount; l++) {
			delete [] fruitObjects[l];
		}
		delete [] wallObjects;
		delete [] dotObjects;
		delete [] fruitObjects;
		delete h;
		delete p;
		delete b;
		delete n;
		delete in;
		delete c;
		delete t;
	}
}

