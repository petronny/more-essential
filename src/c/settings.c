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

void settings_load_settings() {
	// Load the default settings
	settings_default_settings();
	// Read settings from persistent storage, if they exist
	persist_read_data(SETTINGS_KEY, &settings, sizeof(settings));
}

void settings_update_display() {
	// Update the display elements
	text_layer_set_background_color(clock_text_layer, settings.clock_background_color);
	text_layer_set_text_color(clock_text_layer, settings.clock_foreground_color);
	layer_set_hidden(battery_layer, !settings.battery_display);
	layer_mark_dirty(battery_layer);
	layer_set_hidden(bluetooth_layer, !settings.bluetooth_display);
	layer_mark_dirty(bluetooth_layer);
	layer_mark_dirty(panel_layer[0]);
	layer_mark_dirty(panel_layer[1]);
}

void settings_save_settings() {
	// Save the settings to persistent storage
	persist_write_data(SETTINGS_KEY, &settings, sizeof(settings));
	// Update the display based on new settings
	settings_update_display();
}

void settings_inbox_received_handler(DictionaryIterator* iter, void* context) {
	// Handle the response from AppMessage
	Tuple* clock_background_color = dict_find(iter, MESSAGE_KEY_clock_background_color);
	if(clock_background_color)
		settings.clock_background_color = GColorFromHEX(clock_background_color->value->int32);
	Tuple* clock_foreground_color = dict_find(iter, MESSAGE_KEY_clock_foreground_color);
	if(clock_foreground_color)
		settings.clock_foreground_color = GColorFromHEX(clock_foreground_color->value->int32);
	Tuple* bluetooth_vibrate = dict_find(iter, MESSAGE_KEY_bluetooth_vibrate);
	if(bluetooth_vibrate)
		settings.bluetooth_vibrate = bluetooth_vibrate->value->int32 == 1;
	Tuple* clock_hourly_vibrate = dict_find(iter, MESSAGE_KEY_clock_hourly_vibrate);
	if(clock_hourly_vibrate)
		settings.clock_hourly_vibrate = clock_hourly_vibrate->value->int32 == 1;
	Tuple* battery_display = dict_find(iter, MESSAGE_KEY_battery_display);
	if(battery_display)
		settings.battery_display = battery_display->value->int32 == 1;
	Tuple* battery_color_high = dict_find(iter, MESSAGE_KEY_battery_color_high);
	if(battery_color_high)
		settings.battery_color_high = GColorFromHEX(battery_color_high->value->int32);
	Tuple* battery_color_medium = dict_find(iter, MESSAGE_KEY_battery_color_medium);
	if(battery_color_medium)
		settings.battery_color_medium = GColorFromHEX(battery_color_medium->value->int32);
	Tuple* battery_color_low = dict_find(iter, MESSAGE_KEY_battery_color_low);
	if(battery_color_low)
		settings.battery_color_low = GColorFromHEX(battery_color_low->value->int32);
	Tuple* bluetooth_display = dict_find(iter, MESSAGE_KEY_bluetooth_display);
	if(bluetooth_display)
		settings.bluetooth_display = bluetooth_display->value->int32 == 1;
	Tuple* bluetooth_color = dict_find(iter, MESSAGE_KEY_bluetooth_color);
	if(bluetooth_color)
		settings.bluetooth_color = GColorFromHEX(bluetooth_color->value->int32);
	Tuple* upper_panel_background_color = dict_find(iter, MESSAGE_KEY_upper_panel_background_color);
	if(upper_panel_background_color)
		settings.upper_panel_background_color = GColorFromHEX(upper_panel_background_color->value->int32);
	Tuple* upper_panel_foreground_color = dict_find(iter, MESSAGE_KEY_upper_panel_foreground_color);
	if(upper_panel_foreground_color)
		settings.upper_panel_foreground_color = GColorFromHEX(upper_panel_foreground_color->value->int32);
	Tuple* bottom_panel_background_color = dict_find(iter, MESSAGE_KEY_bottom_panel_background_color);
	if(bottom_panel_background_color)
		settings.bottom_panel_background_color = GColorFromHEX(bottom_panel_background_color->value->int32);
	Tuple* bottom_panel_foreground_color = dict_find(iter, MESSAGE_KEY_bottom_panel_foreground_color);
	if(bottom_panel_foreground_color)
		settings.bottom_panel_foreground_color = GColorFromHEX(bottom_panel_foreground_color->value->int32);
	Tuple* theme = dict_find(iter, MESSAGE_KEY_theme);
	if(theme)
		settings.theme = (int)theme->value->uint8-'0';
	switch(settings.theme) {
		case 1:
			settings_theme_default();
			break;
		case 2:
			settings_theme_france();
			break;
		case 3:
			settings_theme_german();
			break;
		case 4:
			settings_theme_italy();
			break;
		case 5:
			settings_theme_russia();
			break;
	}
	// Save the new settings to persistent storage
	settings_save_settings();
}

void settings_init() {
	settings_load_settings();
	// Open AppMessage connection
	app_message_register_inbox_received(settings_inbox_received_handler);
	app_message_open(256, 256);
}
