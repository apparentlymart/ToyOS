
#include "system.h"

uint16_t *screen = 0xb8000;

void screen_clear() {
    // Two bytes per character cell, to clear both the attributes and
    // the contents.
    memset((unsigned char*)screen, 0, SCREEN_WIDTH * SCREEN_HEIGHT * 2);
}

void screen_write_char(uint8_t col, uint8_t row, uint8_t attr, uint8_t c) {
    screen[col + row * SCREEN_WIDTH] = c | (uint16_t)(attr) << 8;
}

void screen_write_string(uint8_t col, uint8_t row, uint8_t attr, uint8_t *str) {
    uint16_t *pos = &(screen[col + row * SCREEN_WIDTH]);

    for (; *str !=0; pos++, str++) {
        *pos = ((uint16_t)(*str)) | (uint16_t)(attr) << 8;
    }
}
