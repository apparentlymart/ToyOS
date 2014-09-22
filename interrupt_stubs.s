

.macro irq_isr irqnum=0
.global irq\irqnum
irq\irqnum :
        cli
        push \irqnum
        jmp irq_stub
.endm

        irq_isr 0
        irq_isr 1
        irq_isr 2
        irq_isr 3
        irq_isr 4
        irq_isr 5
        irq_isr 6
        irq_isr 7
        irq_isr 8
        irq_isr 9
        irq_isr 10
        irq_isr 11
        irq_isr 12
        irq_isr 13
        irq_isr 14
        irq_isr 15

irq_stub:
        pusha                   # Save edi,esi,ebp,esp,ebx,edx,ecx and eax

        mov %ax, %ds            # (ax is the lower 16 bits of eax)
        push %eax               # Store the data segment descriptor

        mov %ax, 0x10           # Load kernal data segment descriptor
        mov %ds, %ax
        mov %es, %ax
        mov %fs, %ax
        mov %gs, %ax

        mov %eax, %esp          # Put stack pointer in irq_handler's first param

        call irq_handler

        pop %ebx                # Restore data segment descriptor
        mov %ds, %bx            # (bx is the lower 16 bits of ebx)
        mov %es, %bx
        mov %fs, %bx
        mov %gs, %bx

        popa                    # Retrieve registers from the stack
        iret
