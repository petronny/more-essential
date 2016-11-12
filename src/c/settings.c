#include "settings.h"

void settings_theme_default() {
	settings.clock_background_color = GColorWhite;
	settings.clock_foreground_color = GColorBlack;
	settings.battery_color_high = GColorDarkGreen;
	settings.battery_color_medium = GColorOrange;
	settings.battery_color_low = GColorRed;
	settings.bluetooth_color = GColorBlack;
	settings.upper_panel_background_color = GColorBlue;
	settings.upper_panel_foreground_color = GColorWhite;
	settings.bottom_panel_background_color = GColorBlue;
	settings.bottom_panel_foreground_color = GColorWhite;
}

void settings_theme_france() {
	settings.clock_background_color = GColorWhite;
	settings.clock_foreground_color = GColorBlack;
	settings.battery_color_high = GColorDarkGreen;
	settings.battery_color_medium = GColorOrange;
	settings.battery_color_low = GColorRed;
	settings.bluetooth_color = GColorBlack;
	settings.upper_panel_background_color = GColorBlue;
	settings.upper_panel_foreground_color = GColorWhite;
	settings.bottom_panel_background_color = GColorRed;
	settings.bottom_panel_foreground_color = GColorCyan;
}

void settings_theme_german() {
	settings.clock_background_color = GColorRed;
	settings.clock_foreground_color = GColorCyan;
	settings.battery_color_high = GColorDarkGreen;
	settings.battery_color_medium = GColorOrange;
	settings.battery_color_low = GColorRed;
	settings.bluetooth_color = GColorBlack;
	settings.upper_panel_background_color = GColorBlack;
	settings.upper_panel_foreground_color = GColorWhite;
	settings.bottom_panel_background_color = GColorFromHEX(0xFFAA00);
	settings.bottom_panel_foreground_color = GColorFromHEX(0x0055FF);
}

void settings_theme_italy() {
	settings.clock_background_color = GColorWhite;
	settings.clock_foreground_color = GColorBlack;
	settings.battery_color_high = GColorDarkGreen;
	settings.battery_color_medium = GColorOrange;
	settings.battery_color_low = GColorRed;
	settings.bluetooth_color = GColorBlack;
	settings.upper_panel_background_color = GColorFromHEX(0x00AA00);
	settings.upper_panel_foreground_color = GColorFromHEX(0xFF55FF);
	settings.bottom_panel_background_color = GColorRed;
	settings.bottom_panel_foreground_color = GColorCyan;
}

void settings_theme_russia() {
	settings.clock_background_color = GColorFromHEX(0x0000AA);
	settings.clock_foreground_color = GColorFromHEX(0xFFFF55);
	settings.battery_color_high = GColorDarkGreen;
	settings.battery_color_medium = GColorOrange;
	settings.battery_color_low = GColorRed;
	settings.bluetooth_color = GColorBlack;
	settings.upper_panel_background_color = GColorWhite;
	settings.upper_panel_foreground_color = GColorBlack;
	settings.bottom_panel_background_color = GColorRed;
	settings.bottom_panel_foreground_color = GColorCyan;
}

void settings_default_settings() {
	// Initialize the default settings
	settings.theme = 0;
	settings.bluetooth_vibrate = true;
	settings.clock_hourly_vibrate = true;
	settings.battery_display = true;
	settings.bluetooth_display = true;
	settings.upper_panel_animations = true;
	settings.bottom_panel_animations = true;
	settings_theme_default();
}
