#pragma once
#include <pebble.h>
#include "clock.h"
#include "battery.h"
#include "bluetooth.h"
#include "panel.h"
#include "pin.h"

#define SETTINGS_KEY 1

typedef struct ClaySettings {
	int theme;
	bool bluetooth_vibrate;
	bool clock_hourly_vibrate;
	GColor clock_background_color;
	GColor clock_foreground_color;
	bool battery_display;
	GColor battery_color_high;
	GColor battery_color_medium;
	GColor battery_color_low;
	bool bluetooth_display;
	GColor bluetooth_color;
	GColor panel_background_color[2];
	GColor panel_foreground_color[2];
	int pin[6];
} ClaySettings;

ClaySettings settings;

void settings_theme_default();
void settings_theme_france();
void settings_theme_german();
void settings_theme_italy();
void settings_theme_russia();
void settings_default_settings();
void settings_load_settings();
void settings_update_display();
void settings_save_settings();
void settings_inbox_received_handler(DictionaryIterator* iter, void* context);
void settings_init();
