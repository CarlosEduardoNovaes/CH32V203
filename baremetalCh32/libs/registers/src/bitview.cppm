module;


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
 * @tparam TP_RegType the type of the register, e.g. bare::uint32_t
 * @tparam TP_Addr the address of the register, e.g. 0x40000000
 * @tparam use 
 */
template<
    class                   TP_RegType,
    bare::uintptr_t         TP_Addr
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
        class               TPF_RegType,
        bare::uintptr_t     TPF_Addr, 
        bare::uint8_t       TPF_Offset,
        bare::uint8_t       TPF_Size,
        class               TPF_FieldType,
        bare::uint16_t      TPF_ArraySize,
        bare::uint16_t      TPF_ArrayNullBits,
        bare::uint8_t       TPF_ByteAlign
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
 * @tparam TP_RegType the type of the register, e.g. bare::uint32_t
 * @tparam TP_Addr the address of the register, e.g. 0x40000000
 * @tparam TP_Offset the offset of the field in the register
 * @tparam TP_Size the size of the field in bits
 * @tparam TP_FieldType the type of the field, e.g. bare::uint32_t
 */
template<
    class                   TP_RegType,
    bare::uintptr_t         TP_Addr, // for real use
    bare::uint8_t           TP_Offset,
    bare::uint8_t           TP_Size,
    class                   TP_FieldType = TP_RegType,
    bare::uint16_t          TP_ArraySize = 1,
    bare::uint16_t          TP_ArrayNullBits = 0,
    bare::uint8_t           TP_ByteAlign = 4
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

    template <typename... Args>
    BitView(Args...) = delete; // Deletes all constructors

    public:
    /**
     * @brief Return a RegisterOperation object to manipulate the register
     * 
     * @param value The value to set in the register
     * @return constexpr RegisterOperation<TP_RegType, TP_Addr> 
     */
    static inline __attribute__((always_inline)) [[nodiscard]]
    constexpr RegisterOperation<TP_RegType, TP_Addr> prepare(TP_RegType value=0) {
        return RegisterOperation<TP_RegType, TP_Addr>(
            (value<<TP_Offset),
            (c_val_mask<<TP_Offset)
        );
    };

    template<bare::uint8_t TP_ArrayIndex>
    static inline __attribute__((always_inline)) [[nodiscard]]
    constexpr RegisterOperation<
        TP_RegType,
        TP_Addr + ((TP_Offset+TP_ArrayIndex*(TP_Size+TP_ArrayNullBits)) / (8*TP_ByteAlign))*TP_ByteAlign
        > prepareAt(TP_RegType value=0) {
        static_assert(TP_ArrayIndex<TP_ArraySize, "Cannot index more itens than array size");
        constexpr bare::uint32_t final_bit_offset = (TP_Offset+TP_ArrayIndex*(TP_Size+TP_ArrayNullBits)) % (8*TP_ByteAlign);
        return RegisterOperation<
            TP_RegType,
            TP_Addr + ((TP_Offset+TP_ArrayIndex*(TP_Size+TP_ArrayNullBits)) / (8*TP_ByteAlign))*TP_ByteAlign
            >( 
            ( value << (TP_Offset+final_bit_offset) ),
            ( c_val_mask << (TP_Offset+final_bit_offset) )
            );
    };

    /**
     * @brief read the value from the register
     * 
     * @return TP_RegType 
     */
    static constexpr inline __attribute__((always_inline)) [[nodiscard]]
    TP_RegType read() {
        return (prepare().read() >> TP_Offset) & c_val_mask;        
    };


    template<bare::uint8_t TP_ArrayIndex>
    static constexpr inline __attribute__((always_inline)) [[nodiscard]]
    TP_RegType readAt() {
        return (prepareAt<TP_ArrayIndex>().read() >> (TP_Offset+TP_ArrayIndex*(TP_Size+TP_ArrayNullBits))) & c_val_mask;        
    };
    
    /**
     * @brief Set the value in the register
     * 
     * @param v The value to set in the register
     */
    static constexpr inline __attribute__((always_inline))
    void write(TP_RegType v)
    {
        prepare(v).apply();
    };


    template<bare::uint8_t TP_ArrayIndex>
    static constexpr inline __attribute__((always_inline))
    void writeAt(TP_RegType v)
    {
        prepareAt<TP_ArrayIndex>(v).apply();
    };

};


// Specialized aliases
export template<
    bare::uintptr_t         TP_Addr, // for real use
    bare::uint8_t           TP_Offset,
    bare::uint8_t           TP_Size,
    class                   TP_FieldType = bare::uint32_t,
    bare::uint16_t          TP_ArraySize = 1,
    bare::uint16_t          TP_ArrayNullBits = 0,
    bare::uint8_t           TP_ByteAlign = 4
>
using BitView32 = BitView<bare::uint32_t, TP_Addr, TP_Offset, TP_Size, TP_FieldType, TP_ArraySize, TP_ArrayNullBits, TP_ByteAlign>;

export template<
    bare::uintptr_t         TP_Addr, // for real use
    bare::uint8_t           TP_Offset,
    bare::uint8_t           TP_Size,
    class                   TP_FieldType = bare::uint16_t,
    bare::uint16_t          TP_ArraySize = 1,
    bare::uint16_t          TP_ArrayNullBits = 0,
    bare::uint8_t           TP_ByteAlign = 4
>
using BitView16 = BitView<bare::uint16_t, TP_Addr, TP_Offset, TP_Size, TP_FieldType, TP_ArraySize, TP_ArrayNullBits, TP_ByteAlign>;

export template<
    bare::uintptr_t         TP_Addr, // for real use
    bare::uint8_t           TP_Offset,
    bare::uint8_t           TP_Size,
    class                   TP_FieldType = bare::uint8_t,
    bare::uint16_t          TP_ArraySize = 1,
    bare::uint16_t          TP_ArrayNullBits = 0,
    bare::uint8_t           TP_ByteAlign = 4
>
using BitView8 = BitView<bare::uint8_t, TP_Addr, TP_Offset, TP_Size, TP_FieldType, TP_ArraySize, TP_ArrayNullBits, TP_ByteAlign>;