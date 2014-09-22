
#include "system.h"

void announce_pci_device(uint32_t ids) {
    debug_putsl("Got PCI device", ids);
}

void main() {

    debug_init();
    debug_puts("ToyOS entered main()");

    screen_clear();

    screen[0] = 'T' | ((7) << 8);
    screen[1] = 'o' | ((7) << 8);
    screen[2] = 'y' | ((7) << 8);
    screen[3] = 'O' | ((7) << 8);
    screen[4] = 'S' | ((7) << 8);

    pci_enumerate_devices(&announce_pci_device);

    debug_puts("ToyOS exiting main()");
}
