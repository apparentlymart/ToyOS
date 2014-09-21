
#include "system.h"

void *memset(void *dest, unsigned char val, int count) {
    char *buf = (char*)dest;
    // Simple implementation for now.
    for (int i = 0; i < count; i++) {
        buf[i] = val;
    }
    return dest;
}
