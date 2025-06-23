// ===================================================================================
// Project:   Example for CH32V203
// Version:   v1.0
// Year:      2023
// Author:    Stefan Wagner
// Github:    https://github.com/wagiminator
// EasyEDA:   https://easyeda.com/wagiminator
// License:   http://creativecommons.org/licenses/by-sa/3.0/
// ===================================================================================
//
// Description:
// ------------
// Blink example.
//
// References:
// -----------
// - WCH Nanjing Qinheng Microelectronics: http://wch.cn
//
// Compilation Instructions:
// -------------------------
// - Make sure GCC toolchain (gcc-riscv64-unknown-elf, newlib) and Python3 with
//   chprog and rvprog (via pip) are installed. In addition, Linux requires access
//   rights to the USB bootloader.
// - Press the BOOT0 button on the MCU board and keep it pressed while connecting it
//   via USB to your PC.
// - Run 'make flash'.


// ===================================================================================
// Libraries, Definitions and Macros
// ===================================================================================
#include <system/system.h>                               // system functions


//#include <gpio.h>                                 // GPIO functions



import pinled;
import registers;


using FieldLedSet = BitView32<0x40010814, 15, 1, bool> ;
using FieldLedReset = BitView32<0x40010810, 15, 1, bool> ;


// ===================================================================================
// Main Function
// ===================================================================================
extern "C"
int main(void) {
  // System Init
  SYS_init();
    NVIC_EnableIRQ(SysTicK_IRQn);     // enable the SysTick IRQ
  // Setup
  //PIN_output(PIN_LED);                            // set LED pin to output
  pinled::init();
  //GPIOA->BSHR = 1 << 15;
  pinled::turnOff();
  
  // Loop
  while(1) {
    /*
      Set led
     */
    FieldLedSet::write(true); // set led
    DLY_ms(50);                                  // wait a bit
    FieldLedReset::write(true); //reset led
    DLY_ms(50);                             
    FieldLedSet::write(true); // set led
    DLY_ms(50);                                  // wait a bit
    FieldLedReset::write(true); //reset led
    DLY_ms(50);                             
    FieldLedSet::write(true); // set led
    DLY_ms(50);
    FieldLedReset::write(true); //reset led
    DLY_ms(50);                             
    FieldLedSet::write(true); // set led
    DLY_ms(50);
      /*
      Clear led
     */
    FieldLedReset::write(true); //reset led
    // pinled::turnOn();
    // DLY_ms(50);                                  // wait a bit
    // pinled::turnOff();
    // DLY_ms(50);                                  // wait a bit
    // pinled::turnOn();
    // DLY_ms(50);                                  // wait a bit
    // pinled::turnOff();
    // DLY_ms(50);                                  // wait a bit
    // pinled::turnOn();
    // DLY_ms(50);                                  // wait a bit
    // pinled::turnOff();
    DLY_ms(700);                                  // wait a bit
  }
}