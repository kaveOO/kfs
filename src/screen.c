#include "screen.h"

t_screen		g_screens[13];
unsigned int	g_current_screen = 1;

static bool get_screen_from_key(uint8_t key, unsigned int *screen_out) {
	if (g_shift_down && key < sizeof(key_to_screen_map)) {
		uint8_t screen = key_to_screen_map[key];
		if (screen == g_current_screen) {
			return false;
		}
		if (screen > 0 && screen <= 12) {
			*screen_out = screen;
			return true;
		}
	}
	return false;
}

static void save_screen_state() {
	unsigned char *vga_start = VGA_ENTRY;

	for (int i = 0; i < VGA_SIZE; i++) {
		g_screens[g_current_screen].buffer[i] = vga_start[i];
	}

	int cursor_pos = (g_vga - VGA_ENTRY) / 2;
	g_screens[g_current_screen].cursor_row = cursor_pos / VGA_WIDTH;
	g_screens[g_current_screen].cursor_col = cursor_pos % VGA_WIDTH;
}

static void load_screen(unsigned int screen) {
	unsigned char *vga_start = VGA_ENTRY;

	for (int i = 0; i < VGA_SIZE; i++) {
		vga_start[i] = g_screens[screen].buffer[i];
	}

	g_current_screen = screen;
	g_vga = VGA_ENTRY + (g_screens[screen].cursor_row * VGA_WIDTH + g_screens[screen].cursor_col) * 2;
	update_cursor(g_screens[screen].cursor_row, g_screens[screen].cursor_col);
}

void screen_changer(uint8_t key) {
	unsigned int screen;
	if (get_screen_from_key(key, &screen)) {
		save_screen_state();
		load_screen(screen);
		if (g_screens[screen].switched == false && g_current_screen != 1) {
			init_header();
		}
		g_screens[screen].switched = true;
	}
}

void init_screens() {
	for (int i = 1; i <= 12; i++) {
		g_screens[i].cursor_col = 0;
		g_screens[i].cursor_row = 0;
		g_screens[i].switched = false;
		for (int j = 0; j < VGA_SIZE; j += 2) {
			BLANK_CELL(g_screens[i].buffer);
		}
	}
}
