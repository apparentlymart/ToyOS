
#include "system.h"

void outb(uint16_t port, uint8_t data) {
    __asm__ __volatile__ ("outb %1, %0" : : "dN" (port), "a" (data));
}

uint8_t inb(uint16_t port) {
    uint8_t rv;
    __asm__ __volatile__ ("inb %1, %0" : "=a" (rv) : "dN" (port));
    return rv;
}

void outl(uint16_t port, uint32_t data) {
    __asm__ __volatile__ ("outl %1, %0" : : "dN" (port), "a" (data));
}

uint32_t inl(uint16_t port) {
    uint32_t rv;
    __asm__ __volatile__ ("inl %1, %0" : "=a" (rv) : "dN" (port));
    return rv;
}
