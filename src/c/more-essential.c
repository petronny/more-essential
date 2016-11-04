#include <pebble.h>
#include "more-essential.h"

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
	text_layer_set_background_color(clock_text_layer, GColorWhite);
	text_layer_set_text_color(clock_text_layer, GColorBlack);
	text_layer_set_text(clock_text_layer, "00:00");
	text_layer_set_font(clock_text_layer, fonts_get_system_font(FONT_KEY_LECO_42_NUMBERS));
	text_layer_set_text_alignment(clock_text_layer, GTextAlignmentCenter);
	// Add it as a child layer to the Window's root layer
	layer_add_child(window_layer, text_layer_get_layer(clock_text_layer));
}

static void clock_init() {
	// Make sure the time is displayed from the start
	clock_update();
	// Register with TickTimerService
	tick_timer_service_subscribe(MINUTE_UNIT, tick_handler);
}

static void clock_destroy() {
	text_layer_destroy(clock_text_layer);
}

// Battery
static int battery_level;
static int battery_height=4;
static Layer* battery_layer[2];

static void battery_callback(BatteryChargeState state) {
	// Record the new battery level
	battery_level = state.charge_percent;
	// Update meter
	for(int i=0; i<2; i++)
		layer_mark_dirty(battery_layer[i]);
}

static void battery_update(Layer* layer, GContext* ctx) {
	GRect bounds = layer_get_bounds(layer);
	// Find the width of the bar
	int width = (int)(float)(((float)battery_level / 100.0F) * 114.0F);
	// Draw the background
	graphics_context_set_fill_color(ctx, GColorBlack);
	graphics_fill_rect(ctx, bounds, 0, GCornerNone);
	// Draw the bar
	graphics_context_set_fill_color(ctx, GColorWhite);
	graphics_fill_rect(ctx, GRect(0, 0, width, bounds.size.h), 0, GCornerNone);
}

static void battery_load() {
	// Create battery meter Layer
	battery_layer [0] = layer_create(GRect(0,window_bounds.size.h/3,window_bounds.size.w, battery_height));
	battery_layer [1] = layer_create(GRect(0,window_bounds.size.h/3*2-battery_height,window_bounds.size.w, battery_height));
	for(int i=0; i<2; i++) {
		layer_set_update_proc(battery_layer[i], battery_update);
		layer_add_child(window_layer, battery_layer[i]);
	}
}

static void battery_init() {
	// Register for battery level updates
	battery_state_service_subscribe(battery_callback);
	// Ensure battery level is displayed from the start
	battery_callback(battery_state_service_peek());
}

static void battery_destroy() {
	for(int i=0; i<2; i++)
		layer_destroy(battery_layer[i]);
}

// Icons
static Layer* icon_canvas_layer;
static GDrawCommandImage* s_command_image;
static TextLayer* icon_text_layer;

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

static void icons_load() {
	// Load the image and check it was succcessful
	s_command_image = gdraw_command_image_create_with_resource(RESOURCE_ID_CALENDAR);
	// Create canvas Layer and set up the update procedure
	icon_canvas_layer = layer_create(GRect(0,0,window_bounds.size.w/3,window_bounds.size.h/3*5/8));
	layer_set_update_proc(icon_canvas_layer, update_proc);
	layer_add_child(window_layer, icon_canvas_layer);
	GRect canvas_layer_bounds=layer_get_bounds(icon_canvas_layer);
	icon_text_layer = text_layer_create(GRect(0, canvas_layer_bounds.size.h, canvas_layer_bounds.size.w,window_bounds.size.h/3-canvas_layer_bounds.size.h));
	text_layer_set_background_color(icon_text_layer, GColorClear);
	text_layer_set_text_color(icon_text_layer, GColorWhite);
	text_layer_set_text(icon_text_layer, "43°");
	text_layer_set_font(icon_text_layer, fonts_get_system_font(FONT_KEY_LECO_20_BOLD_NUMBERS));
	text_layer_set_text_alignment(icon_text_layer, GTextAlignmentCenter);
	layer_add_child(window_layer, text_layer_get_layer(icon_text_layer));
}

static void icons_destroy() {
	// Destroy TextLayer
	text_layer_destroy(icon_text_layer);
	// Destroy canvas Layer
	layer_destroy(icon_canvas_layer);
	// Destroy the image
	gdraw_command_image_destroy(s_command_image);
}

// Public
static Window* main_window;

static void tick_handler(struct tm* tick_time, TimeUnits units_changed) {
	clock_update();
}

static void main_window_load(Window* window) {
	// Get information about the Window
	window_layer = window_get_root_layer(window);
	window_bounds = layer_get_bounds(window_layer);
	window_set_background_color(window, GColorDukeBlue);
	clock_load();
	icons_load();
	battery_load();
}

static void main_window_unload(Window* window) {
	clock_destroy();
	icons_destroy();
	battery_destroy();
}

static void init() {
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
