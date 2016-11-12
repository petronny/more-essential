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
	upper_panel_layer = layer_create(GRect(0,0,window_bounds.size.w, window_bounds.size.h/3));
	bottom_panel_layer = layer_create(GRect(0,window_bounds.size.h/3*2,window_bounds.size.w, window_bounds.size.h/3));
	layer_set_update_proc(upper_panel_layer, upper_panel_update);
	layer_set_update_proc(bottom_panel_layer, bottom_panel_update);
	layer_add_child(window_layer, upper_panel_layer);
	layer_add_child(window_layer, bottom_panel_layer);
	layer_mark_dirty(upper_panel_layer);
	layer_mark_dirty(bottom_panel_layer);
}

void panel_destroy() {
	layer_destroy(upper_panel_layer);
	layer_destroy(bottom_panel_layer);
}
