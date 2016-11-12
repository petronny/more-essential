#include <pebble.h>
#include "settings.h"
#include "window.h"
#include "clock.h"
#include "battery.h"
#include "bluetooth.h"
#include "panel.h"

static void main_window_load(Window* window) {
	// Get information about the Window
	window_layer = window_get_root_layer(window);
	window_bounds = layer_get_bounds(window_layer);
	clock_load();
	battery_load();
	bluetooth_load();
	panel_load();
//	pins_load();
}

static void main_window_unload(Window* window) {
	clock_destroy();
	battery_destroy();
	bluetooth_destroy();
	panel_destroy();
//	pins_destroy();
}

static void init() {
	settings_init();
	// Create main Window element and assign to pointer
	main_window = window_create();
	// Set handlers to manage the elements inside the Window
	window_set_window_handlers(main_window, (WindowHandlers) {
		.load = main_window_load,
		 .unload = main_window_unload
	});
	// Show the Window on the watch, with animated=true
	window_stack_push(main_window, true);
	clock_init();
	battery_init();
	bluetooth_init();
}

static void deinit() {
	// Destroy Window
	window_destroy(main_window);
}

int main(void) {
	init();
	app_event_loop();
	deinit();
}
