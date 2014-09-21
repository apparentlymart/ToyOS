
#include "system.h"

void main() {

    debug_init();
    debug_puts("ToyOS entered main()");

    screen_clear();

    screen[0] = 'T' | ((7) << 8);
    screen[1] = 'o' | ((7) << 8);
    screen[2] = 'y' | ((7) << 8);
    screen[3] = 'O' | ((7) << 8);
    screen[4] = 'S' | ((7) << 8);

    debug_puts("ToyOS exiting main()");
}
