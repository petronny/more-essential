#pragma once
#include <pebble.h>
#include "settings.h"
#include "window.h"

Layer* bluetooth_layer;
int bluetooth_layer_height;
bool bluetooth_state;

void bluetooth_callback(bool connected);
void bluetooth_update(Layer* layer, GContext* ctx);
void bluetooth_load();
void bluetooth_init();
void bluetooth_destroy();
