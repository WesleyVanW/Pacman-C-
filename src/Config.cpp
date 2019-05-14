#include "Config.h"

namespace Pac {

	Config::Config(movingEntity* p, movingEntity* b, movingEntity* in, movingEntity* n, movingEntity* c) {
		this->p = p;
		this->b = b;
		this->in = in;
		this->n = n;
		this->c = c;
		this->mapNaam = "";
		this->tileWidth = 0;
		this->tileHeight = 0;
		this->lives=0;
		this->pacSpeed=0;
		this->frightenTime=0;
		this->huntTime=0;
		this->homeTime=0;
		this->bSpeed=0;
		this->bHomeTileX=0;
		this->bHomeTileY=0;
		this->iSpeed=0;
		this->iHomeTileX=0;
		this->iHomeTileY=0;
		this->pSpeed=0;
		this->pHomeTileX=0;
		this->pHomeTileY=0;
		this->cSpeed=0;
		this->cHomeTileX=0;
		this->cHomeTileY=0;
		this->speed = 0;
	}

	//Reads a text file and adjust setting based on its content
	bool Config::loadConfig() {
		std::ifstream file;
		file.open("config.txt");
		int counter = 0;
		if(!file.is_open()) {
			return false;
		}
		else {
			std::string word;
			while(file >> word) {
				counter += 1;
				if(counter == 2) {
					mapNaam = word;
				}
				if(counter == 4) {
					tileWidth = std::stoi(word);
				}
				if(counter == 6) {
					tileHeight = std::stoi(word);
					if(tileHeight!=tileWidth) {
						return false;
					}
				}
				if(counter == 8) {
					lives = std::stoi(word);
					if(lives < 0 || lives > 3) {
						return false;
					}
					else {
						p->setLives(lives);
					}
				}
				if(counter == 10) {
					pacSpeed = std::stoi(word);
					p->setSpeed(pacSpeed);
				}
				if(counter == 12) {
					frightenTime = std::stoi(word);
					b->setFrightenTime(frightenTime);
					in->setFrightenTime(frightenTime);
					n->setFrightenTime(frightenTime);
					c->setFrightenTime(frightenTime);
				}
				if(counter == 14) {
					huntTime = std::stoi(word);
				}
				if(counter == 16) {
					homeTime = std::stoi(word);
				}
				if(counter == 18) {
					bSpeed = std::stof(word);
					b->setSpeed(bSpeed);
				}
				if(counter == 20) {
					bHomeTileX = std::stoi(word);
				}
				if(counter == 22) {
					bHomeTileY = std::stoi(word);
					b->setHomeTile(bHomeTileX,bHomeTileY);
				}
				if(counter == 24) {
					iSpeed = std::stof(word);
					in->setSpeed(iSpeed);
				}
				if(counter == 26) {
					iHomeTileX = std::stoi(word);
				}
				if(counter == 28) {
					iHomeTileY = std::stoi(word);
					in->setHomeTile(iHomeTileX,iHomeTileY);
				}
				if(counter == 30) {
					pSpeed = std::stof(word);
					n->setSpeed(pSpeed);
				}
				if(counter == 32) {
					pHomeTileX = std::stoi(word);
				}
				if(counter == 34) {
					pHomeTileY = std::stoi(word);
					n->setHomeTile(pHomeTileX,pHomeTileY);
				}
				if(counter == 36) {
					cSpeed = std::stof(word);
					speed = cSpeed/100.;
					c->setSpeed(cSpeed);
				}
				if(counter == 38) {
					cHomeTileX = std::stoi(word);
				}
				if(counter == 40) {
					cHomeTileY = std::stoi(word);
					c->setHomeTile(cHomeTileX,cHomeTileY);
				}
			}
		}
		return true;

	}
	//returns name of txt file containing map
	std::string Config::getMapnaam() {
		return mapNaam;
	}
	//returns time ghosts should hunt pacman
	int Config::getHunttime() {
		return huntTime;
	}
	//returns time ghosts should move to hometile
	int Config::getHometime() {
		return homeTime;
	}
	//returns tilewidth
	int Config::getTileWidth() {
		return tileWidth;
	}
	//returns tileheight
	int Config::getTileHeight() {
		return tileHeight;
	}

	Config::~Config() {
		delete p;
		delete b;
		delete in;
		delete n;
		delete c;
	}

}




