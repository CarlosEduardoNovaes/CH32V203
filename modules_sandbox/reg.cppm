module;
#include <cstdint>


import bitfield;

export module reg;

export template<volatile uint32_t* TP_Addr>
class Register{
public:
    // Constructor
    Register() = default;

    // Destructor
    ~Register() = default;

    BitField<TP_Addr, 0, 4> field0;
    BitField<TP_Addr, 4, 4> field1;
    BitField<TP_Addr, 8, 1> field2;
};