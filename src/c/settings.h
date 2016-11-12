#pragma once
#include <pebble.h>

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
	GColor upper_panel_background_color;
	GColor upper_panel_foreground_color;
	bool upper_panel_animations;
	int upper_panel_pin_1;
	int upper_panel_pin_2;
	int upper_panel_pin_3;
	GColor bottom_panel_background_color;
	GColor bottom_panel_foreground_color;
	bool bottom_panel_animations;
	int bottom_panel_pin_1;
	int bottom_panel_pin_2;
	int bottom_panel_pin_3;
} ClaySettings;

ClaySettings settings;

void settings_theme_default();
void settings_theme_france();
void settings_theme_german();
void settings_theme_italy();
void settings_theme_russia();
void settings_default_settings();
