#ifndef ABSTRACTBUTTONHANDLER_H_
#define ABSTRACTBUTTONHANDLER_H_

namespace Pac {
	class abstractButtonHandler {
		public :
			virtual ~abstractButtonHandler();
			virtual char eventCheck() = 0;
	};
}

#endif /* ABSTRACTBUTTONHANDLER_H_ */
