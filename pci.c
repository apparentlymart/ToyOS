
#include "system.h"

uint32_t pci_config_read_long(uint8_t bus, uint8_t slot, uint8_t func) {
    uint32_t lbus = (uint32_t)bus;
    uint32_t lslot = (uint32_t)slot;
    uint32_t lfunc = (uint32_t)func;

    uint32_t address = (uint32_t)(
        (lbus << 16) |
        (lslot << 11) |
        (lfunc << 8) |
        (uint32_t)0x80000000
    );

    // Write address to the address selection port
    outl(0xcf8, address);
    return inl(0xcfc);
}

uint16_t pci_config_read_short(uint8_t bus, uint8_t slot, uint8_t func, uint8_t offset) {
    uint32_t lbus = (uint32_t)bus;
    uint32_t lslot = (uint32_t)slot;
    uint32_t lfunc = (uint32_t)func;

    uint32_t address = (uint32_t)(
        (lbus << 16) |
        (lslot << 11) |
        (lfunc << 8) |
        (offset & 0xfc) |
        (uint32_t)0x80000000
    );

    // Write address to the address selection port
    outl(0xcf8, address);
    return (uint16_t)(
        (inl(0xcfc) >> ((offset & 2) * 8)) & 0xffff
    );
}

uint32_t pci_get_device_ids(uint8_t bus, uint8_t slot, uint8_t function) {
    return pci_config_read_long(bus, slot, function);
}

uint16_t pci_get_device_class_ids(uint8_t bus, uint8_t slot, uint8_t function) {
    return pci_config_read_short(bus, slot, function, 4);
}

int pci_device_is_multifunction(uint8_t bus, uint8_t slot) {
    uint16_t header_type = pci_config_read_short(bus, slot, 0, 0x0c);
    return (header_type & 0x80) ? 1 : 0;
}

uint8_t pci_get_device_header_type(uint8_t bus, uint8_t slot, uint8_t function) {
    // Mask off the BIST part in the first byte.
    // (though this is returning an 8-bit int so it'll get dropped anyway)
    return 0xff & pci_config_read_short(bus, slot, 0, 0x0c);
}

void pci_scan_bus(uint8_t bus, pci_scan_func cb) {
    for (uint8_t slot = 0; slot < 32; slot++) {
        uint8_t func = 0;
        uint32_t pci_dev = pci_get_device_ids(bus, slot, func);

        if (pci_dev == 0xffffffff) continue;

        uint8_t header_type = pci_get_device_header_type(bus, slot, func);

        int function_count = (header_type & 0x80) ? 8 : 1;
        while (1) {
            header_type &= ~0x80; // mask out the multifunction flag
            cb(pci_dev);

            if (header_type == 1) {
                // PCI-to-PCI bridge.
                // TODO: Implement recursive enumeration.
                debug_putsl("Unsupported PCI-to-PCI bridge", pci_dev);
            }

            func++;
            if (func < function_count) {
                pci_dev = pci_get_device_ids(bus, slot, func);
                header_type = pci_get_device_header_type(bus, slot, func);
            }
            else {
                break;
            }
        }
    }
}

void pci_enumerate_devices(pci_scan_func cb) {
    pci_scan_bus(0, cb);
}
