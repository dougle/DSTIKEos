/*
 * Display.cpp
 */

#include "Display.h"
#include "../version.h"

Display::Display() {}

void Display::begin(std::shared_ptr<Configuration> config, std::shared_ptr<State> state) {
	Serial.println("Begin display");
	this->configuration = config;
	this->state = state;

	this->OLED.init();
	// flip to fit for the Watch
	this->OLED.flipScreenVertically();
	// default font
	this->OLED.setFont(ArialMT_Plain_10);
	// default text alignment
	this->OLED.setTextAlignment(TEXT_ALIGN_LEFT);

	this->on();
	// clear the display
	this->clear();
	// show the content (Write the buffer to the display memory)
	this->render();
}

void Display::loop() {
	Serial.println("Display loop");
}

bool Display::clearSplash() {
	Serial.println("Clearing splash");

	this->splashHold = false;
	this->clear();
}

void Display::showSplash() {
	Serial.println("Displaying splash");

	this->clear();

	this->string(OLED_WIDTH/2,0, (char *)"DSTIKEos", ArialMT_Plain_16, TEXT_ALIGN_CENTER);
	this->string(OLED_WIDTH,OLED_HEIGHT-12, (char *)"v" DSTIKEOS_VERSION, ArialMT_Plain_10, TEXT_ALIGN_RIGHT);

	this->render();

	this->splashHold = true;
}

void Display::showClock(tm local_time) {
	if(this->splashHold) return;

	if((*this->state).rendered_time.tm_sec != local_time.tm_sec) {
		// clear the area to be updated
		this->OLED.setColor(BLACK);
		int time_font_width = 18;
		int time_font_width_sep = 5;
		int y_offset = 15;

		// mask out seconds
		this->OLED.fillRect((OLED_WIDTH/2)+time_font_width-time_font_width_sep, y_offset, 2*time_font_width, 22);

		if((*this->state).rendered_time.tm_min != local_time.tm_min) {
			// mask out minutes
			this->OLED.fillRect((OLED_WIDTH/2)-time_font_width, y_offset, 2*time_font_width, 22);

			if((*this->state).rendered_time.tm_hour != local_time.tm_hour) {
				// mask out hours
				this->OLED.fillRect((OLED_WIDTH/2)-(time_font_width*3)-time_font_width_sep, y_offset, 2*time_font_width, 22);

				if((*this->state).rendered_time.tm_mday != local_time.tm_mday) {
					// clear the whole clock
					this->OLED.fillRect(0, y_offset, OLED_WIDTH, 28);
				}
			}
		}

		(*this->state).rendered_time = local_time;
	}

	this->OLED.setColor(WHITE);

	char formatted_time[20];
	strftime(formatted_time, 20, (*this->configuration).Time_Format, &local_time);
	this->string(OLED_WIDTH/2, 10, formatted_time, ArialMT_Plain_16, TEXT_ALIGN_CENTER);

	char formatted_date[30];
	strftime(formatted_date, 30, (*this->configuration).Date_Format, &local_time);
	this->string(OLED_WIDTH/2, 28, formatted_date, ArialMT_Plain_10, TEXT_ALIGN_CENTER);
}

/**
 * Sets non content UI elements, icons etc
 * @param int wifi 0=Connecting 1=Station 2=AP
 */
void Display::showStatusIcons(unsigned int wifi) {
	if(this->splashHold) return;

	Serial.println("Displaying Status Icons");
	Serial.printf("wifi is: %d\n", wifi);

	switch (wifi) {
		case 0:
			this->OLED.drawXbm(OLED_WIDTH - wifi_01_width, 0, wifi_01_width, wifi_01_height, wifi_01_bits);
			this->string(OLED_WIDTH - wifi_01_width - 1,0, "!", ArialMT_Plain_10, TEXT_ALIGN_RIGHT);
			break;
		case 1:
			this->OLED.drawXbm(OLED_WIDTH - wifi_01_width, 0, wifi_01_width, wifi_01_height, wifi_01_bits);
			break;
		case 2:
			this->OLED.drawXbm(OLED_WIDTH - wifi_01_width, 0, wifi_01_width, wifi_01_height, wifi_01_bits);
			this->string(int16_t(OLED_WIDTH - wifi_01_width - 1),int16_t(0), "AP", ArialMT_Plain_10, TEXT_ALIGN_RIGHT);
			break;
	}

	this->render();
}

void Display::clear() {
	if(this->splashHold) return;

	Serial.println("Clearing display");

	this->OLED.clear();
	this->render();
}

void Display::string(int16_t x, int16_t y, const char * text, const uint8_t *fontData, OLEDDISPLAY_TEXT_ALIGNMENT align = TEXT_ALIGN_LEFT) {
	Serial.printf("Setting display string: %s\n", text);

	this->OLED.setFont(fontData);
	this->OLED.setTextAlignment(align);

	this->OLED.drawString(x, y, String(text));
}

void Display::on() {
	Serial.println("Display on");
	this->OLED.displayOn();
	(*state).display_on = true;
}

void Display::off() {
	Serial.println("Display off");
	this->OLED.displayOff();
	(*state).display_on = false;
}

void Display::render() {
	if(this->splashHold) return;

	Serial.println("Rendering display");
	this->OLED.display();
}