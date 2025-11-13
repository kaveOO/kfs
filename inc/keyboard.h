#pragma once

#include "kernel.h"

static const char scancode_normal[128] = {
	0,  27, '1','2','3','4','5','6','7','8','9','0','-','=', '\b', '\t',
	'q','w','e','r','t','y','u','i','o','p','[',']','\n', 0,
	'a','s','d','f','g','h','j','k','l',';','\'', '`', 0,
	'\\','z','x','c','v','b','n','m',',','.','/', 0,  '*', 0, ' '
};

static const char scancode_shifted[128] = {
	0,  27, '!','@','#','$','%','^','&','*','(',')','_','+', '\b', '\t',
	'Q','W','E','R','T','Y','U','I','O','P','{','}','\n', 0,
	'A','S','D','F','G','H','J','K','L',':','"','~', 0,
	'|','Z','X','C','V','B','N','M','<','>','?', 0,  '*', 0, ' '
};

static const uint8_t f_keys_to_int[0x59] = {
	[0x3B] = 1,	// F1
	[0x3C] = 2,
	[0x3D] = 3,
	[0x3E] = 4,
	[0x3F] = 5,
	[0x40] = 6,
	[0x41] = 7,
	[0x42] = 8,
	[0x43] = 9,
	[0x44] = 10,
	[0x57] = 11,
	[0x58] = 12 // F12
};

extern int g_shift_down;
extern int g_caps_lock;
extern int g_insert_on;

void keyboard_poll_loop();
