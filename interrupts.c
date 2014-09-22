
#include "system.h"

struct idt_entry_s {
    uint16_t base_low;
    uint16_t selector;
    uint8_t dummy;
    uint8_t flags;
    uint16_t base_high;
} __attribute__((packed));
typedef struct idt_entry_s idt_entry;

struct idt_ptr_s {
    uint16_t size;
    uint32_t start;
} __attribute__((packed));
typedef struct idt_ptr_s idt_ptr;

idt_entry idt[256];
interrupt_irq_func irq_handlers[16] = {0};

void interrupts_set_gate(uint8_t num, uint32_t base, uint32_t selector, uint8_t flags) {
    idt[num].base_low = base & 0xffff;
    idt[num].base_high = base >> 16;

    idt[num].selector = selector;
    idt[num].flags = flags;
    idt[num].dummy = 0;
}

void interrupt_irq_handler(int32_t irq_num, interrupt_irq_func handler) {
    irq_handlers[irq_num] = handler;
}

static inline void lidt(void *base, uint16_t length) {
    struct {
        uint16_t length;
        uint32_t base;
    } __attribute__((packed)) IDTR;
    IDTR.base = (uint32_t)base;
    IDTR.length = length;
    __asm__ __volatile__ ("lidt (%0)" : : "r" (&IDTR));
}

extern void irq0();
extern void irq1();
extern void irq2();
extern void irq3();
extern void irq4();
extern void irq5();
extern void irq6();
extern void irq7();
extern void irq8();
extern void irq9();
extern void irq10();
extern void irq11();
extern void irq12();
extern void irq13();
extern void irq14();
extern void irq15();

void interrupts_init() {
    // Map IRQs 0 through 15 to IDT entries 32-47.
    outb(0x20, 0x11);
    outb(0xA0, 0x11);
    outb(0x21, 0x20);
    outb(0xA1, 0x28);
    outb(0x21, 0x04);
    outb(0xA1, 0x02);
    outb(0x21, 0x01);
    outb(0xA1, 0x01);
    outb(0x21, 0x0);
    outb(0xA1, 0x0);

    // Set up the IRQ stubs in the interrupt table
    interrupts_set_gate(32, (uint32_t)irq0, 0x8, 0x8e);
    interrupts_set_gate(33, (uint32_t)irq1, 0x8, 0x8e);
    interrupts_set_gate(34, (uint32_t)irq2, 0x8, 0x8e);
    interrupts_set_gate(35, (uint32_t)irq3, 0x8, 0x8e);
    interrupts_set_gate(36, (uint32_t)irq4, 0x8, 0x8e);
    interrupts_set_gate(37, (uint32_t)irq5, 0x8, 0x8e);
    interrupts_set_gate(38, (uint32_t)irq6, 0x8, 0x8e);
    interrupts_set_gate(39, (uint32_t)irq7, 0x8, 0x8e);
    interrupts_set_gate(40, (uint32_t)irq8, 0x8, 0x8e);
    interrupts_set_gate(41, (uint32_t)irq9, 0x8, 0x8e);
    interrupts_set_gate(42, (uint32_t)irq10, 0x8, 0x8e);
    interrupts_set_gate(43, (uint32_t)irq11, 0x8, 0x8e);
    interrupts_set_gate(44, (uint32_t)irq12, 0x8, 0x8e);
    interrupts_set_gate(45, (uint32_t)irq13, 0x8, 0x8e);
    interrupts_set_gate(46, (uint32_t)irq14, 0x8, 0x8e);
    interrupts_set_gate(47, (uint32_t)irq15, 0x8, 0x8e);

    // Install the IDT into the appropriate register.
    lidt(&idt, sizeof(idt) - 1);

    // Enable interrupts.
    // Not doing this yet because it makes us go into a reboot loop.
    // TODO: Figure out what's causing that and fix it.
    //__asm__ __volatile__ ("sti");
}

struct irq_state {
    uint32_t gs, fs, es, ds; // Backed up segment register values
    uint32_t edi, esi, ebp, esp, ebx, edx, ecx, eax; // Backed up by 'pusha'
    uint32_t irq_no; // Pushed by the irq stub
};

void irq_handler(struct irq_state *state) {
    // The state is passed into us by copying the stack pointer
    // into eax before calling in interrupt_stubs.s.
    // The irq_state struct is carefully designed to fit the shape
    // of data pushed by the interrupt stub, so we can access irq_no
    // relative to the given stack pointer.

    interrupt_irq_func handler = irq_handlers[state->irq_no];
    if (handler != 0) {
        handler();
    }

    // Signal the interrupt controllers that we're done.
    if (state->irq_no > 7) {
        // Handled by the secondary controller, so we need to signal it.
        outb(0xa0, 0x20);
    }
    // All interrupts are either directly or indirectly handled by the
    // primary controller (secondary is connected through it) so we
    // must always signal it.
    outb(0x20, 0x20);
}
