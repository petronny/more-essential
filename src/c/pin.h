#pragma once
#include <pebble.h>
#include "settings.h"
#include "window.h"
#include "panel.h"

typedef struct Pin {
	int type;
	Layer* canvas_layer;
	GDrawCommandImage* draw_command_image;
	TextLayer* text_layer;
} Pin;

Pin pin[6];

LayerUpdateProc pin_layer_update[6];
void pin_0_update(Layer* layer, GContext* ctx);
void pin_1_update(Layer* layer, GContext* ctx);
void pin_2_update(Layer* layer, GContext* ctx);
void pin_3_update(Layer* layer, GContext* ctx);
void pin_4_update(Layer* layer, GContext* ctx);
void pin_5_update(Layer* layer, GContext* ctx);
void pin_load(int i, int type, int current, int num_of_pins, GRect panel_bounds);
void pins_load();
void pin_destroy();
