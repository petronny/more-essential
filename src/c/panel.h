#pragma once
#include <pebble.h>
#include "settings.h"
#include "window.h"

Layer* panel_layer[2];

void upper_panel_update(Layer* layer, GContext* ctx);
void bottom_panel_update(Layer* layer, GContext* ctx);
LayerUpdateProc panel_layer_update[2];
void panel_load();
void panel_destroy();
