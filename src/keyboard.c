#include "keyboard.h"

// Modifier state
int g_shift_down = 0;
int g_caps_lock = 0;

// TODO handle vga shifting when moving to the left and writing

static void handle_extended(uint8_t scancode) {
	switch (scancode) {
		case 0x48:
			// Up (handle command history)
			break;
		case 0x50:
			// Down (handle command history)
			break;
		case 0x4D:
			vga += 2;
			break;
		case 0x4B:
			vga -= 2;
			break;
		default:
			// Error handling here
			break;
	}
	move_cursor();
}

static char translate_scancode(uint8_t scancode) {

    uint8_t key = scancode & 0x7F; // base scancode (without release bit)

    // Handle modifier keys separately
    if (key == 0x2A || key == 0x36) { // Left or Right Shift
        return 0; // modifier handled elsewhere
    }
    if (key == 0x3A) { // Caps Lock
        return 0;
    }

    char c = 0;
    if (g_shift_down) { c = scancode_shifted[key]; }
    else { c = scancode_normal[key]; }

    // Letter caps handling
    if (c >= 'a' && c <= 'z') {
        if (g_caps_lock ^ g_shift_down) return (char)(c - 'a' + 'A');
    }
    if (c >= 'A' && c <= 'Z') {
        if (g_caps_lock ^ g_shift_down) return c;
        else return (char)(c - 'A' + 'a');
    }
    return c;
}

// Fallback polling loop: call this from kmain if IRQs aren't set up yet.
void keyboard_poll_loop() {
    while (1) {
        // Wait until output buffer is full (status port 0x64 bit 0 == 1)
        while (!(inb(0x64) & 1));

        uint8_t scancode = inb(0x60);
        int released = scancode & 0x80;
        uint8_t key = scancode & 0x7F;
        // Modifier handling in polling mode
        if (key == 0x2A || key == 0x36) {
            if (released) g_shift_down = 0; else g_shift_down = 1;
            continue;
        }
        if (key == 0x3A && !released) { g_caps_lock = !g_caps_lock; continue; }
        if (released) continue;
		theme_changer(key);
		handle_extended(scancode);
        char c = translate_scancode(scancode);
        if (c) {
            char buf[2] = { c, '\0' };
            printk(WHITE, buf);
        }
    }
}
