#ifndef CONFIG_H_
#define CONFIG_H_

#include "movingEntity.h"
#include <sstream>
#include <iostream>
#include <fstream>

namespace Pac {
	class Config {
	public :
		Config(movingEntity* p, movingEntity* b, movingEntity* i, movingEntity* n, movingEntity* c);
		bool loadConfig();
		std::string getMapnaam();
		int getHunttime();
		int getHometime();
		int getTileWidth();
		int getTileHeight();
		virtual ~Config();
	private :
		movingEntity* p;
		movingEntity* b;
		movingEntity* in;
		movingEntity* n;
		movingEntity* c;
		std::string mapNaam;
		int tileWidth;
		int tileHeight;
		int lives;
		int pacSpeed;
		int frightenTime;
		int huntTime;
		int homeTime;
		float bSpeed;
		int bHomeTileX;
		int bHomeTileY;
		float iSpeed;
		int iHomeTileX;
		int iHomeTileY;
		float pSpeed;
		int pHomeTileX;
		int pHomeTileY;
		float cSpeed;
		int cHomeTileX;
		int cHomeTileY;
		float speed;

	};
}



#endif /* CONFIG_H_ */
