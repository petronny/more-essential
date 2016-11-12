#pragma once
#include <pebble.h>
#include "settings.h"
#include "window.h"

int battery_level;
Layer* battery_layer;
int battery_layer_height;

void battery_callback(BatteryChargeState state);
void battery_update(Layer* layer, GContext* ctx);
void battery_load();
void battery_init();
void battery_destroy();
