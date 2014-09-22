
#include "system.h"

void announce_pci_device(uint32_t ids) {
    debug_putsl("Got PCI device", ids);
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

    debug_puts("ToyOS exiting main()");
}
