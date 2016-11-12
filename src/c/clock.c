#include "window.h"
#include "clock.h"
void clock_load() {
	// Create the TextLayer with specific bounds
	clock_text_layer = text_layer_create(GRect(0, window_bounds.size.h/3, window_bounds.size.w, window_bounds.size.h/3));
	// Improve the layout to be more like a watchface
	text_layer_set_background_color(clock_text_layer, settings.clock_background_color);
	text_layer_set_text_color(clock_text_layer, settings.clock_foreground_color);
	text_layer_set_text(clock_text_layer, "00:00");
	text_layer_set_font(clock_text_layer, fonts_get_system_font(FONT_KEY_LECO_42_NUMBERS));
	text_layer_set_text_alignment(clock_text_layer, GTextAlignmentCenter);
	// Add it as a child layer to the Window's root layer
	layer_add_child(window_layer, text_layer_get_layer(clock_text_layer));
}

void clock_destroy() {
	text_layer_destroy(clock_text_layer);
}


void clock_update() {
	// Get a tm structure
	time_t temp = time(NULL);
	struct tm* tick_time = localtime(&temp);
	// Write the current hours and minutes into a buffer
	static char s_buffer[8];
	strftime(s_buffer, sizeof(s_buffer), clock_is_24h_style() ? "%H:%M" : "%I:%M", tick_time);
	// Display this time on the TextLayer
	text_layer_set_text(clock_text_layer, s_buffer);
}

void clock_tick_handler(struct tm* tick_time, TimeUnits units_changed) {
	clock_update();
}

void clock_init() {
	// Make sure the time is displayed from the start
	clock_update();
	// Register with TickTimerService
	tick_timer_service_subscribe(MINUTE_UNIT, clock_tick_handler);
}
