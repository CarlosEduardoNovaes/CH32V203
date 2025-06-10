module;
#include <system/ch32v203.h>

export module pinled;

namespace pinled
{
  export void init()
  {
    GPIOA->CFGHR &= 0xF<<28;
    GPIOA->CFGHR |= 0x3<<28;
  };
  
  export void turnOn()
  {
    GPIOA->BCR = 1 << 15;
  };

  export void turnOff()
  {
    GPIOA->BSHR = 1 << 15;
  };

};