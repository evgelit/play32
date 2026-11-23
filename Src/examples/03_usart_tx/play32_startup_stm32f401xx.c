#include <stdint.h>

extern uint32_t _estack;
extern uint32_t _sidata;
extern uint32_t _sdata;
extern uint32_t _edata;
extern uint32_t _sbss;
extern uint32_t _ebss;

extern int main(void);

void Reset_Handler(void);
void Default_Handler(void);

void NMI_Handler(void)        __attribute__((weak, alias("Default_Handler")));
void HardFault_Handler(void)  __attribute__((weak, alias("Default_Handler")));
void MemManage_Handler(void)  __attribute__((weak, alias("Default_Handler")));
void BusFault_Handler(void)   __attribute__((weak, alias("Default_Handler")));
void UsageFault_Handler(void) __attribute__((weak, alias("Default_Handler")));
void SVC_Handler(void)        __attribute__((weak, alias("Default_Handler")));
void DebugMon_Handler(void)   __attribute__((weak, alias("Default_Handler")));
void PendSV_Handler(void)     __attribute__((weak, alias("Default_Handler")));
void SysTick_Handler(void)    __attribute__((weak, alias("Default_Handler")));

void TIM2_IRQHandler(void)    __attribute__((weak, alias("Default_Handler")));
void TIM3_IRQHandler(void)    __attribute__((weak, alias("Default_Handler")));
void TIM4_IRQHandler(void)    __attribute__((weak, alias("Default_Handler")));
void TIM5_IRQHandler(void)    __attribute__((weak, alias("Default_Handler")));

void Default_Handler(void) {
    while (1) {
    }
}

void Reset_Handler(void) {
    uint32_t *src = &_sidata;
    uint32_t *dst = &_sdata;
    while (dst < &_edata) {
        *dst++ = *src++;
    }
    dst = &_sbss;
    while (dst < &_ebss) {
        *dst++ = 0UL;
    }
    (*(volatile uint32_t *)0xE000ED88UL) |= (0xFUL << 20);
    __asm volatile ("dsb");
    __asm volatile ("isb");

    (void)main();

    while (1) {
    }
}

__attribute__((section(".isr_vector"), used))
const uint32_t vector_table[] = {
    (uint32_t)&_estack,           /* 0x00: Начальное значение указателя стека (SP) */
    (uint32_t)Reset_Handler,      /* 0x04: Reset Handler (точка старта программы) */
    (uint32_t)NMI_Handler,        /* 0x08: Non Maskable Interrupt */
    (uint32_t)HardFault_Handler,  /* 0x0C: Hard Fault (ошибка памяти/инструкций) */
    (uint32_t)MemManage_Handler,  /* 0x10: Memory Management Fault */
    (uint32_t)BusFault_Handler,   /* 0x14: Bus Fault */
    (uint32_t)UsageFault_Handler, /* 0x18: Usage Fault */
    0UL,                          /* 0x1C: Reserved */
    0UL,                          /* 0x20: Reserved */
    0UL,                          /* 0x24: Reserved */
    0UL,                          /* 0x28: Reserved */
    (uint32_t)SVC_Handler,        /* 0x2C: SVCall */
    (uint32_t)DebugMon_Handler,   /* 0x30: Debug Monitor */
    0UL,                          /* 0x34: Reserved */
    (uint32_t)PendSV_Handler,     /* 0x38: PendSV */
    (uint32_t)SysTick_Handler,    /* 0x3C: SysTick Timer */

    [16 + 28] = (uint32_t)TIM2_IRQHandler, /* IRQ 28: TIM2 global interrupt */
    [16 + 29] = (uint32_t)TIM3_IRQHandler, /* IRQ 29: TIM3 global interrupt */
    [16 + 30] = (uint32_t)TIM4_IRQHandler, /* IRQ 30: TIM4 global interrupt */
    [16 + 50] = (uint32_t)TIM5_IRQHandler  /* IRQ 50: TIM5 global interrupt */
};
