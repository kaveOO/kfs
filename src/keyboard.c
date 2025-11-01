#include "keyboard.h"
#include "io.h"
#include "types.h"

// TODO handle arrows which is required to nagivate in the terminal
// Full US QWERTY scancode set 1 mapping (partial printable subset)
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

// Modifier state
static int shift_down = 0;
static int caps_lock = 0;

static char translate_scancode(uint8_t scancode)
{
    uint8_t key = scancode & 0x7F; // base scancode (without release bit)

    // Handle modifier keys separately
    if (key == 0x2A || key == 0x36) { // Left or Right Shift
        return 0; // modifier handled elsewhere
    }
    if (key == 0x3A) { // Caps Lock
        return 0;
    }

    char c = 0;
    if (shift_down)
        c = scancode_shifted[key];
    else
        c = scancode_normal[key];

    // Letter caps handling
    if (c >= 'a' && c <= 'z') {
        if (caps_lock ^ shift_down) return (char)(c - 'a' + 'A');
    }
    if (c >= 'A' && c <= 'Z') {
        if (caps_lock ^ shift_down) return c;
        else return (char)(c - 'A' + 'a');
    }
    return c;
}

void init_keyboard()
{
    // Register IRQ1 (keyboard) handler. irq_install_handler must exist elsewhere.
    irq_install_handler(1, keyboard_handler);
}

void keyboard_handler()
{
    uint8_t scancode = inb(0x60);

    int released = scancode & 0x80;
    uint8_t key = scancode & 0x7F;

    // Modifier handling: Shift
    if (key == 0x2A || key == 0x36) {
        if (released) shift_down = 0; else shift_down = 1;
        outb(0x20, 0x20);
        return;
    }

    // Caps lock toggles on key press (not on release)
    if (key == 0x3A && !released) {
        caps_lock = !caps_lock;
        outb(0x20, 0x20);
        return;
    }

    if (released) {
        // ignore most releases
        outb(0x20, 0x20);
        return;
    }

    char c = translate_scancode(scancode);
    if (c) {
        char buf[2] = { c, '\0' };
        printk(WHITE, buf);
    }

    // Send End Of Interrupt (EOI) to PIC
    outb(0x20, 0x20);
}

// Fallback polling loop: call this from kmain if IRQs aren't set up yet.
void keyboard_poll_loop(void)
{
    while (1) {
        // Wait until output buffer is full (status port 0x64 bit 0 == 1)
        while (!(inb(0x64) & 1));
        uint8_t scancode = inb(0x60);
        int released = scancode & 0x80;
        uint8_t key = scancode & 0x7F;
        // Modifier handling in polling mode
        if (key == 0x2A || key == 0x36) {
            if (released) shift_down = 0; else shift_down = 1;
            continue;
        }
        if (key == 0x3A && !released) { caps_lock = !caps_lock; continue; }
        if (released) continue;
        char c = translate_scancode(scancode);
        if (c) {
            char buf[2] = { c, '\0' };
            printk(WHITE, buf);
        }
    }
}
