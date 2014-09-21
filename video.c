
#include "system.h"

unsigned short *screen = 0xb8000;

void screen_clear() {
    // Two bytes per character cell, to clear both the attributes and
    // the contents.
    memset((unsigned char*)screen, 0, SCREEN_WIDTH * SCREEN_HEIGHT * 2);
}
