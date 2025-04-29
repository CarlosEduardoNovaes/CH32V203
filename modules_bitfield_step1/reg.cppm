module;
#include <cstdint>


export import bitfield;

export module reg;

export template<uint32_t* TP_Addr>
class Register{
public:
    // Constructor
    Register() = default;

    // Destructor
    ~Register() = default;

    BitView32<TP_Addr, 0, 4> field0;
    BitView32<TP_Addr, 4, 4> field1;
    BitView32<TP_Addr, 8, 4> field2;
    BitView32<TP_Addr, 12, 1> status;
};