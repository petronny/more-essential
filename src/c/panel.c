#include "panel.h"

void upper_panel_update(Layer* layer, GContext* ctx) {
	GRect bounds = layer_get_bounds(layer);
	graphics_context_set_fill_color(ctx, settings.upper_panel_background_color);
	graphics_fill_rect(ctx, bounds, 0, GCornerNone);
}

void bottom_panel_update(Layer* layer, GContext* ctx) {
	GRect bounds = layer_get_bounds(layer);
	graphics_context_set_fill_color(ctx, settings.bottom_panel_background_color);
	graphics_fill_rect(ctx, bounds, 0, GCornerNone);
}

void panel_load() {
	panel_layer[0] = layer_create(GRect(0,0,window_bounds.size.w, window_bounds.size.h/3));
	panel_layer[1] = layer_create(GRect(0,window_bounds.size.h/3*2,window_bounds.size.w, window_bounds.size.h/3));
	layer_set_update_proc(panel_layer[0], upper_panel_update);
	layer_set_update_proc(panel_layer[1], bottom_panel_update);
	for(int i=0; i<2; i++) {
		layer_add_child(window_layer, panel_layer[i]);
		layer_mark_dirty(panel_layer[i]);
	}
}

void panel_destroy() {
	for(int i=0; i<2; i++)
		layer_destroy(panel_layer[i]);
}
