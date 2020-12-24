/*
 * Display.h
 */

#ifndef DSTIKEOS_DISPLAY_H
#define DSTIKEOS_DISPLAY_H

#include <Eventually.h>
#include <SH1106Wire.h>
#include <OLEDDisplayFonts.h>

#include "core/images.h"
#include "Configuration.h"
#include "State.h"

#define OLED_SDA_PIN D1  // pin 5
#define OLED_SCL_PIN D2  // pin 4
#define OLED_ADDR 60  //0x3C
#define OLED_WIDTH 128
#define OLED_HEIGHT 64

class Display {
public:
	Display();
	void begin(std::shared_ptr<Configuration> config, std::shared_ptr<State> state);
	void render();
	void clear();
	void on();
	void off();
	void showSplash();
	bool clearSplash();
	void showStatusIcons(unsigned int);
	void string(int16_t x, int16_t y, const char* text, const uint8_t *fontData, OLEDDISPLAY_TEXT_ALIGNMENT align);
	void string(int16_t x, int16_t y, const char* text, const uint8_t *fontData) {
		string(x, y, text, fontData, TEXT_ALIGN_LEFT);
	};
	void loop();
	void showClock(tm);

	unsigned long displayTimeout;
	EvtTimeListener *displayTimer;


private:
	std::shared_ptr<Configuration> configuration;
	std::shared_ptr<State> state;

	SH1106Wire OLED = SH1106Wire(OLED_ADDR, OLED_SDA_PIN, OLED_SCL_PIN);
	bool splashHold = false;
};

#endif //DSTIKEOS_DISPLAY_H
