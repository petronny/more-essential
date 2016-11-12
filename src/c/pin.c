#include "pin.h"

static Layer* pin_canvas_layer;
static GDrawCommandImage* s_command_image;
static TextLayer* pin_text_layer;
static void update_proc(Layer* layer, GContext* ctx) {
	// Place image in the center of the Window
	GSize img_size = gdraw_command_image_get_bounds_size(s_command_image);
	GRect bounds = layer_get_bounds(layer);
	const GEdgeInsets frame_insets = {
		.top = (bounds.size.h - img_size.h) / 2,
		.left = (bounds.size.w - img_size.w) / 2
	};
	// If the image was loaded successfully...
	if(s_command_image) {
		// Draw it
		gdraw_command_image_draw(ctx, s_command_image, grect_inset(bounds, frame_insets).origin);
	}
}
static void pins_load() {
	// Load the image and check it was succcessful
	s_command_image = gdraw_command_image_create_with_resource(RESOURCE_ID_CALENDAR);
	// Create canvas Layer and set up the update procedure
	pin_canvas_layer = layer_create(GRect(0,0,window_bounds.size.w/3,window_bounds.size.h/3*5/8));
	layer_set_update_proc(pin_canvas_layer, update_proc);
	layer_add_child(window_layer, pin_canvas_layer);
	GRect canvas_layer_bounds=layer_get_bounds(pin_canvas_layer);
	pin_text_layer = text_layer_create(GRect(0, canvas_layer_bounds.size.h, canvas_layer_bounds.size.w,window_bounds.size.h/3-canvas_layer_bounds.size.h));
	text_layer_set_background_color(pin_text_layer, GColorClear);
	text_layer_set_text_color(pin_text_layer, GColorWhite);
	text_layer_set_text(pin_text_layer, "43°");
	text_layer_set_font(pin_text_layer, fonts_get_system_font(FONT_KEY_LECO_20_BOLD_NUMBERS));
	text_layer_set_text_alignment(pin_text_layer, GTextAlignmentCenter);
	layer_add_child(window_layer, text_layer_get_layer(pin_text_layer));
}
static void pins_destroy() {
	// Destroy TextLayer
	text_layer_destroy(pin_text_layer);
	// Destroy canvas Layer
	layer_destroy(pin_canvas_layer);
	// Destroy the image
	gdraw_command_image_destroy(s_command_image);
}
