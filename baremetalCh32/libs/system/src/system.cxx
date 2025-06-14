// ===================================================================================
// Basic System Functions for CH32V203                                        * v1.1 *
// ===================================================================================
//
// This file must be included!!!!
//
// References:
// -----------
// - WCH Nanjing Qinheng Microelectronics: http://wch.cn
//
// 2023 by Stefan Wagner:   https://github.com/wagiminator

#include "system/system.h"

// ===================================================================================
// Setup Microcontroller (this function is called automatically at startup)
// ===================================================================================
void SYS_init(void) {
  // Init system clock
  #if SYS_CLK_INIT > 0
    RCC->INTR = 0x009F0000;                               // Clear ready flags
    CLK_init();                                           // Setup system clock
    #if F_CPU > 60000000
      FLASH->CTLR &= ~FLASH_CTLR_SCKMOD;                  // FLASH CLK = SYSCLK / 2
    #else
      FLASH->CTLR |=  FLASH_CTLR_SCKMOD;                  // FLASH CLK = SYSCLK
    #endif
  #endif

  // Init SYSTICK
  #if SYS_TICK_INIT > 0
  STK_init();
  #endif

  // Enable GPIO
  #if SYS_GPIO_EN > 0
  RCC->APB2PCENR |= RCC_IOPAEN | RCC_IOPBEN | RCC_IOPCEN | RCC_IOPDEN;
  #endif
}

// ===================================================================================
// System Clock Functions
// ===================================================================================

// Init internal oscillator (non PLL) as system clock source
void CLK_init_HSI(void) {
  RCC->CFGR0 = RCC_HPRE_DIV1                              // HCLK = SYSCLK
             | RCC_PPRE2_DIV1                             // PCLK2 = HCLK
             | RCC_PPRE1_DIV1                             // PCLK1 = HCLK
             | RCC_SW_HSI;                                // HSI as system clock source
  while((RCC->CFGR0 & RCC_SWS));                          // Wait for HSI
}

// Init internal oscillator with PLL as system clock source
void CLK_init_HSI_PLL(void) {
  EXTEN->EXTEN_CTR |= EXTEN_PLL_HSI_PRE;                  // HSI not divided for PLL
  RCC->CFGR0 = RCC_HPRE_DIV1                              // HCLK = SYSCLK
             | RCC_PPRE2_DIV1                             // PCLK2 = HCLK
             | RCC_PPRE1_DIV1                             // PCLK1 = HCLK
             | RCC_PLLSRC_HSI_Div2                        // HSI for PLL entry
             | CLK_MUL;                                   // PLL multiplier
  RCC->CTLR |= RCC_PLLON;                                 // Enable PLL
  while(!(RCC->CTLR & RCC_PLLRDY));                       // Wait till PLL is ready      
  RCC->CFGR0 |= RCC_SW_PLL;                               // PLL as system clock source
  while((RCC->CFGR0 & RCC_SWS) != (uint32_t)0x08);        // Wait for PLL
}

// Init external crystal (non PLL) as system clock source
void CLK_init_HSE(void) {
  RCC->APB2PCENR |= RCC_AFIOEN;                           // enable auxiliary clock module
  AFIO->PCFR1 |= AFIO_PCFR1_PD01_REMAP;                   // Use PD0/PD1 for crystal
  RCC->CTLR   |= RCC_HSEON;                               // Turn on HSE
  while(!(RCC->CTLR & RCC_HSERDY));                       // wait till HSE is ready
  RCC->CFGR0   = RCC_HPRE_DIV1                            // HCLK = SYSCLK
               | RCC_PPRE2_DIV1                           // PCLK2 = HCLK
               | RCC_PPRE1_DIV1                           // PCLK1 = HCLK
               | RCC_SW_HSE;                              // HSE as system clock source
  while((RCC->CFGR0 & RCC_SWS) != (uint32_t)0x04);        // Wait for HSE
}

// Init external oscillator with PLL as system clock source
void CLK_init_HSE_PLL(void) {
  RCC->APB2PCENR |= RCC_AFIOEN;                           // enable auxiliary clock module
  AFIO->PCFR1 |= AFIO_PCFR1_PD01_REMAP;                   // Use PD0/PD1 for crystal
  RCC->CTLR   |= RCC_HSEON;                               // Turn on HSE
  while(!(RCC->CTLR & RCC_HSERDY));                       // wait till HSE is ready
  RCC->CFGR0   = RCC_HPRE_DIV1                            // HCLK = SYSCLK
               | RCC_PPRE2_DIV1                           // PCLK2 = HCLK
               | RCC_PPRE1_DIV1                           // PCLK1 = HCLK
               | RCC_PLLSRC_HSE                           // HSE for PLL entry
               | RCC_PLLXTPRE_HSE                         // HSE not divided for PLL entry
               | CLK_MUL;                                 // PLL multiplier
  RCC->CTLR    |= RCC_PLLON;                              // Enable PLL
  while(!(RCC->CTLR & RCC_PLLRDY));                       // Wait till PLL is ready      
  RCC->CFGR0   |= RCC_SW_PLL;                             // PLL as system clock source
  while((RCC->CFGR0 & RCC_SWS) != (uint32_t)0x08);        // Wait for PLL
}

// Reset system clock to default state
void CLK_reset(void) {
  FLASH->CTLR &= ~FLASH_CTLR_SCKMOD;
  RCC->INTR = 0x009F0000;
  RCC->CTLR |= RCC_HSION;
  while(!(RCC->CTLR & RCC_HSIRDY));
  RCC->CFGR0 = RCC_HPRE_DIV1 | RCC_PPRE2_DIV1 | RCC_PPRE1_DIV1 | RCC_SW_HSI;
  while((RCC->CFGR0 & RCC_SWS));
  RCC->CFGR0 &= 0x0000FFFF;
}

// Setup pin PA8 for MCO (output, push-pull, 50MHz, auxiliary)
void MCO_init(void) {
  RCC->APB2PCENR |= RCC_AFIOEN | RCC_IOPAEN;
  GPIOA->CFGHR    = (GPIOA->CFGHR & ~((uint32_t)0b1111<<(0<<2))) | ((uint32_t)0b1011<<(0<<2));
}

// ===================================================================================
// Real-Time Clock (RTC) Functions
// ===================================================================================

// Init RTC with internal low-speed clock
void RTC_init_LSI(void) {
  //PWR->CTLR |= PWR_CTLR_DBP;          // enable access to backup domain
  //RCC->APB1PCENR |= RCC_BKPEN;        // enable backup domain interface
  RCC->RSTSCKR |= RCC_LSION;            // enable LSI
  while(!(RCC->RSTSCKR & RCC_LSIRDY));  // wait till LSI is ready
  RCC->BDCTLR |= RCC_RTCSEL_LSI;        // select LSI as RTC clock source
  RCC->BDCTLR |= RCC_RTCEN;             // enable RTC
  RTC->CTLRL &= ~RTC_CTLRL_RSF;         // start synchronization
  while((~RTC->CTLRL) & (RTC_CTLRL_RSF | RTC_CTLRL_RTOFF));   // wait ready
  RTC->CTLRL |= RTC_CTLRL_CNF;          // enter configuration mode
  RTC->PSCRL  = LSI_VALUE;              // set prescaler for 1 second ticks
  RTC->PSCRH  = 0;
  RTC->CTLRL &= ~RTC_CTLRL_CNF;         // exit configuration mode
}

// Init RTC with external low-speed clock
void RTC_init_LSE(void) {
  RCC->BDCTLR |= RCC_LSEON;             // enable LSE
  while(!(RCC->BDCTLR & RCC_LSERDY));   // wait till LSE is ready
  RCC->BDCTLR |= RCC_RTCSEL_LSE;        // select LSE as RTC clock source
  RCC->BDCTLR |= RCC_RTCEN;             // enable RTC
  RTC->CTLRL &= ~RTC_CTLRL_RSF;         // start synchronization
  while((~RTC->CTLRL) & (RTC_CTLRL_RSF | RTC_CTLRL_RTOFF));   // wait ready
  RTC->CTLRL |= RTC_CTLRL_CNF;          // enter configuration mode
  RTC->PSCRL  = LSE_VALUE;              // set prescaler for 1 second ticks
  RTC->PSCRH  = 0;
  RTC->CTLRL &= ~RTC_CTLRL_CNF;         // exit configuration mode
}

// Set RTC counter value
void RTC_set(uint32_t n) {
  RTC->CTLRL &= ~RTC_CTLRL_RSF;         // start synchronization
  while((~RTC->CTLRL) & (RTC_CTLRL_RSF | RTC_CTLRL_RTOFF));   // wait ready
  RTC->CTLRL |= RTC_CTLRL_CNF;          // enter configuration mode
  RTC->CNTL   = n;                      // set counter value
  RTC->CNTH   = n >> 16;
  RTC->CTLRL &= ~RTC_CTLRL_CNF;         // exit configuration mode
}

// Set RTC ALARM value
void RTC_ALARM_set(uint32_t n) {
  RTC->CTLRL &= ~RTC_CTLRL_RSF;         // start synchronization
  while((~RTC->CTLRL) & (RTC_CTLRL_RSF | RTC_CTLRL_RTOFF));   // wait ready
  RTC->CTLRL |= RTC_CTLRL_CNF;          // enter configuration mode
  RTC->ALRML  = n;                      // set ALARM value
  RTC->ALRMH  = n >> 16;
  RTC->CTLRL &= ~RTC_CTLRL_CNF;         // exit configuration mode
}

// ===================================================================================
// Delay Functions
// ===================================================================================

// Wait n counts of SysTick
void DLY_ticks(uint32_t n) {
  uint32_t end = STK->CNTL + n;
  while(((int32_t)(STK->CNTL - end)) < 0 );
}

// ===================================================================================
// Independent Watchdog Timer (IWDG) Functions
// ===================================================================================

// Start independent watchdog timer (IWDG) with given amount of WDG clock cycles
// (ticks). One tick is 64/40 ms long, max ticks is 4095 = 6552ms.
// Once the IWDG has been started, it cannot be disabled, only reloaded (feed).
// It can be stopped by disabling the internal low-speed clock (LSI).
void IWDG_start(uint16_t ticks) {
  LSI_enable();                         // enable internal low-speed clock (LSI)
  IWDG->CTLR = 0x5555;                  // allow register modification
  while(IWDG->STATR & IWDG_PVU);        // wait for clock register to be ready
  IWDG->PSCR = 0b100;                   // set LSI clock prescaler 64
  while(IWDG->STATR & IWDG_RVU);        // wait for reload register to be ready
  IWDG->RLDR = ticks;                   // set watchdog counter reload value
  IWDG->CTLR = 0xAAAA;                  // load reload value into watchdog counter
  IWDG->CTLR = 0xCCCC;                  // enable IWDG
}

// Reload watchdog counter with n ticks, n<=4095
void IWDG_reload(uint16_t ticks) {
  IWDG->CTLR = 0x5555;                  // allow register modification
  while(IWDG->STATR & IWDG_RVU);        // wait for reload register to be ready
  IWDG->RLDR = ticks;                   // set watchdog counter reload value
  IWDG->CTLR = 0xAAAA;                  // load reload value into watchdog counter
}

// ===================================================================================
// Sleep Functions
// ===================================================================================

// Put device into sleep, wake up by interrupt
void SLEEP_WFI_now(void) {
  PWR->CTLR &= ~PWR_CTLR_PDDS;          // set power-down mode to SLEEP
  __WFI();                              // wait for interrupt
}

// Put device into sleep, wake up by event
void SLEEP_WFE_now(void) {
  PWR->CTLR &= ~PWR_CTLR_PDDS;          // set power-down mode to SLEEP
  __WFE();                              // wait for event
}

// Put device into stop, wake up interrupt
void STOP_WFI_now(void) {
  PWR->CTLR   &= ~PWR_CTLR_PDDS;        // set power-down mode to STOP
  PFIC->SCTLR |= PFIC_SLEEPDEEP;
  __WFI();                              // wait for interrupt
  PFIC->SCTLR &= ~PFIC_SLEEPDEEP;       // unset deep sleep mode
}

// Put device into stop, wake up event
void STOP_WFE_now(void) {
  PWR->CTLR   &= ~PWR_CTLR_PDDS;        // set power-down mode to STOP
  PFIC->SCTLR |= PFIC_SLEEPDEEP;
  __WFE();                              // wait for event
  PFIC->SCTLR &= ~PFIC_SLEEPDEEP;       // unset deep sleep mode
}

// Put device into standby (deep sleep), wake up interrupt
void STDBY_WFI_now(void) {
  PWR->CTLR   |= PWR_CTLR_PDDS;         // set power-down mode to STANDBY
  PFIC->SCTLR |= PFIC_SLEEPDEEP;
  __WFI();                              // wait for interrupt
  PFIC->SCTLR &= ~PFIC_SLEEPDEEP;       // unset deep sleep mode
}

// Put device into standby (deep sleep), wake up event
void STDBY_WFE_now(void) {
  PWR->CTLR   |= PWR_CTLR_PDDS;         // set power-down mode to STANDBY
  PFIC->SCTLR |= PFIC_SLEEPDEEP;
  __WFE();                              // wait for event
  PFIC->SCTLR &= ~PFIC_SLEEPDEEP;       // unset deep sleep mode
}

