#include "panel.h"

LayerUpdateProc panel_layer_update[2]={upper_panel_update,bottom_panel_update};

void upper_panel_update(Layer* layer, GContext* ctx) {
	GRect bounds = layer_get_bounds(layer);
	graphics_context_set_fill_color(ctx, settings.panel_background_color[0]);
	graphics_fill_rect(ctx, bounds, 0, GCornerNone);
}

void bottom_panel_update(Layer* layer, GContext* ctx) {
	GRect bounds = layer_get_bounds(layer);
	graphics_context_set_fill_color(ctx, settings.panel_background_color[1]);
	graphics_fill_rect(ctx, bounds, 0, GCornerNone);
}

void panel_load() {
	panel_layer[0] = layer_create(GRect(0,0,window_bounds.size.w, window_bounds.size.h/3));
	panel_layer[1] = layer_create(GRect(0,window_bounds.size.h/3*2,window_bounds.size.w, window_bounds.size.h/3));
	for(int i=0;i<2;i++){
		layer_set_update_proc(panel_layer[i], panel_layer_update[i]);
		layer_add_child(window_layer, panel_layer[i]);
		layer_mark_dirty(panel_layer[i]);
	}
}

void panel_destroy() {
	for(int i=0;i<2;i++)
		layer_destroy(panel_layer[i]);
}
