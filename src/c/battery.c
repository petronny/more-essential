#include "battery.h"

int battery_layer_height=4;

void battery_callback(BatteryChargeState state) {
	// Record the new battery level
	battery_level = state.charge_percent;
	// Update meter
	if(settings.battery_display)
		layer_mark_dirty(battery_layer);
}

void battery_update(Layer* layer, GContext* ctx) {
	GRect bounds = layer_get_bounds(layer);
	// Find the width of the bar
	int width = (int)(float)(((float)battery_level / 100.0F) * bounds.size.w);
	// Draw the background
	graphics_context_set_fill_color(ctx, GColorClear);
	graphics_fill_rect(ctx, bounds, 0, GCornerNone);
	// Draw the bar
	graphics_context_set_fill_color(ctx, settings.battery_color_low);
	if(battery_level>=30)
		graphics_context_set_fill_color(ctx, settings.battery_color_medium);
	if(battery_level>=70)
		graphics_context_set_fill_color(ctx, settings.battery_color_high);
	graphics_fill_rect(ctx, GRect(0, 0, width, bounds.size.h), 0, GCornerNone);
}

void battery_load() {
	// Create battery meter Layer
	battery_layer = layer_create(GRect(0,window_bounds.size.h/3*2-battery_layer_height,window_bounds.size.w, battery_layer_height));
	layer_set_update_proc(battery_layer, battery_update);
	layer_set_hidden(battery_layer, !settings.battery_display);
	layer_add_child(window_layer, battery_layer);
}

void battery_init() {
	// Register for battery level updates
	battery_state_service_subscribe(battery_callback);
	// Ensure battery level is displayed from the start
	battery_callback(battery_state_service_peek());
}

void battery_destroy() {
	layer_destroy(battery_layer);
}

