
#include "system.h"

// Debug interface writes strings to COM1.
// QEMU can be configured to write this data to the console or to a file.

#define COM1 0x3f8

const char hex[] = {
    '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f'
};

void debug_init() {
    outb(COM1 + 1, 0x00); // Disable serial port interrupts
    outb(COM1 + 3, 0x80); // Enable setting baud rate divider
    outb(COM1 + 0, 0x03); // Set divider for 38400 baud
    outb(COM1 + 1, 0x00); // Set divider high byte
    outb(COM1 + 3, 0x03); // 8 bits, no partity, one stop bit
    outb(COM1 + 2, 0xC7); // enable FIFO
    outb(COM1 + 4, 0x0b); // Enable IRQs, RTS and DSR
}

void debug_puts(char *msg) {

    for (char *ch = msg; *ch != 0; ch++) {
        outb(COM1, *ch);
    }

    outb(COM1, '\n');
}

void debug_putsl(char *msg, uint32_t val) {

    for (char *ch = msg; *ch != 0; ch++) {
        outb(COM1, *ch);
    }
    outb(COM1, ':');
    outb(COM1, ' ');
    outb(COM1, '0');
    outb(COM1, 'x');

    for (int i = 0; i < 8; i++) {
        outb(COM1, hex[val >> 28]);
        val <<= 4;
    }

    outb(COM1, '\n');
}
