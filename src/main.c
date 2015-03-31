#include <pebble.h>
#include "directions.h"

Window *my_window;
GBitmap  *b_back,*b_arrow;
BitmapLayer *l_back,*l_arrow[3];
TextLayer *t_arrow[3];

Layer *bg_layer;
Layer *clk_layer;
Layer *date_layer;
TextLayer *day_label;
char day_buffer[9];
TextLayer *num_label;
char num_buffer[20];
GBitmap *BT_icon;

static char c_arrow[3][3];
static int sx,sy;
//GPath *bt_paths[NUM_BT_LINES];
GPath *bat_paths[NUM_BAT_LINES];

void bg_update_proc(Layer* me, GContext* ctx) 
{
	graphics_context_set_stroke_color(ctx, GColorWhite);
	graphics_context_set_fill_color(ctx, GColorWhite);	
	
	BatteryChargeState bat_stat = battery_state_service_peek();
	uint8_t bat_level = bat_stat.charge_percent;
	//APP_LOG(APP_LOG_LEVEL_DEBUG, "bat : %d", bat_level);
	int BatNumToFill = 0;
	if( bat_level > 87.5 ) BatNumToFill = 10;
	else if( bat_level > 75 ) BatNumToFill = 9;
	else if( bat_level > 62.5 ) BatNumToFill = 8;
	else if( bat_level > 50 ) BatNumToFill = 7;
	else if( bat_level > 37.5 ) BatNumToFill = 6;
	else if( bat_level > 25 ) BatNumToFill = 5;
	else if( bat_level > 12.5 ) BatNumToFill = 4;
	else BatNumToFill = 3;
	//APP_LOG(APP_LOG_LEVEL_DEBUG, "batnumtofill : %d", BatNumToFill);
	//BatNumToFill = BatNumToFill + 1;
	for (int i = 0; i < BatNumToFill; ++i) 
	{
		gpath_draw_outline(ctx, bat_paths[i]);
	}
	
	if(bluetooth_connection_service_peek())
	{	
		//graphics_fill_rect(ctx, GRect(144-10,160-14,9,13),0,0);
		graphics_draw_bitmap_in_rect(ctx,BT_icon,GRect(144-10,168-14,9,13));
	}

}

void date_update_proc(Layer *me, GContext* ctx) 
{
	time_t now = time(NULL);
	struct tm *current_time = localtime(&now);
	
	strftime(day_buffer, sizeof(day_buffer), "%a",current_time );
	text_layer_set_text(day_label, day_buffer);

	strftime(num_buffer, sizeof(num_buffer), "%m/%d", current_time);
	text_layer_set_text(num_label, num_buffer);
}
	
void updatetime(Layer *me, GContext* ctx) {
	time_t temp = time(NULL); 
	struct tm *tick_time = localtime(&temp);
	int angle,hour;

	for(int i=0;i<3;i++) {
		angle=(120*i+60-2*tick_time->tm_min)%360;
		if (angle>180) {hour=(tick_time->tm_hour+23)%24;} //hour in the bottom left
		else {hour=(tick_time->tm_hour+i)%24;}
		if (!clock_is_24h_style()) {
			hour=hour%12;
		  	if (hour==0) hour=12;
		} 
		snprintf(c_arrow[i], sizeof(c_arrow[i]),"%i",hour);
		//center is 42,84, radius is 82. sx and sy are coords of the tip of the arrow
		sx=42+(82*cos_lookup(TRIG_MAX_ANGLE * angle / 360))/TRIG_MAX_RATIO;
		sy=84-(82*sin_lookup(TRIG_MAX_ANGLE * angle / 360))/TRIG_MAX_RATIO;
		if (sx<39) sx=39;
		layer_set_frame(bitmap_layer_get_layer(l_arrow[i]),GRect(sx-39,sy-9,39,18));
		layer_set_frame(text_layer_get_layer(t_arrow[i]),GRect(sx-38,sy-9-3,22,20));
		text_layer_set_text(t_arrow[i],c_arrow[i]);
	}
}

static void tick_handler(struct tm *tick_time, TimeUnits units_changed) {
  	// Update things here
  	layer_mark_dirty(window_get_root_layer(my_window));
}

//static void handle_bluetooth(bool connected)
//{
//	if(!connected)
//	{
//		vibes_short_pulse();
//	}
//	tick_handler(NULL,SECOND_UNIT); //updateds BG images
//}


void handle_init(void) {
	//fonts
	//GFont bold18 = fonts_get_system_font(FONT_KEY_GOTHIC_14_BOLD);
	GFont norm18 = fonts_get_system_font(FONT_KEY_GOTHIC_14);
	//GFont g28    = fonts_get_system_font(FONT_KEY_GOTHIC_28_BOLD);
	GFont g24    = fonts_get_system_font(FONT_KEY_GOTHIC_24_BOLD);

	//init buffers
	day_buffer[0] = '\0';
	num_buffer[0] = '\0';	
	
	my_window = window_create();
	window_set_fullscreen(my_window, true);

	b_back=gbitmap_create_with_resource(RESOURCE_ID_IMG_BACK);
	b_arrow=gbitmap_create_with_resource(RESOURCE_ID_IMG_ARROW);
	BT_icon=gbitmap_create_with_resource(RESOURCE_ID_BT_IMG);
		
	clk_layer = layer_create(layer_get_frame(window_get_root_layer(my_window)));
	layer_set_update_proc(clk_layer, updatetime);
	// background
	l_back=bitmap_layer_create(GRect(0,0,144,168));
	bitmap_layer_set_bitmap(l_back,b_back);
	layer_add_child(clk_layer, bitmap_layer_get_layer(l_back));


	for(int i=0;i<3;i++) {
		//arrow
		l_arrow[i]=bitmap_layer_create(GRect(0,0,39,18)); 
		bitmap_layer_set_compositing_mode(l_arrow[i],GCompOpOr);
		bitmap_layer_set_bitmap(l_arrow[i],b_arrow);
		//text on the arrow
		t_arrow[i]=text_layer_create(GRect(0,0,22,20));
		text_layer_set_text_alignment(t_arrow[i],GTextAlignmentCenter);
		text_layer_set_text_color(t_arrow[i],GColorWhite);
		text_layer_set_text(t_arrow[i],c_arrow[i]);
		text_layer_set_background_color(t_arrow[i],GColorClear);
		text_layer_set_font(t_arrow[i],fonts_get_system_font(FONT_KEY_GOTHIC_18_BOLD));
		//add to the clk_layer
		layer_add_child(clk_layer, bitmap_layer_get_layer(l_arrow[i]));
		layer_add_child(clk_layer, text_layer_get_layer(t_arrow[i]));
	}

	bg_layer = layer_create(layer_get_frame(window_get_root_layer(my_window)));
	layer_set_update_proc(bg_layer, bg_update_proc);
	
	date_layer = layer_create(layer_get_frame(bg_layer));
	layer_set_update_proc(date_layer, date_update_proc);	
	// init day
	day_label = text_layer_create(GRect(40, 60, 40, 30));
	text_layer_set_text(day_label, day_buffer);
	text_layer_set_background_color(day_label, GColorClear);
	text_layer_set_text_color(day_label, GColorWhite);
	text_layer_set_font(day_label, g24);
	text_layer_set_text_alignment(day_label,GTextAlignmentCenter);
	layer_add_child(date_layer, text_layer_get_layer(day_label));
	//APP_LOG(APP_LOG_LEVEL_DEBUG, "created day_label textLayer");

	// init num
	num_label = text_layer_create(GRect(40, 85, 40, 20));
	text_layer_set_text(num_label, num_buffer);
	text_layer_set_background_color(num_label, GColorClear);
	text_layer_set_text_color(num_label, GColorWhite);
	text_layer_set_font(num_label, norm18);
	text_layer_set_text_alignment(num_label,GTextAlignmentCenter);
	layer_add_child(date_layer, text_layer_get_layer(num_label));
	
	//add layers to window
	layer_add_child(window_get_root_layer(my_window), clk_layer);
	layer_add_child(bg_layer, date_layer);
	layer_add_child(window_get_root_layer(my_window), bg_layer);

	//setup battery lines
	for (int i = 0; i < NUM_BAT_LINES; ++i) 
	{
		bat_paths[i] = gpath_create(&BATTERY_POINTS[i]);	  
	}

	//bluetooth_connection_service_subscribe(handle_bluetooth);
	//tick_handler(NULL, SECOND_UNIT);
	tick_timer_service_subscribe(SECOND_UNIT, tick_handler);
	window_stack_push(my_window, true);
}

void handle_deinit(void) {
	for (int i=1;i<3;i++) { 
		text_layer_destroy(t_arrow[i]);
	  	bitmap_layer_destroy(l_arrow[i]);
	}
	//destroy paths
	for (int i = 0; i < NUM_BAT_LINES; ++i) 
	{
		gpath_destroy(bat_paths[i]);
	}	
	gbitmap_destroy(b_back);
	gbitmap_destroy(b_arrow);
	gbitmap_destroy(BT_icon);
	bitmap_layer_destroy(l_back);
	text_layer_destroy(day_label);
	text_layer_destroy(num_label);
	layer_destroy(date_layer);
	layer_destroy(bg_layer);
	layer_destroy(clk_layer);
	window_destroy(my_window);
	tick_timer_service_unsubscribe();
}

int main(void) {
	handle_init();
	app_event_loop();
	handle_deinit();
}
