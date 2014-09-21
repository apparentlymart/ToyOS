
// memory.c
void *memset(void *dest, unsigned char val, int count);
int strlen(const char *str);

// io.c
void outb(unsigned short port, unsigned char data);
char inb(unsigned short port);

// video.c
extern unsigned short *screen;
#define SCREEN_WIDTH 80
#define SCREEN_HEIGHT 25
void screen_clear();

// debug.c
void debug_init();
void debug_puts(char *msg);
void debug_putsl(char *msg, uint32_t val);

// main.c
void main();
