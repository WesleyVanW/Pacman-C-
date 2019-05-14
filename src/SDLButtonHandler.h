#ifndef SDLBUTTONHANDLER_H_
#define SDLBUTTONHANDLER_H_

#include "abstractButtonHandler.h"
#include "SDL.h"

namespace SDLPac {
	class SDLButtonHandler : public Pac::abstractButtonHandler {
		public:
			virtual ~SDLButtonHandler();
			char eventCheck();
	};
}



#endif /* SDLBUTTONHANDLER_H_ */
