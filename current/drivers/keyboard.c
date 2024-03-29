#include "keyboard.h"
#include "screen.h"
#include "../cpu/ports.h"
#include "../cpu/isr.h"
#include "../libc/string.h"
#include "../libc/function.h"
#include "../kernel/kernel.h"

#define BACKSPACE 0x0E
#define ENTER 0x1C
#define LSHIFT 0x2A
#define LSHIFT_UP 0xAA
#define RSHIFT 0x36
#define RSHIFT_UP 0xB6

static char key_buffer[256];
static int key_buffer_size = 0;
static int shift = 0;

#define SC_MAX 57
const char *sc_name[] = { "ERROR", "Esc", "1", "2", "3", "4", "5", "6", 
    "7", "8", "9", "0", "-", "=", "Backspace", "Tab", "Q", "W", "E", 
        "R", "T", "Y", "U", "I", "O", "P", "[", "]", "Enter", "Lctrl", 
        "A", "S", "D", "F", "G", "H", "J", "K", "L", ";", "'", "`", 
        "LShift", "\\", "Z", "X", "C", "V", "B", "N", "M", ",", ".", 
        "/", "RShift", "Keypad *", "LAlt", "Spacebar"};
const char sc_ascii[] = { '?', '?', '1', '2', '3', '4', '5', '6',     
    '7', '8', '9', '0', '-', '=', '?', '?', 'Q', 'W', 'E', 'R', 'T', 'Y', 
        'U', 'I', 'O', 'P', '[', ']', '?', '?', 'A', 'S', 'D', 'F', 'G', 
        'H', 'J', 'K', 'L', ';', '\'', '`', '?', '\\', 'Z', 'X', 'C', 'V', 
        'B', 'N', 'M', ',', '.', '/', '?', '?', '?', ' '};

static void keybord_callback(registers_t *regs) {
    u8 scancode = port_byte_in(0x60);

    if (scancode == LSHIFT || scancode == RSHIFT) {
        shift = 1;
        return;
    } else if (scancode == LSHIFT_UP || scancode == RSHIFT_UP) {
        shift = 0;
        return;
    }

    if (scancode > SC_MAX) return;
    if (scancode == BACKSPACE) { 
        backspace(key_buffer);
        if (key_buffer_size > 0) {
            kprint_backspace();
            key_buffer_size--;
        }
    } else if (scancode == ENTER) {
        kprint("\n");
        user_input(key_buffer);
        key_buffer[0] = '\0';
        key_buffer_size = 0;
    } else {
        char letter = sc_ascii[(int)scancode];
        if (is_alpha(letter) && !shift) {
            letter += 0x20;
        }
        char str[2] = {letter, '\0'};
        append(key_buffer, letter);
        key_buffer_size++;
        kprint(str);
    }
    UNUSED(regs);
}

void init_keyboard() {
    register_interrupt_handler(IRQ1, keybord_callback);
}


