#include "main.h"

#include "screens.h"

#include <memory>
#include <soogh.h>

#include "gui.h"

#include "config.h"
#include "tools-log.h"
#include "globals.h"


lv_style_t 	style_font26;

uint8_t prec;

const char *unit_V, *unit_A;

// C-style callbacks

/*********************************************************************************************************************************/

class MotorPanel
{
	public:
		MotorPanel(lv_obj_t* parent, const uint8_t num, M5UnitHbridge& drv_in);
		~MotorPanel() {};
		void setVoltage(uint8_t num);
		void setSpeed(uint8_t num);
		void setStatus(uint8_t num);

	lv_obj_t	*box;

	private:
		int _num;
		M5UnitHbridge& drv;
		lv_obj_t	*lbl_m, *vlt_Label, *_spd_Label;
		lv_style_t 	style_font26, style_font22;

};

void MotorPanel::setVoltage(uint8_t num)
{
	lv_label_set_text_fmt(vlt_Label, "%.1f V",  vin_raw[num]);
};

void MotorPanel::setSpeed(uint8_t num)
{
	lv_label_set_text_fmt(_spd_Label, "Speed %i%%", int(motorSpeed[num] * SPEED_PERCENT));
};

void MotorPanel::setStatus(uint8_t num)
{
 if (num == HBRIDGE_FORWARD | num == HBRIDGE_BACKWARD)lv_obj_set_style_bg_color(lbl_m, COLOR_GREEN, 0);
 else lv_obj_set_style_bg_color(lbl_m, COLOR_YELLOW_LIGHT(1), 0);
};

MotorPanel::MotorPanel(lv_obj_t* parent, const uint8_t num_in, M5UnitHbridge& drv_in)
	 : _num(num_in), drv(drv_in)
{
	lv_color_t color1 = COLOR_BLACK;
	unit_V =   "V";
	unit_A =   "mA";
	prec =   1;
	color1 = COLOR_YELLOW;
	lv_color_t color2 = lv_color_lighten(color1, 4);

	box = lv_obj_create(parent);

	char integer_string[32];
	sprintf(integer_string, "%d", num_in);
	char top_Label[64] = "Motor ";
	strcat(top_Label, integer_string); // top_Label now contains "Integer: 1234"

	//Background 
	{
		lv_obj_set_size(box, DISPLAY_WIDTH/2, DISPLAY_HEIGHT/2);
		lv_obj_set_style_border_width(box, 3, 0);
		lv_obj_set_style_pad_all(box, 5, 0);
		lv_obj_set_style_border_color(box, COLOR_WHITE, 0);
		lv_obj_set_style_bg_color(box, COLOR_WHITE, 0);
	}
	
	lv_style_init(&style_font26);
	lv_style_set_text_font(&style_font26, &lv_font_montserrat_26);

	lv_style_init(&style_font22);
	lv_style_set_text_font(&style_font22, &lv_font_montserrat_22);

	// Top label
	{
		lbl_m = lv_label_create(box);
		lv_obj_set_style_border_width(lbl_m, 1, 0);
		lv_obj_set_size(lbl_m, (DISPLAY_WIDTH/2) - 20, 25);
		lv_obj_align(lbl_m, LV_ALIGN_TOP_MID, 0, 0);
		lv_obj_set_style_text_color(lbl_m, COLOR_GREY, LV_PART_ANY);
		lv_obj_set_style_text_align(lbl_m, LV_TEXT_ALIGN_CENTER, 0);
		lv_label_set_text(lbl_m, top_Label);
		lv_obj_set_style_bg_opa(lbl_m, LV_OPA_COVER, 0);
	}
	
	// Voltage label
	{
		vlt_Label = lv_label_create(box);
		lv_obj_set_style_border_width(vlt_Label, 1, 0);
		lv_obj_set_size(vlt_Label, (DISPLAY_WIDTH/2) - 20, 35);
		lv_obj_align_to(vlt_Label, lbl_m, LV_ALIGN_OUT_BOTTOM_MID, 0, 0);
		lv_obj_add_style(vlt_Label, &style_font26, 0);
		lv_obj_set_style_text_color(vlt_Label, COLOR_BLACK, LV_PART_ANY);
		lv_obj_set_style_text_align(vlt_Label, LV_TEXT_ALIGN_CENTER, 0);
		lv_label_set_text(vlt_Label, "<Voltage>");
		lv_obj_set_style_bg_opa(vlt_Label, LV_OPA_COVER, 0);
	};

	// Current label
	{
		_spd_Label = lv_label_create(box);
		lv_obj_set_style_border_width(_spd_Label, 1, 0);
		lv_obj_set_size(_spd_Label, (DISPLAY_WIDTH/2) - 20, 35);
		lv_obj_align_to(_spd_Label, vlt_Label, LV_ALIGN_OUT_BOTTOM_MID, 0, 0);
		lv_obj_add_style(_spd_Label, &style_font22, 0);
		lv_obj_set_style_text_color(_spd_Label, COLOR_BLACK, LV_PART_ANY);
		lv_obj_set_style_text_align(_spd_Label, LV_TEXT_ALIGN_CENTER, 0);
		lv_label_set_text(_spd_Label, "<Speed>");
		lv_obj_set_style_bg_opa(_spd_Label, LV_OPA_COVER, 0);
	};
	
};

MainScreen::MainScreen(SooghGUI& g) : Screen(g)
{
	// make screen for each motor
	for (int i = 0; i < 4; i++)
	{
		_mps[i] = new MotorPanel(_screen, 1, *(drvs[i]));
	}

	// align panels to eachother
	lv_obj_align_to(_mps[1]->box, _mps[0]->box, LV_ALIGN_OUT_RIGHT_MID, 0, 0);
	lv_obj_align_to(_mps[2]->box, _mps[0]->box, LV_ALIGN_OUT_BOTTOM_MID, 0, 0);
	lv_obj_align_to(_mps[3]->box, _mps[1]->box, LV_ALIGN_OUT_BOTTOM_MID, 0, 0);

};

MainScreen::~MainScreen()
{
	if(_mps[0] != nullptr)
		delete(_mps[0]);
	if(_mps[1] != nullptr)
		delete(_mps[1]);
	if(_mps[2] != nullptr)
		delete(_mps[2]);
	if(_mps[3] != nullptr)
		delete(_mps[3]);
};

void MainScreen::loop()
{	
	time_t now = millis();
	if(now < _next_update)
		return;

	_next_update = now + MAIN_LOOP_MS;

	for (int i = 0; i < NUMBER_OF_MOTORS; i++)
	{
		_mps[i]->setVoltage(i);
		_mps[i]->setSpeed(i);
		_mps[i]->setStatus(drvs[i]->getDriverDirection());
	}
	return;
};

bool MainScreen::handle(soogh_event_t key)
{
	switch(key)
	{
		case KEY_A_SHORT:
			break;
		case KEY_B_SHORT:
			return true;
		case KEY_C_SHORT:
			break;
		case KEY_B_LONG:
		gui.pushScreen(std::make_shared<MenuScreen>(gui));
		default: break;
	};
	return true;
};
