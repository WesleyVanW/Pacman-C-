#include "SDLFactory.h"
#include "Game.h"

int main( int argc, char *argv[]){
	Pac::abstractFactory* F = new SDLPac::SDLFactory();
	Pac::Game* g = new Pac::Game(F);
	g->start();
	//delete g;
	//delete F;
	return 0;
}



