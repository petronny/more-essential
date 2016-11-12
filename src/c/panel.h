#pragma once
#include <pebble.h>
#include "settings.h"
#include "window.h"

Layer* upper_panel_layer;
Layer* bottom_panel_layer;

void upper_panel_update(Layer* layer, GContext* ctx);
void bottom_panel_update(Layer* layer, GContext* ctx);
void panel_load();
void panel_destroy();
