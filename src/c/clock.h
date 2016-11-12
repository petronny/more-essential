#include <pebble.h>
#include "settings.h"

TextLayer* clock_text_layer;
void clock_load();
void clock_update();
void clock_tick_handler(struct tm* tick_time, TimeUnits units_changed);
void clock_init();
void clock_destroy();
