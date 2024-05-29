#include "screens.h"

#include <soogh.h>

#include "gui.h"

#include "config.h"
#include "tools-log.h"
#include "globals.h"
#include "soogh-debug.h"
#include <widgets/treemenu.h>

bool motoron1;
// C-style callbacks
void menu_close_cb(MenuItem* item, void* data);

void allOn()
{
	for (int i = 0; i < NUMBER_OF_MOTORS; i++)
	{	
		motorOn[i] = motoron1;
		drvs[i]->setDriverDirection((hbridge_direction_t)(motorOn[i]));
	}
	
}

MenuScreen::MenuScreen(SooghGUI& g) : Screen(g)
{
	menu.addCloseMenuButton();

	menu.addSeparator("Menu");

	menu.addSwitch("All motors on/off", &motoron1)->onChange([](MenuItem*, void*){ allOn();});
	
	auto sub1 = menu.addSubMenu("Motor 1");
	sub1->addSpinbox("speed ", &motorSpeed[0], 0, 10, 0)->onChange([](MenuItem*, void*){ drvs[0]->setDriverSpeed8Bits(motorSpeed[0] * SPEED_MULTIPLIER);});
	sub1->addSwitch("motor on/off", &motorOn[0])->onChange([](MenuItem*, void*){ drvs[0]->setDriverDirection((hbridge_direction_t)(motorOn[0]));});


	auto sub2 = menu.addSubMenu("Motor 2");
	sub2->addSpinbox("speed ", &motorSpeed[1], 0, 10, 0)->onChange([](MenuItem*, void*){ drvs[1]->setDriverSpeed8Bits(motorSpeed[1] * SPEED_MULTIPLIER);});
	sub2->addSwitch("motor on/off", &motorOn[1])->onChange([](MenuItem*, void*){ drvs[1]->setDriverDirection((hbridge_direction_t)(motorOn[1]));});


	auto sub3 = menu.addSubMenu("Motor 3");
	sub3->addSpinbox("speed ", &motorSpeed[2], 0, 10, 0)->onChange([](MenuItem*, void*){ drvs[2]->setDriverSpeed8Bits(motorSpeed[2] * SPEED_MULTIPLIER);});
	sub3->addSwitch("motor on/off", &motorOn[2])->onChange([](MenuItem*, void*){ drvs[2]->setDriverDirection((hbridge_direction_t)(motorOn[2]));});


	auto sub4 = menu.addSubMenu("Motor 4");
	sub4->addSpinbox("speed ", &motorSpeed[3], 0, 10, 0)->onChange([](MenuItem*, void*){ drvs[3]->setDriverSpeed8Bits(motorSpeed[3] * SPEED_MULTIPLIER);});
	sub4->addSwitch("motor on/off", &motorOn[3])->onChange([](MenuItem*, void*){ drvs[3]->setDriverDirection((hbridge_direction_t)(motorOn[3]));});

	menu.onClose(menu_close_cb, this);
	menu.open();
};

void menu_close_cb(MenuItem* item, void* data)
{
	gui.popScreen();
};

void MenuScreen::load()
{
	// Do not load my screen, menu is overlayed
};

void MenuScreen::loop()
{    
    return;
};

bool MenuScreen::handle(soogh_event_t e)
{	
	switch(e)
	{
		case KEY_A_SHORT:
		case KEY_A_LONG:
		case KEY_A_LONG_REPEAT:
			menu.sendKey(LV_KEY_LEFT);
			break;
		case KEY_B_SHORT:
			menu.sendKey(LV_KEY_ENTER);
			break;
		case KEY_C_SHORT:
		case KEY_C_LONG:
		case KEY_C_LONG_REPEAT:
			menu.sendKey(LV_KEY_RIGHT);
			break;
		case KEY_B_LONG:
			menu.sendKey(LV_KEY_ESC);
			break;
		case KEY_AC_LONG:
			gui.popScreen();
			return true;
		default: break;
	};
	return true;
};
