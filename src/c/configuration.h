#pragma once
#include <pebble.h>

// Persistent storage key
#define SETTINGS_KEY 1

// Define our settings struct
typedef struct ClaySettings {
	GColor BackgroundColor;
	GColor ForegroundColor;
	bool SecondTick;
	bool Animations;
} ClaySettings;

static void prv_inbox_received_handler(DictionaryIterator* iter, void* context);
static void prv_save_settings();
