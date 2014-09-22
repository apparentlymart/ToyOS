
typedef short int16_t;
typedef int int32_t;
typedef char int8_t;
typedef unsigned short uint16_t;
typedef unsigned int uint32_t;
typedef unsigned char uint8_t;

// memory.c
void *memset(void *dest, uint8_t val, int count);
int strlen(const char *str);

// io.c
void outb(uint16_t port, uint8_t data);
uint8_t inb(uint16_t port);
void outs(uint16_t port, uint16_t data);
uint16_t ins(uint16_t port);
void outl(uint16_t port, uint32_t data);
uint32_t inl(uint16_t port);
void cpu_type_string(char *out);

// video.c
extern unsigned short *screen;
#define SCREEN_WIDTH 80
#define SCREEN_HEIGHT 25
void screen_clear();
void screen_write_char(uint8_t col, uint8_t row, uint8_t attr, uint8_t c);
void screen_write_string(uint8_t col, uint8_t row, uint8_t attr, uint8_t *str);

// pci.c
typedef void (*pci_scan_func)(uint32_t ids);
uint32_t pci_get_device_ids(uint8_t bus, uint8_t slot, uint8_t func);
uint16_t pci_get_device_class_ids(uint8_t bus, uint8_t slot, uint8_t func);
uint8_t pci_get_device_header_type(uint8_t bus, uint8_t slot, uint8_t func);
void pci_enumerate_devices(pci_scan_func cb);

// interrupts.c
typedef void(*interrupt_irq_func)();
void interrupts_init();
void interrupt_irq_handler(int32_t irq_num, interrupt_irq_func handler);

// debug.c
void debug_init();
void debug_puts(char *msg);
void debug_putsl(char *msg, uint32_t val);

// main.c
void main();
