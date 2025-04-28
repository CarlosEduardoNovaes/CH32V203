module;
#include <cstdint>
#include <type_traits>

export module bitfield;

export template<
    class           TP_RegType,
    TP_RegType*     TP_Addr // for testing fake registers
    //uintptr_t       TP_Addr, // for real use
>
class RegisterOperation
{
    private:
    template<
        class           TPF_RegType,
        TP_RegType*     TPF_Addr, // for testing fake registers
        //uintptr_t       TPF_Addr, // for real use
        int8_t          TPF_Offset,
        int8_t          TPF_Size,
        class           TPF_FieldType
    >
    friend class BitView;
    
    TP_RegType          m_value;
    TP_RegType          m_mask;
    public:

    // should be private but befriending with BitView does not seen to work
    RegisterOperation(TP_RegType value, TP_RegType mask):
    m_value(value),
    m_mask(mask)
    {};
    

    inline static constexpr volatile TP_RegType& m_reg()
    {
        return *reinterpret_cast<volatile TP_RegType*>(TP_Addr);
    };

    public:
    RegisterOperation() = delete;
    RegisterOperation(const RegisterOperation&) = default;
    RegisterOperation& operator=(const RegisterOperation&) = default;

    inline void apply() const
    {
        m_reg() = (m_reg() & ~m_mask) | m_value;
    };

    inline TP_RegType read() const
    {
        return m_reg();
    };

    inline void clearMaskBits() const {
        m_reg() &= ~m_mask;
    };

    inline void setMaskBits() const {
        m_reg() |= m_mask;
    };

    
    constexpr RegisterOperation operator|(const RegisterOperation& other) const {
        return RegisterOperation{(m_value | other.m_value), (m_mask | other.m_mask)};
    };
    
};

export template<
    class           TP_RegType,
    TP_RegType*     TP_Addr, // for testing fake registers
    //uintptr_t       TP_Addr, // for real use
    int8_t          TP_Offset,
    int8_t          TP_Size,
    class           TP_FieldType = TP_RegType
>
class BitView
{
    private:
    static_assert(std::is_integral_v<TP_RegType>, "RegType must be integral");
    static_assert(
        std::is_integral_v<TP_FieldType> || std::is_enum_v<TP_FieldType>,
        "FieldType must be integral or enum with integral base"
    );

    static constexpr TP_RegType c_val_mask = ((1u << TP_Size) - 1);
    static constexpr TP_RegType c_reg_mask = c_val_mask << TP_Offset;

    public:
    [[nodiscard]]
    constexpr RegisterOperation<TP_RegType, TP_Addr> prepare(TP_RegType value=0) const {
        return RegisterOperation<TP_RegType, TP_Addr>((value<<TP_Offset), (c_reg_mask));
    };

    constexpr TP_RegType get() const {
        return (prepare().read() >> TP_Offset) & c_val_mask;        
    };
    
    // Set the value of the field in the register
    constexpr void set(TP_RegType value) const {
        prepare(value).apply();
    };

    inline BitView& operator=(TP_FieldType value) { set(value); return *this; }
    inline operator TP_FieldType() const { return get(); }

    inline bool operator==(TP_FieldType value) const { return get() == value; }
    inline bool operator!=(TP_FieldType value) const { return !(*this == value); }

};


export template<
    typename TP_RegType,
    TP_RegType* TP_Addr,
    int8_t TP_Offset,
    int8_t TP_Size,
    typename TP_FieldType = TP_RegType
>
class BitField {
    static_assert(std::is_integral_v<TP_RegType>, "RegType must be integral");
    static_assert(
        std::is_integral_v<TP_FieldType> || std::is_enum_v<TP_FieldType>,
        "FieldType must be integral or enum with integral base"
    );

    static constexpr TP_RegType val_mask = ((1u << TP_Size) - 1);
    static constexpr TP_RegType reg_mask = val_mask << TP_Offset;

    static volatile TP_RegType& reg() {
        return *reinterpret_cast<volatile TP_RegType*>(TP_Addr);
    }

public:
    BitField() = default;

    void set(TP_FieldType value) {
        auto raw = static_cast<TP_RegType>(value);
        reg() = (reg() & ~reg_mask) | ((raw & val_mask) << TP_Offset);
    }

    TP_FieldType get() const {
        return static_cast<TP_FieldType>((reg() >> TP_Offset) & val_mask);
    }

    BitField& operator=(TP_FieldType value) { set(value); return *this; }
    operator TP_FieldType() const { return get(); }

    bool operator==(TP_FieldType value) const { return get() == value; }
    bool operator!=(TP_FieldType value) const { return !(*this == value); }
};

// Specialized aliases
export template<
    uint32_t* TP_Addr,
    int8_t TP_Offset,
    int8_t TP_Size,
    typename TP_FieldType = uint32_t
>
using BitField32 = BitField<uint32_t, TP_Addr, TP_Offset, TP_Size, TP_FieldType>;

export template<
    uint16_t* TP_Addr,
    int8_t TP_Offset,
    int8_t TP_Size,
    typename TP_FieldType = uint16_t
>
using BitField16 = BitField<uint16_t, TP_Addr, TP_Offset, TP_Size, TP_FieldType>;

export template<
    uint8_t* TP_Addr,
    int8_t TP_Offset,
    int8_t TP_Size,
    typename TP_FieldType = uint8_t
>
using BitField8 = BitField<uint8_t, TP_Addr, TP_Offset, TP_Size, TP_FieldType>;


// Specialized aliases
export template<
    uint32_t*     TP_Addr, // for testing fake registers
    //uintptr_t       TP_Addr, // for real use
    int8_t          TP_Offset,
    int8_t          TP_Size,
    class           TP_FieldType = uint32_t
>
using BitView32 = BitView<uint32_t, TP_Addr, TP_Offset, TP_Size, TP_FieldType>;

export template<
    uint16_t*     TP_Addr, // for testing fake registers
    //uintptr_t       TP_Addr, // for real use
    int8_t          TP_Offset,
    int8_t          TP_Size,
    class           TP_FieldType = uint16_t
>
using BitView16 = BitView<uint16_t, TP_Addr, TP_Offset, TP_Size, TP_FieldType>;

export template<
    uint8_t*     TP_Addr, // for testing fake registers
    //uintptr_t       TP_Addr, // for real use
    int8_t          TP_Offset,
    int8_t          TP_Size,
    class           TP_FieldType = uint8_t
>
using BitView8 = BitField<uint8_t, TP_Addr, TP_Offset, TP_Size, TP_FieldType>;