#pragma once
#include <pebble.h>
#include "settings.h"
#include "window.h"

typedef struct Pin {
	Layer* canvas_layer;
	GDrawCommandImage* draw_command_image;
	TextLayer* text_layer;
} Pin;
