#include "types.h"
#include "io.h"
#include "song.h"

// TODO Rework entire sound system + define tunes !

// https://wiki.osdev.org/PC_Speaker
static void PlaySound(uint32_t nFrequence) {
 	uint32_t Div;
 	uint8_t tmp;

	// Set the PIT to the desired frequency (Programmable Interval Timer)
	// To play a square wave https://en.wikipedia.org/wiki/Pulse-VGA_WIDTH_modulation
 	Div = 1193180 / nFrequence;
 	outb(0x43, 0xb6);
	outb(0x42, (uint8_t) (Div) );
	outb(0x42, (uint8_t) (Div >> 8));

	// And play the sound using the PC speaker
 	tmp = inb(SPEAKER_CONTROL_PORT);

  	if (tmp != (tmp | 3)) { // Check if speaker enabled; if not enable
		  outb(SPEAKER_CONTROL_PORT, tmp | 3);
	}
}

// Mute the sound
static void mute_sound() {
 	uint8_t tmp = inb(SPEAKER_CONTROL_PORT) & 0xFC;
 	outb(SPEAKER_CONTROL_PORT, tmp);
}

// Make a beep
void beep() {
	PlaySound(1000);
	for (int i = 0; i < 10000; i++) {
		outb(2, 10); // Trigger random port for delay
	}
	mute_sound();
}
