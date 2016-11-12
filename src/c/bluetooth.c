#include "bluetooth.h"

int bluetooth_layer_height=4;

void bluetooth_callback(bool connected) {
	//bluetooth_state=connected;
	layer_set_hidden(bluetooth_layer, !connected || !settings.bluetooth_display);
	if(!connected && settings.bluetooth_vibrate) {
		// Issue a vibrating alert
		vibes_double_pulse();
	}
}

void bluetooth_update(Layer* layer, GContext* ctx) {
	GRect bounds = layer_get_bounds(layer);
	graphics_context_set_fill_color(ctx, settings.bluetooth_color);
	graphics_fill_rect(ctx, bounds, 0, GCornerNone);
}

void bluetooth_load() {
	bluetooth_layer = layer_create(GRect(0,window_bounds.size.h/3,window_bounds.size.w, bluetooth_layer_height));
	layer_set_update_proc(bluetooth_layer, bluetooth_update);
	layer_mark_dirty(bluetooth_layer);
	layer_set_hidden(bluetooth_layer, !settings.bluetooth_display);
	layer_add_child(window_layer, bluetooth_layer);
}

void bluetooth_init() {
	connection_service_subscribe((ConnectionHandlers) {
		.pebble_app_connection_handler = bluetooth_callback
	});
	// Show the correct state of the BT connection from the start
	bluetooth_callback(connection_service_peek_pebble_app_connection());
}

void bluetooth_destroy() {
	layer_destroy(bluetooth_layer);
}
