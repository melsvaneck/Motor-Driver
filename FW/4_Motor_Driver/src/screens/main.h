#ifndef __SCREENS_MAIN_H
#define __SCREENS_MAIN_H

#include <stdlib.h>
#include <stdint.h>

#include <soogh.h>

#include "gui.h"
#include "globals.h"

class MotorPanel;

/*** MAIN ************************************************************************************/
class MainScreen : public Screen
{
    public:
		MainScreen(SooghGUI& g);
		virtual ScreenType type() { return ScreenType::MAIN; };

        virtual void loop();
		virtual bool handle(soogh_event_t);
		~MainScreen();
	
	private:
		MotorPanel* _mps[NUMBER_OF_MOTORS];

		time_t _next_update = 0;
};

#endif // __SCREENS_MAIN_H
