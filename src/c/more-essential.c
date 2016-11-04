#include <pebble.h>
#include "configuration.h"

static Window* s_main_window;
static TextLayer* s_time_layer;
static Layer* s_canvas_layer;

static GDrawCommandImage* s_command_image;
static ClaySettings settings;

// Initialize the default settings
static void prv_default_settings() {
	settings.BackgroundColor = GColorBlack;
	settings.ForegroundColor = GColorWhite;
	settings.SecondTick = false;
	settings.Animations = false;
}

// Read settings from persistent storage
static void prv_load_settings() {
	// Load the default settings
	prv_default_settings();
	// Read settings from persistent storage, if they exist
	persist_read_data(SETTINGS_KEY, &settings, sizeof(settings));
}

// Save the settings to persistent storage
static void prv_save_settings() {
	persist_write_data(SETTINGS_KEY, &settings, sizeof(settings));
}

static void prv_inbox_received_handler(DictionaryIterator* iter, void* context) {
	// Read color preferences
	Tuple* bg_color_t = dict_find(iter, MESSAGE_KEY_BackgroundColor);
	if(bg_color_t)
		settings.BackgroundColor = GColorFromHEX(bg_color_t->value->int32);
	Tuple* fg_color_t = dict_find(iter, MESSAGE_KEY_ForegroundColor);
	if(fg_color_t)
		settings.ForegroundColor = GColorFromHEX(fg_color_t->value->int32);
	// Read boolean preferences
	Tuple* second_tick_t = dict_find(iter, MESSAGE_KEY_SecondTick);
	if(second_tick_t)
		settings.SecondTick = second_tick_t->value->int32 == 1;
	Tuple* animations_t = dict_find(iter, MESSAGE_KEY_Animations);
	if(animations_t)
		settings.Animations = animations_t->value->int32 == 1;
	prv_save_settings();
}

static void update_proc(Layer* layer, GContext* ctx) {
	// Place image in the center of the Window
	GSize img_size = gdraw_command_image_get_bounds_size(s_command_image);
	GRect bounds = layer_get_bounds(layer);
	const GEdgeInsets frame_insets = {
		.top = (bounds.size.h - img_size.h) / 2,
		.left = (bounds.size.w - img_size.w) / 2
	};
	// If the image was loaded successfully...
	if(s_command_image) {
		// Draw it
		gdraw_command_image_draw(ctx, s_command_image, grect_inset(bounds, frame_insets).origin);
	}
}

static void update_time() {
	// Get a tm structure
	time_t temp = time(NULL);
	struct tm* tick_time = localtime(&temp);
	// Write the current hours and minutes into a buffer
	static char s_buffer[8];
	strftime(s_buffer, sizeof(s_buffer), clock_is_24h_style() ?
	         "%H:%M" : "%I:%M", tick_time);
	// Display this time on the TextLayer
	text_layer_set_text(s_time_layer, s_buffer);
}

static void tick_handler(struct tm* tick_time, TimeUnits units_changed) {
	update_time();
}

static void main_window_load(Window* window) {
	// Get information about the Window
	Layer* window_layer = window_get_root_layer(window);
	GRect bounds = layer_get_bounds(window_layer);
	window_set_background_color(window, GColorVividCerulean);
	// Create the TextLayer with specific bounds
	s_time_layer = text_layer_create(
	                   GRect(0, bounds.size.h/3, bounds.size.w, bounds.size.h/3));
	// Improve the layout to be more like a watchface
	text_layer_set_background_color(s_time_layer, GColorWhite);
	text_layer_set_text_color(s_time_layer, GColorBlack);
	text_layer_set_text(s_time_layer, "00:00");
	text_layer_set_font(s_time_layer, fonts_get_system_font(FONT_KEY_LECO_42_NUMBERS));
	text_layer_set_text_alignment(s_time_layer, GTextAlignmentCenter);
	// Add it as a child layer to the Window's root layer
	layer_add_child(window_layer, text_layer_get_layer(s_time_layer));
	// Load the image and check it was succcessful
	s_command_image = gdraw_command_image_create_with_resource(RESOURCE_ID_CALENDAR);
	if(!s_command_image)
		APP_LOG(APP_LOG_LEVEL_ERROR, "Image is NULL!");
	// Create canvas Layer and set up the update procedure
	s_canvas_layer = layer_create(GRect(0,0,bounds.size.w/2,bounds.size.h/6));
	layer_set_update_proc(s_canvas_layer, update_proc);
	layer_add_child(window_layer, s_canvas_layer);
}

static void main_window_unload(Window* window) {
	// Destroy TextLayer
	text_layer_destroy(s_time_layer);
	// Destroy canvas Layer
	layer_destroy(s_canvas_layer);
	// Destroy the image
	gdraw_command_image_destroy(s_command_image);
}


static void init() {
	// Open AppMessage connection
	app_message_register_inbox_received(prv_inbox_received_handler);
	app_message_open(128, 128);
	// Create main Window element and assign to pointer
	s_main_window = window_create();
	// Set handlers to manage the elements inside the Window
	window_set_window_handlers(s_main_window, (WindowHandlers) {
		.load = main_window_load,
		 .unload = main_window_unload
	});
	// Show the Window on the watch, with animated=true
	window_stack_push(s_main_window, true);
	// Make sure the time is displayed from the start
	update_time();
	// Register with TickTimerService
	tick_timer_service_subscribe(MINUTE_UNIT, tick_handler);
}

static void deinit() {
	// Destroy Window
	window_destroy(s_main_window);
}

int main(void) {
	init();
	app_event_loop();
	deinit();
}
