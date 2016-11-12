#include "pin.h"

LayerUpdateProc pin_layer_update[6]= {pin_0_update,pin_1_update,pin_2_update,pin_3_update,pin_4_update,pin_5_update};

void pin_0_update(Layer* layer, GContext* ctx) {
	// Place image in the center of the Window
	GSize img_size = gdraw_command_image_get_bounds_size(pin[0].draw_command_image);
	GRect bounds = layer_get_bounds(layer);
	const GEdgeInsets frame_insets = {
		.top = (bounds.size.h - img_size.h) / 2,
		.left = (bounds.size.w - img_size.w) / 2
	};
	// If the image was loaded successfully...
	if(pin[0].draw_command_image) {
		// Draw it
		gdraw_command_image_draw(ctx, pin[0].draw_command_image, grect_inset(bounds, frame_insets).origin);
	}
}

void pin_1_update(Layer* layer, GContext* ctx) {
	// Place image in the center of the Window
	GSize img_size = gdraw_command_image_get_bounds_size(pin[1].draw_command_image);
	GRect bounds = layer_get_bounds(layer);
	const GEdgeInsets frame_insets = {
		.top = (bounds.size.h - img_size.h) / 2,
		.left = (bounds.size.w - img_size.w) / 2
	};
	// If the image was loaded successfully...
	if(pin[1].draw_command_image) {
		// Draw it
		gdraw_command_image_draw(ctx, pin[1].draw_command_image, grect_inset(bounds, frame_insets).origin);
	}
}

void pin_2_update(Layer* layer, GContext* ctx) {
	// Place image in the center of the Window
	GSize img_size = gdraw_command_image_get_bounds_size(pin[2].draw_command_image);
	GRect bounds = layer_get_bounds(layer);
	const GEdgeInsets frame_insets = {
		.top = (bounds.size.h - img_size.h) / 2,
		.left = (bounds.size.w - img_size.w) / 2
	};
	// If the image was loaded successfully...
	if(pin[2].draw_command_image) {
		// Draw it
		gdraw_command_image_draw(ctx, pin[2].draw_command_image, grect_inset(bounds, frame_insets).origin);
	}
}

void pin_3_update(Layer* layer, GContext* ctx) {
	// Place image in the center of the Window
	GSize img_size = gdraw_command_image_get_bounds_size(pin[3].draw_command_image);
	GRect bounds = layer_get_bounds(layer);
	const GEdgeInsets frame_insets = {
		.top = (bounds.size.h - img_size.h) / 2,
		.left = (bounds.size.w - img_size.w) / 2
	};
	// If the image was loaded successfully...
	if(pin[3].draw_command_image) {
		// Draw it
		gdraw_command_image_draw(ctx, pin[3].draw_command_image, grect_inset(bounds, frame_insets).origin);
	}
}

void pin_4_update(Layer* layer, GContext* ctx) {
	// Place image in the center of the Window
	GSize img_size = gdraw_command_image_get_bounds_size(pin[4].draw_command_image);
	GRect bounds = layer_get_bounds(layer);
	const GEdgeInsets frame_insets = {
		.top = (bounds.size.h - img_size.h) / 2,
		.left = (bounds.size.w - img_size.w) / 2
	};
	// If the image was loaded successfully...
	if(pin[4].draw_command_image) {
		// Draw it
		gdraw_command_image_draw(ctx, pin[4].draw_command_image, grect_inset(bounds, frame_insets).origin);
	}
}

void pin_5_update(Layer* layer, GContext* ctx) {
	// Place image in the center of the Window
	GSize img_size = gdraw_command_image_get_bounds_size(pin[5].draw_command_image);
	GRect bounds = layer_get_bounds(layer);
	const GEdgeInsets frame_insets = {
		.top = (bounds.size.h - img_size.h) / 2,
		.left = (bounds.size.w - img_size.w) / 2
	};
	// If the image was loaded successfully...
	if(pin[5].draw_command_image) {
		// Draw it
		gdraw_command_image_draw(ctx, pin[5].draw_command_image, grect_inset(bounds, frame_insets).origin);
	}
}

void pin_load(int i, int type, int current, int num_of_pins, GRect panel_bounds) {
	if(type==0)
		return;
	// Load the image and check it was succcessful
	switch(type){
		case 1:
			pin[i].draw_command_image = gdraw_command_image_create_with_resource(RESOURCE_ID_CALENDAR);
			break;
		default:
			pin[i].draw_command_image = gdraw_command_image_create_with_resource(RESOURCE_ID_CALENDAR);
	}
	// Create canvas Layer and set up the update procedure
	if(num_of_pins==1)
		pin[i].canvas_layer = layer_create(GRect(0,0,panel_bounds.size.w/4,panel_bounds.size.h));
	else
		pin[i].canvas_layer = layer_create(GRect(current*panel_bounds.size.w/num_of_pins,0,panel_bounds.size.w/num_of_pins,panel_bounds.size.h*5/8));
	layer_set_update_proc(pin[i].canvas_layer, pin_layer_update[i]);
	layer_add_child(window_layer, pin[i].canvas_layer);
	if(num_of_pins==1)
		pin[i].text_layer = text_layer_create(GRect(panel_bounds.size.w/4, 0, panel_bounds.size.w*3/4,panel_bounds.size.h));
	else
		pin[i].text_layer = text_layer_create(GRect(current*panel_bounds.size.w/num_of_pins, panel_bounds.size.h*5/8, panel_bounds.size.w/num_of_pins,panel_bounds.size.h*3/8));
	text_layer_set_background_color(pin[i].text_layer, GColorClear);
	text_layer_set_text_color(pin[i].text_layer, settings.panel_foreground_color[i/3]);
	text_layer_set_text(pin[i].text_layer, "TXT");
	switch(type){
		case 1:
			text_layer_set_font(pin[i].text_layer, fonts_get_system_font(FONT_KEY_GOTHIC_18_BOLD));
			break;
		case 2:
			text_layer_set_font(pin[i].text_layer, fonts_get_system_font(FONT_KEY_LECO_20_BOLD_NUMBERS));
			break;
		default:
			text_layer_set_font(pin[i].text_layer, fonts_get_system_font(FONT_KEY_GOTHIC_18_BOLD));
			break;
	}
	text_layer_set_text_alignment(pin[i].text_layer, GTextAlignmentCenter);
	layer_add_child(window_layer, text_layer_get_layer(pin[i].text_layer));
}

void pins_load() {
	pin_destroy();
	for(int i=0; i<2; i++) {
		int num_of_pins=0;
		int current=0;
		GRect bounds=layer_get_bounds(panel_layer[i]);
		for(int j=0; j<2; j++)
			num_of_pins+=settings.pin[i*3+j]>0;
		for(int j=0; j<2; j++){
			pin_load(i*3+j,settings.pin[i*3+j], current, num_of_pins, bounds);
			current+=settings.pin[i*3+j]>0;
		}
	}
}

void pin_destroy() {
	for(int i=0; i<6; i++) {
		text_layer_destroy(pin[i].text_layer);
		layer_destroy(pin[i].canvas_layer);
		gdraw_command_image_destroy(pin[i].draw_command_image);
	}
}
