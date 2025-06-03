module;

#include <stdint.h>
import bare; // for is_integral and is_enum


/**
 * @brief Export the bitfield module
 * 
 */
export module registers;


export 
/**
 * @brief Implement operations on registers
 * 
 * @tparam TP_RegType the type of the register, e.g. uint32_t
 * @tparam TP_Addr the address of the register, e.g. 0x40000000
 * @tparam use 
 */
template<
    class           TP_RegType,
    // TP_RegType*     TP_Addr 
    uintptr_t       TP_Addr  // for real use
>
class RegisterOperation
{
    private:
    /**
     * @brief RegisterOperation has a private constructor, and BitView
     *        is a friend class. This allows BitView to create instances
     *        of RegisterOperation, but prevents other classes from doing so.
    */
    template<
        class           TPF_RegType,
        //TPF_RegType*     TPF_Addr, // for testing fake registers
        uintptr_t       TPF_Addr, // for real use
        int8_t          TPF_Offset,
        int8_t          TPF_Size,
        class           TPF_FieldType
    >
    friend class BitView;
    
    TP_RegType          m_value; // value to set
    TP_RegType          m_mask; // mask to clear

    /**
     * @brief Construct a new Register Operation object
     * 
     * @param value Value to set on the register
     * @param mask  Mask to clear
     */
    inline __attribute__((always_inline))
    constexpr RegisterOperation(TP_RegType value, TP_RegType mask):
    m_value(value),
    m_mask(mask)
    {};

    // public:     

    /**
     * @brief returns the register address as a reference
     * 
     * @return constexpr volatile& 
     */
    inline __attribute__((always_inline))
    static constexpr volatile TP_RegType& m_reg()
    {
        return *reinterpret_cast<volatile TP_RegType*>(TP_Addr);
    };

    public:
    /**
     * @brief Deleted default constructor
     * 
     */
    RegisterOperation() = delete;
    /**
     * @brief Default copy constructor
     * 
     */
    RegisterOperation(const RegisterOperation&) = default;
    /**
     * @brief Default assignment operator
     * 
     * @return RegisterOperation& 
     */
    RegisterOperation& operator=(const RegisterOperation&) = default;

    /**
     * @brief Apply the operation to the register
     * 
     */
    inline __attribute__((always_inline))
    void apply() const
    {
        m_reg() = (m_reg() & ~m_mask) | m_value;
    };

    /**
     * @brief Read the register value
     * 
     * @return TP_RegType 
     */
    inline __attribute__((always_inline))
    TP_RegType read() const
    {
        return m_reg();
    };

    /**
     * @brief Clear the mask bits in the register
     * 
     */
    inline __attribute__((always_inline))
    void clearMaskBits() const {
        m_reg() &= ~m_mask;
    };

    /**
     * @brief Set the mask bits in the register
     * 
     * 
     */
    inline __attribute__((always_inline))    
    void setMaskBits() const {
        m_reg() |= m_mask;
    };

    
    /**
     * @brief Chain the operations together
     * 
     * @param other 
     * @return constexpr RegisterOperation 
     */
    inline __attribute__((always_inline))    
    constexpr RegisterOperation operator|(const RegisterOperation& other) const {
        return RegisterOperation{(m_value | other.m_value), (m_mask | other.m_mask)};
    };
    
};


export
/**
 * @brief BitView class to manipulate bits in a register
 * 
 * @tparam TP_RegType the type of the register, e.g. uint32_t
 * @tparam TP_Addr the address of the register, e.g. 0x40000000
 * @tparam TP_Offset the offset of the field in the register
 * @tparam TP_Size the size of the field in bits
 * @tparam TP_FieldType the type of the field, e.g. uint32_t
 */
template<
    class           TP_RegType,
    //TP_RegType*     TP_Addr, // for testing fake registers
    uintptr_t       TP_Addr, // for real use
    int8_t          TP_Offset,
    int8_t          TP_Size,
    class           TP_FieldType = TP_RegType
>
class BitView
{
    private:
    /**
     * @brief static assertions to check the types of the template parameters
     * 
     */
    static_assert(bare::is_integral_v<TP_RegType>, "RegType must be integral");
    static_assert(
        bare::is_integral_v<TP_FieldType> || bare::is_enum_v<TP_FieldType>,
        "FieldType must be integral or enum with integral base"
    );

    
    static constexpr TP_RegType c_val_mask = ((1u << TP_Size) - 1); // mask for the field value
    static constexpr TP_RegType c_reg_mask = c_val_mask << TP_Offset; // mask for the register memory

    public:
    /**
     * @brief Return a RegisterOperation object to manipulate the register
     * 
     * @param value The value to set in the register
     * @return constexpr RegisterOperation<TP_RegType, TP_Addr> 
     */
    [[nodiscard]]
    constexpr RegisterOperation<TP_RegType, TP_Addr> prepare(TP_RegType value=0) const {
        return RegisterOperation<TP_RegType, TP_Addr>((value<<TP_Offset), (c_reg_mask));
    };

    /**
     * @brief Extract value from the register
     * 
     * @return constexpr TP_RegType 
     */
    constexpr TP_RegType get() const {
        return (prepare().read() >> TP_Offset) & c_val_mask;        
    };
    
    /**
     * @brief Set the value in the register
     * 
     * @param value The value to set in the register
     */
    constexpr void set(TP_RegType value) const {
        prepare(value).apply();
    };

    /**
     * @brief Assign the value to the register
     * 
     * @param value The value to set in the register
     * @return BitView& 
     */
    inline BitView& operator=(TP_FieldType value)
    {
        set(value);
        return *this;
    }


    /**
     * @brief 
     * 
     * @param value 
     * @return constexpr RegisterOperation<TP_RegType, TP_Addr> 
     */
    [[nodiscard]]
    constexpr RegisterOperation<TP_RegType, TP_Addr> operator() (TP_FieldType value)
    {
        return prepare(value);
    };

    /**
     * @brief Compare the value of the field with the given value
     * 
     * @param value 
     * @return true 
     * @return false 
     */
    inline bool operator==(TP_FieldType value) const { return get() == value; }

    /**
     * @brief Compare the value of the field with the given value
     * 
     * @param value 
     * @return true 
     * @return false 
     */
    inline bool operator!=(TP_FieldType value) const { return !(*this == value); }

};


// Specialized aliases
export template<
    //uint32_t*     TP_Addr, // for testing fake registers
    uintptr_t       TP_Addr, // for real use
    int8_t          TP_Offset,
    int8_t          TP_Size,
    class           TP_FieldType = uint32_t
>
using BitView32 = BitView<uint32_t, TP_Addr, TP_Offset, TP_Size, TP_FieldType>;

export template<
    //uint16_t*     TP_Addr, // for testing fake registers
    uintptr_t       TP_Addr, // for real use
    int8_t          TP_Offset,
    int8_t          TP_Size,
    class           TP_FieldType = uint16_t
>
using BitView16 = BitView<uint16_t, TP_Addr, TP_Offset, TP_Size, TP_FieldType>;

export template<
    //uint8_t*     TP_Addr, // for testing fake registers
    uintptr_t       TP_Addr, // for real use
    int8_t          TP_Offset,
    int8_t          TP_Size,
    class           TP_FieldType = uint8_t
>
using BitView8 = BitView<uint8_t, TP_Addr, TP_Offset, TP_Size, TP_FieldType>;