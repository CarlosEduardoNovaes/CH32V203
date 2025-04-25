module;
#include <cstdint>
export module bitfield;





export template<volatile uint32_t* TP_Addr, int8_t offset, int8_t size>
class BitField
{
public:
    constexpr static uint32_t val_mask = ((1 << size) - 1);
    constexpr static uint32_t reg_mask = val_mask << offset;

    // Constructor
    BitField() = default;

    // Destructor
    ~BitField() = default;

    // Set the value of the bit field
    void set(uint32_t value)
    {
        *TP_Addr = (*TP_Addr & ~reg_mask) | ((value & val_mask) << offset);
    }

    // Get the value of the bit field
    uint32_t get() const
    {
        return (*TP_Addr >> offset) & val_mask;
    }
};