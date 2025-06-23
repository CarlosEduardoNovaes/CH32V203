#include <stdint.h>
#define SYS_USE_VECTORS   1         // 1: create interrupt vector table

extern void __cxa_pure_virtual() { while (1); }
extern void (*__preinit_array_start[]) (void) __attribute__((weak));
extern void (*__preinit_array_end[]) (void) __attribute__((weak));
extern void (*__init_array_start[]) (void) __attribute__((weak));
extern void (*__init_array_end[]) (void) __attribute__((weak));

void __libc_init_array(void) {
  uint32_t count, i;
  count = __preinit_array_end - __preinit_array_start;
  for (i = 0; i < count; i++) __preinit_array_start[i]();
  count = __init_array_end - __init_array_start;
  for (i = 0; i < count; i++) __init_array_start[i]();
}


// ===================================================================================
// C version of CH32V203 Startup .s file from WCH
// ===================================================================================
extern uint32_t _sbss;
extern uint32_t _ebss;
extern uint32_t _data_lma;
extern uint32_t _data_vma;
extern uint32_t _edata;

// Prototypes
int main(void)                __attribute__((section(".text.main"), used));
void jump_reset(void)         __attribute__((section(".init.jump"), naked, used));
// const uint32_t init_data[]    __attribute__((section(".init.data"), used));
void (*const vectors[])(void) __attribute__((section(".vector"), used));
void reset_handler(void)      __attribute__((section(".text.reset_handler"), naked, used));

#if SYS_USE_VECTORS > 0
// Unless a specific handler is overridden, it just spins forever
void default_handler(void)    __attribute__((section(".text.vector_handler"), naked, used));
void default_handler(void)    { while(1); }

// All interrupt handlers are aliased to default_handler unless overridden individually
#define DUMMY_HANDLER __attribute__((section(".text.vector_handler"), weak, alias("default_handler"), used))
DUMMY_HANDLER void NMI_Handler(void);
DUMMY_HANDLER void HardFault_Handler(void);
DUMMY_HANDLER void Ecall_M_Mode_Handler(void);
DUMMY_HANDLER void Ecall_U_Mode_Handler(void);
DUMMY_HANDLER void Break_Point_Handler(void);
DUMMY_HANDLER void SysTick_Handler(void);
DUMMY_HANDLER void SW_Handler(void);
DUMMY_HANDLER void WWDG_IRQHandler(void);
DUMMY_HANDLER void PVD_IRQHandler(void);
DUMMY_HANDLER void TAMPER_IRQHandler(void);
DUMMY_HANDLER void RTC_IRQHandler(void);
DUMMY_HANDLER void FLASH_IRQHandler(void);
DUMMY_HANDLER void RCC_IRQHandler(void);
DUMMY_HANDLER void EXTI0_IRQHandler(void);
DUMMY_HANDLER void EXTI1_IRQHandler(void);
DUMMY_HANDLER void EXTI2_IRQHandler(void);
DUMMY_HANDLER void EXTI3_IRQHandler(void);
DUMMY_HANDLER void EXTI4_IRQHandler(void);
DUMMY_HANDLER void DMA1_Channel1_IRQHandler(void);
DUMMY_HANDLER void DMA1_Channel2_IRQHandler(void);
DUMMY_HANDLER void DMA1_Channel3_IRQHandler(void);
DUMMY_HANDLER void DMA1_Channel4_IRQHandler(void);
DUMMY_HANDLER void DMA1_Channel5_IRQHandler(void);
DUMMY_HANDLER void DMA1_Channel6_IRQHandler(void);
DUMMY_HANDLER void DMA1_Channel7_IRQHandler(void);
DUMMY_HANDLER void ADC1_2_IRQHandler(void);
DUMMY_HANDLER void USB_HP_CAN1_TX_IRQHandler(void);
DUMMY_HANDLER void USB_LP_CAN1_RX0_IRQHandler(void);
DUMMY_HANDLER void CAN1_RX1_IRQHandler(void);
DUMMY_HANDLER void CAN1_SCE_IRQHandler(void);
DUMMY_HANDLER void EXTI9_5_IRQHandler(void);
DUMMY_HANDLER void TIM1_BRK_IRQHandler(void);
DUMMY_HANDLER void TIM1_UP_IRQHandler(void);
DUMMY_HANDLER void TIM1_TRG_COM_IRQHandler(void);
DUMMY_HANDLER void TIM1_CC_IRQHandler(void);
DUMMY_HANDLER void TIM2_IRQHandler(void);
DUMMY_HANDLER void TIM3_IRQHandler(void);
DUMMY_HANDLER void TIM4_IRQHandler(void);
DUMMY_HANDLER void I2C1_EV_IRQHandler(void);
DUMMY_HANDLER void I2C1_ER_IRQHandler(void);
DUMMY_HANDLER void I2C2_EV_IRQHandler(void);
DUMMY_HANDLER void I2C2_ER_IRQHandler(void);
DUMMY_HANDLER void SPI1_IRQHandler(void);
DUMMY_HANDLER void SPI2_IRQHandler(void);
DUMMY_HANDLER void USART1_IRQHandler(void);
DUMMY_HANDLER void USART2_IRQHandler(void);
DUMMY_HANDLER void USART3_IRQHandler(void);
DUMMY_HANDLER void EXTI15_10_IRQHandler(void);
DUMMY_HANDLER void RTCAlarm_IRQHandler(void);
DUMMY_HANDLER void USBWakeUp_IRQHandler(void);
DUMMY_HANDLER void USBHD_IRQHandler(void);
DUMMY_HANDLER void USBHDWakeUp_IRQHandler(void);
DUMMY_HANDLER void UART4_IRQHandler(void);
DUMMY_HANDLER void DMA1_Channel8_IRQHandler(void);
#endif  // SYS_USE_VECTORS > 0

// FLASH starts with a jump to the reset handler
void jump_reset(void) { asm volatile("j reset_handler"); }

// // Afterwards there comes some data
// const uint32_t init_data[] = {
//   0x00000013, 0x00000013, 0x00000013, 0x00000013,
//   0x00000013, 0x00000013, 0x00000013, 0x00000013,
//   0x00000013, 0x00000013, 0x00000013, 0x00000013,
//   0x00100073
// };

// Interrupt vector table
void (* const vectors[])(void) = {
  // RISC-V handlers
  jump_reset,                       //  0 - Reset
  #if SYS_USE_VECTORS > 0
  0,                                //  1 - Reserved
  NMI_Handler,                      //  2 - NMI Handler
  HardFault_Handler,                //  3 - Hard Fault Handler
  0,                                //  4 - Reserved
  Ecall_M_Mode_Handler,             //  5 - Ecall M Mode Handler
  0,                                //  6 - Reserved
  0,                                //  7 - Reserved
  Ecall_U_Mode_Handler,             //  8 - Ecall U Mode Handler
  Break_Point_Handler,              //  9 - Break Point Handler
  0,                                // 10 - Reserved
  0,                                // 11 - Reserved
  SysTick_Handler,                  // 12 - SysTick Handler
  0,                                // 13 - Reserved
  SW_Handler,                       // 14 - SW Handler
  0,                                // 15 - Reserved
  
  // Peripheral handlers
  WWDG_IRQHandler,                  // 16 - Window Watchdog
  PVD_IRQHandler,                   // 17 - PVD through EXTI Line detect
  TAMPER_IRQHandler,                // 18 - TAMPER
  RTC_IRQHandler,                   // 19 - RTC
  FLASH_IRQHandler,                 // 20 - Flash
  RCC_IRQHandler,                   // 21 - RCC
  EXTI0_IRQHandler,                 // 22 - EXTI Line 0
  EXTI1_IRQHandler,                 // 23 - EXTI Line 1
  EXTI2_IRQHandler,                 // 24 - EXTI Line 2
  EXTI3_IRQHandler,                 // 25 - EXTI Line 3
  EXTI4_IRQHandler,                 // 26 - EXTI Line 4
  DMA1_Channel1_IRQHandler,         // 27 - DMA1 Channel 1
  DMA1_Channel2_IRQHandler,         // 28 - DMA1 Channel 2
  DMA1_Channel3_IRQHandler,         // 29 - DMA1 Channel 3
  DMA1_Channel4_IRQHandler,         // 30 - DMA1 Channel 4
  DMA1_Channel5_IRQHandler,         // 31 - DMA1 Channel 5
  DMA1_Channel6_IRQHandler,         // 32 - DMA1 Channel 6
  DMA1_Channel7_IRQHandler,         // 33 - DMA1 Channel 7
  ADC1_2_IRQHandler,                // 34 - ADC1/2
  USB_HP_CAN1_TX_IRQHandler,        // 35 - USB HP and CAN1 TX
  USB_LP_CAN1_RX0_IRQHandler,       // 36 - USB LP and CAN1 RX0
  CAN1_RX1_IRQHandler,              // 37 - CAN1 RX1
  CAN1_SCE_IRQHandler,              // 38 - CAN1 SCE
  EXTI9_5_IRQHandler,               // 39 - EXTI Line 9..5
  TIM1_BRK_IRQHandler,              // 40 - TIM1 Break
  TIM1_UP_IRQHandler,               // 41 - TIM1 Update
  TIM1_TRG_COM_IRQHandler,          // 42 - TIM1 Trigger and Commutation
  TIM1_CC_IRQHandler,               // 43 - TIM1 Capture Compare
  TIM2_IRQHandler,                  // 44 - TIM2
  TIM3_IRQHandler,                  // 45 - TIM3
  TIM4_IRQHandler,                  // 46 - TIM4
  I2C1_EV_IRQHandler,               // 47 - I2C1 Event
  I2C1_ER_IRQHandler,               // 48 - I2C1 Error
  I2C2_EV_IRQHandler,               // 49 - I2C2 Event
  I2C2_ER_IRQHandler,               // 50 - I2C2 Error
  SPI1_IRQHandler,                  // 51 - SPI1
  SPI1_IRQHandler,                  // 52 - SPI2
  USART1_IRQHandler,                // 53 - USART1
  USART2_IRQHandler,                // 54 - USART2
  USART3_IRQHandler,                // 55 - USART3
  EXTI15_10_IRQHandler,             // 56 - EXTI Line 15..10
  RTCAlarm_IRQHandler,              // 57 - RTC Alarm through EXTI Line
  USBWakeUp_IRQHandler,             // 58 - USB Wake up from suspend
  USBHD_IRQHandler,                 // 59 - USBHD Break
  USBHDWakeUp_IRQHandler,           // 60 - USBHD Wake up from suspend
  UART4_IRQHandler,                 // 61 - UART4
  DMA1_Channel8_IRQHandler          // 62 - DMA1 Channel8
  #endif  // SYS_USE_VECTORS > 0
};

// Reset handler
void reset_handler(void) {
  uint32_t *src, *dst;
  
  // Set pointers, vectors, processor status, and interrupts
  asm volatile(
  " .option push              \n\
    .option norelax           \n\
    la gp, __global_pointer$  \n\
    .option pop               \n\
    la sp, _eusrstack         \n"
    #if __GNUC__ > 10
    ".option arch, +zicsr     \n"
    #endif
  " li a0, 0x1f               \n\
    csrw 0xbc0, a0            \n\
    li a0, 0x88               \n\
    csrw mstatus, a0          \n\
    li a1, 0x3                \n\
    csrw 0x804, a1            \n\
    la a0, vectors            \n\
    or a0, a0, a1             \n\
    csrw mtvec, a0            \n\
    csrw mepc, %[main]        \n"
    : : [main] "r" (main) : "a0", "a1" , "memory"
  );

  // Copy data from FLASH to RAM
  src = &_data_lma;
  dst = &_data_vma;
  while(dst < &_edata) *dst++ = *src++;

  // Clear uninitialized variables
  #if SYS_CLEAR_BSS > 0
  dst = &_sbss;
  while(dst < &_ebss) *dst++ = 0;
  #endif


  __libc_init_array();


  // Init system
  

  // Return
  asm volatile("mret");
}
