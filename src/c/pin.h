#pragma once
#include <pebble.h>

typedef struct Pin {
	Layer* canvas_layer;
	GDrawCommandImage* draw_command_image;
	TextLayer* text_layer;
} Pin;
