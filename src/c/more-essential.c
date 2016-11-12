#include <pebble.h>
#include "settings.h"

// Window
static Layer* window_layer;
static GRect window_bounds;

// Clock
static TextLayer* clock_text_layer;

static void clock_update() {
	// Get a tm structure
	time_t temp = time(NULL);
	struct tm* tick_time = localtime(&temp);
	// Write the current hours and minutes into a buffer
	static char s_buffer[8];
	strftime(s_buffer, sizeof(s_buffer), clock_is_24h_style() ? "%H:%M" : "%I:%M", tick_time);
	// Display this time on the TextLayer
	text_layer_set_text(clock_text_layer, s_buffer);
}

static void clock_load() {
	// Create the TextLayer with specific bounds
	clock_text_layer = text_layer_create(GRect(0, window_bounds.size.h/3, window_bounds.size.w, window_bounds.size.h/3));
	// Improve the layout to be more like a watchface
	text_layer_set_background_color(clock_text_layer, settings.clock_background_color);
	text_layer_set_text_color(clock_text_layer, settings.clock_foreground_color);
	text_layer_set_text(clock_text_layer, "00:00");
	text_layer_set_font(clock_text_layer, fonts_get_system_font(FONT_KEY_LECO_42_NUMBERS));
	text_layer_set_text_alignment(clock_text_layer, GTextAlignmentCenter);
	// Add it as a child layer to the Window's root layer
	layer_add_child(window_layer, text_layer_get_layer(clock_text_layer));
}

static void clock_tick_handler(struct tm* tick_time, TimeUnits units_changed) {
	clock_update();
}

static void clock_init() {
	// Make sure the time is displayed from the start
	clock_update();
	// Register with TickTimerService
	tick_timer_service_subscribe(MINUTE_UNIT, clock_tick_handler);
}

static void clock_destroy() {
	text_layer_destroy(clock_text_layer);
}

// Battery
static int battery_level;
static Layer* battery_layer;
static int battery_layer_height=4;

static void battery_callback(BatteryChargeState state) {
	// Record the new battery level
	battery_level = state.charge_percent;
	// Update meter
	if(settings.battery_display)
		layer_mark_dirty(battery_layer);
}

static void battery_update(Layer* layer, GContext* ctx) {
	GRect bounds = layer_get_bounds(layer);
	// Find the width of the bar
	int width = (int)(float)(((float)battery_level / 100.0F) * bounds.size.w);
	// Draw the background
	graphics_context_set_fill_color(ctx, GColorClear);
	graphics_fill_rect(ctx, bounds, 0, GCornerNone);
	// Draw the bar
	graphics_context_set_fill_color(ctx, settings.battery_color_low);
	if(battery_level>=30)
		graphics_context_set_fill_color(ctx, settings.battery_color_medium);
	if(battery_level>=70)
		graphics_context_set_fill_color(ctx, settings.battery_color_high);
	graphics_fill_rect(ctx, GRect(0, 0, width, bounds.size.h), 0, GCornerNone);
}

static void battery_load() {
	// Create battery meter Layer
	battery_layer = layer_create(GRect(0,window_bounds.size.h/3*2-battery_layer_height,window_bounds.size.w, battery_layer_height));
	layer_set_update_proc(battery_layer, battery_update);
	layer_set_hidden(battery_layer, !settings.battery_display);
	layer_add_child(window_layer, battery_layer);
}

static void battery_init() {
	// Register for battery level updates
	battery_state_service_subscribe(battery_callback);
	// Ensure battery level is displayed from the start
	battery_callback(battery_state_service_peek());
}

static void battery_destroy() {
	layer_destroy(battery_layer);
}

// Bluetooth
static Layer* bluetooth_layer;
static int bluetooth_layer_height=4;
//static bool bluetooth_state;

static void bluetooth_callback(bool connected) {
	//bluetooth_state=connected;
	layer_set_hidden(bluetooth_layer, !connected || !settings.bluetooth_display);
	if(!connected && settings.bluetooth_vibrate) {
		// Issue a vibrating alert
		vibes_double_pulse();
	}
}

static void bluetooth_update(Layer* layer, GContext* ctx) {
	GRect bounds = layer_get_bounds(layer);
	graphics_context_set_fill_color(ctx, settings.bluetooth_color);
	graphics_fill_rect(ctx, bounds, 0, GCornerNone);
}

static void bluetooth_load() {
	bluetooth_layer = layer_create(GRect(0,window_bounds.size.h/3,window_bounds.size.w, bluetooth_layer_height));
	layer_set_update_proc(bluetooth_layer, bluetooth_update);
	layer_mark_dirty(bluetooth_layer);
	layer_set_hidden(bluetooth_layer, !settings.bluetooth_display);
	layer_add_child(window_layer, bluetooth_layer);
}

static void bluetooth_init() {
	connection_service_subscribe((ConnectionHandlers) {
		.pebble_app_connection_handler = bluetooth_callback
	});
	// Show the correct state of the BT connection from the start
	bluetooth_callback(connection_service_peek_pebble_app_connection());
}

static void bluetooth_destroy() {
	layer_destroy(bluetooth_layer);
}

/*/ Pin
static Layer* pin_canvas_layer;
static GDrawCommandImage* s_command_image;
static TextLayer* pin_text_layer;

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

static void pins_load() {
	// Load the image and check it was succcessful
	s_command_image = gdraw_command_image_create_with_resource(RESOURCE_ID_CALENDAR);
	// Create canvas Layer and set up the update procedure
	pin_canvas_layer = layer_create(GRect(0,0,window_bounds.size.w/3,window_bounds.size.h/3*5/8));
	layer_set_update_proc(pin_canvas_layer, update_proc);
	layer_add_child(window_layer, pin_canvas_layer);
	GRect canvas_layer_bounds=layer_get_bounds(pin_canvas_layer);
	pin_text_layer = text_layer_create(GRect(0, canvas_layer_bounds.size.h, canvas_layer_bounds.size.w,window_bounds.size.h/3-canvas_layer_bounds.size.h));
	text_layer_set_background_color(pin_text_layer, GColorClear);
	text_layer_set_text_color(pin_text_layer, GColorWhite);
	text_layer_set_text(pin_text_layer, "43°");
	text_layer_set_font(pin_text_layer, fonts_get_system_font(FONT_KEY_LECO_20_BOLD_NUMBERS));
	text_layer_set_text_alignment(pin_text_layer, GTextAlignmentCenter);
	layer_add_child(window_layer, text_layer_get_layer(pin_text_layer));
}

static void pins_destroy() {
	// Destroy TextLayer
	text_layer_destroy(pin_text_layer);
	// Destroy canvas Layer
	layer_destroy(pin_canvas_layer);
	// Destroy the image
	gdraw_command_image_destroy(s_command_image);
}*/

// Panel
static Layer* panel_layer[2];

static void upper_panel_update(Layer* layer, GContext* ctx) {
	GRect bounds = layer_get_bounds(layer);
	graphics_context_set_fill_color(ctx, settings.upper_panel_background_color);
	graphics_fill_rect(ctx, bounds, 0, GCornerNone);
}

static void bottom_panel_update(Layer* layer, GContext* ctx) {
	GRect bounds = layer_get_bounds(layer);
	graphics_context_set_fill_color(ctx, settings.bottom_panel_background_color);
	graphics_fill_rect(ctx, bounds, 0, GCornerNone);
}

static void panel_load() {
	panel_layer[0] = layer_create(GRect(0,0,window_bounds.size.w, window_bounds.size.h/3));
	panel_layer[1] = layer_create(GRect(0,window_bounds.size.h/3*2,window_bounds.size.w, window_bounds.size.h/3));
	layer_set_update_proc(panel_layer[0], upper_panel_update);
	layer_set_update_proc(panel_layer[1], bottom_panel_update);
	for(int i=0; i<2; i++) {
		layer_add_child(window_layer, panel_layer[i]);
		layer_mark_dirty(panel_layer[i]);
	}
}

static void panel_destroy() {
	for(int i=0; i<2; i++)
		layer_destroy(panel_layer[i]);
}

// Settings

void settings_default_settings() {
	// Initialize the default settings
	settings.theme = 0;
	settings.bluetooth_vibrate = true;
	settings.clock_hourly_vibrate = true;
	settings.battery_display = true;
	settings.bluetooth_display = true;
	settings.upper_panel_animations = true;
	settings.bottom_panel_animations = true;
	settings_theme_default();
}

static void settings_load_settings() {
	// Load the default settings
	settings_default_settings();
	// Read settings from persistent storage, if they exist
	persist_read_data(SETTINGS_KEY, &settings, sizeof(settings));
}

static void settings_update_display() {
	// Update the display elements
	text_layer_set_background_color(clock_text_layer, settings.clock_background_color);
	text_layer_set_text_color(clock_text_layer, settings.clock_foreground_color);
	layer_set_hidden(battery_layer, !settings.battery_display);
	layer_mark_dirty(battery_layer);
	layer_set_hidden(bluetooth_layer, !settings.bluetooth_display);
	layer_mark_dirty(bluetooth_layer);
	layer_mark_dirty(panel_layer[0]);
	layer_mark_dirty(panel_layer[1]);
}

static void settings_save_settings() {
	// Save the settings to persistent storage
	persist_write_data(SETTINGS_KEY, &settings, sizeof(settings));
	// Update the display based on new settings
	settings_update_display();
}

static void settings_inbox_received_handler(DictionaryIterator* iter, void* context) {
	// Handle the response from AppMessage
	Tuple* clock_background_color = dict_find(iter, MESSAGE_KEY_clock_background_color);
	if(clock_background_color)
		settings.clock_background_color = GColorFromHEX(clock_background_color->value->int32);
	Tuple* clock_foreground_color = dict_find(iter, MESSAGE_KEY_clock_foreground_color);
	if(clock_foreground_color)
		settings.clock_foreground_color = GColorFromHEX(clock_foreground_color->value->int32);
	Tuple* bluetooth_vibrate = dict_find(iter, MESSAGE_KEY_bluetooth_vibrate);
	if(bluetooth_vibrate)
		settings.bluetooth_vibrate = bluetooth_vibrate->value->int32 == 1;
	Tuple* clock_hourly_vibrate = dict_find(iter, MESSAGE_KEY_clock_hourly_vibrate);
	if(clock_hourly_vibrate)
		settings.clock_hourly_vibrate = clock_hourly_vibrate->value->int32 == 1;
	Tuple* battery_display = dict_find(iter, MESSAGE_KEY_battery_display);
	if(battery_display)
		settings.battery_display = battery_display->value->int32 == 1;
	Tuple* battery_color_high = dict_find(iter, MESSAGE_KEY_battery_color_high);
	if(battery_color_high)
		settings.battery_color_high = GColorFromHEX(battery_color_high->value->int32);
	Tuple* battery_color_medium = dict_find(iter, MESSAGE_KEY_battery_color_medium);
	if(battery_color_medium)
		settings.battery_color_medium = GColorFromHEX(battery_color_medium->value->int32);
	Tuple* battery_color_low = dict_find(iter, MESSAGE_KEY_battery_color_low);
	if(battery_color_low)
		settings.battery_color_low = GColorFromHEX(battery_color_low->value->int32);
	Tuple* bluetooth_display = dict_find(iter, MESSAGE_KEY_bluetooth_display);
	if(bluetooth_display)
		settings.bluetooth_display = bluetooth_display->value->int32 == 1;
	Tuple* bluetooth_color = dict_find(iter, MESSAGE_KEY_bluetooth_color);
	if(bluetooth_color)
		settings.bluetooth_color = GColorFromHEX(bluetooth_color->value->int32);
	Tuple* upper_panel_background_color = dict_find(iter, MESSAGE_KEY_upper_panel_background_color);
	if(upper_panel_background_color)
		settings.upper_panel_background_color = GColorFromHEX(upper_panel_background_color->value->int32);
	Tuple* upper_panel_foreground_color = dict_find(iter, MESSAGE_KEY_upper_panel_foreground_color);
	if(upper_panel_foreground_color)
		settings.upper_panel_foreground_color = GColorFromHEX(upper_panel_foreground_color->value->int32);
	Tuple* bottom_panel_background_color = dict_find(iter, MESSAGE_KEY_bottom_panel_background_color);
	if(bottom_panel_background_color)
		settings.bottom_panel_background_color = GColorFromHEX(bottom_panel_background_color->value->int32);
	Tuple* bottom_panel_foreground_color = dict_find(iter, MESSAGE_KEY_bottom_panel_foreground_color);
	if(bottom_panel_foreground_color)
		settings.bottom_panel_foreground_color = GColorFromHEX(bottom_panel_foreground_color->value->int32);
	Tuple* theme = dict_find(iter, MESSAGE_KEY_theme);
	if(theme)
		settings.theme = (int)theme->value->uint8-'0';
	switch(settings.theme) {
		case 1:
			settings_theme_default();
			break;
		case 2:
			settings_theme_france();
			break;
		case 3:
			settings_theme_german();
			break;
		case 4:
			settings_theme_italy();
			break;
		case 5:
			settings_theme_russia();
			break;
	}
	// Save the new settings to persistent storage
	settings_save_settings();
}

static void settings_init() {
	settings_load_settings();
	// Open AppMessage connection
	app_message_register_inbox_received(settings_inbox_received_handler);
	app_message_open(256, 256);
}

// Public
static Window* main_window;

static void main_window_load(Window* window) {
	// Get information about the Window
	window_layer = window_get_root_layer(window);
	window_bounds = layer_get_bounds(window_layer);
	clock_load();
	battery_load();
	bluetooth_load();
	panel_load();
//	pins_load();
}

static void main_window_unload(Window* window) {
	clock_destroy();
	battery_destroy();
	bluetooth_destroy();
	panel_destroy();
//	pins_destroy();
}

static void init() {
	settings_init();
	// Create main Window element and assign to pointer
	main_window = window_create();
	// Set handlers to manage the elements inside the Window
	window_set_window_handlers(main_window, (WindowHandlers) {
		.load = main_window_load,
		 .unload = main_window_unload
	});
	// Show the Window on the watch, with animated=true
	window_stack_push(main_window, true);
	clock_init();
	battery_init();
	bluetooth_init();
}

static void deinit() {
	// Destroy Window
	window_destroy(main_window);
}

int main(void) {
	init();
	app_event_loop();
	deinit();
}
