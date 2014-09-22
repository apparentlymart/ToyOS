
#include "system.h"

keyboard_func callback_func;

void keyboard_handler() {
    // Read from the keyboard buffer
    uint8_t scancode = inb(0x60);
    callback_func(scancode);
}

void keyboard_init(keyboard_func func) {
    callback_func = func;

    // Enable the keyboard interrupt.
    // This tells the first interrupt controller to only pay
    // attention to IRQ1, which is the keyboard.
    // FIXME: This should be done in a more respectful way that
    // doesn't force all of the other IRQs off.
    outb(0x21, ~2);
    // Mask everything on the second interrupt controller.
    outb(0xa1, ~0);

    interrupt_irq_handler(1, keyboard_handler);
}
