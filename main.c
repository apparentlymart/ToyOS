
#include "system.h"

volatile int keypress = 0;
volatile uint8_t last_key_pressed;

void announce_pci_device(uint32_t ids) {
    debug_putsl("Got PCI device", ids);
}

void handle_keypress(uint8_t scancode) {
    last_key_pressed = scancode;
    keypress = 1;
}

void main() {

    debug_init();
    debug_puts("ToyOS entered main()");

    char cpu_type_msg[] = "Running ????????????";
    cpu_type_string(cpu_type_msg + 8); // Writes over the question marks.
    debug_puts(cpu_type_msg);

    screen_clear();
    screen_write_string(40 - 7, 5, 0xe, "Welcome to ToyOS");
    screen_write_char(38, 7, 0xf, 1);
    screen_write_char(42, 7, 0xf, 2);
    screen_write_string(31, 15, 0x7, cpu_type_msg);

    pci_enumerate_devices(&announce_pci_device);

    keyboard_init(handle_keypress);
    interrupts_init();

    // Go into a busy loop waiting for keypresses.
    // FIXME: Don't use a busy loop for this.
    while (1) {
        if (keypress) {
            keypress = 0;
            debug_putsl("Key event", last_key_pressed);
        }
    }

    debug_puts("ToyOS exiting main()");
}
