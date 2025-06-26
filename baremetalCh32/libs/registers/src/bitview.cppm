module;


import bare; // for is_integral and is_enum


/**
 * @brief Export the bitfield module
 * 
 */
export module registers;

export
/**
 * @brief Implement Register Snapshot
 * @details This class wrap the primitive type TP_RegType
 * 
 * @tparam TP_RegType A primitive type
 * @tparam TP_Addr Register Address 
 */
template<
    class               TP_RegType,
    bare::uintptr_t     TP_Addr
>
class Snapshot
{
    public:
    Snapshot(TP_RegType v) {value = v;};
    TP_RegType value;
};

export
/**
 * @brief Implement RegisterAccessor class
 * @details This class provides access to the hardware register and is base for Register and RegisterOperation classes
 * 
 * @tparam TP_RegType 
 * @tparam TP_Addr 
 */
template<
    class               TP_RegType,
    bare::uintptr_t     TP_Addr
>
class RegisterAccessor
{
    public:    
    inline __attribute__((always_inline))
    static constexpr Snapshot<TP_RegType, TP_Addr> getSnapshot()
    {
        return Snapshot<TP_RegType, TP_Addr>(getReference());
    };
    protected:
    inline __attribute__((always_inline))
    static constexpr volatile TP_RegType& getReference()
    {
        return *reinterpret_cast<volatile TP_RegType*>(TP_Addr);
    };
};

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
class RegisterOperation : public RegisterAccessor<TP_RegType, TP_Addr>
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
        class               TPF_FieldType
    >
    friend class BitView;
    
    TP_RegType              m_value; // value to set
    TP_RegType              m_mask; // mask to clear

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
        //RegisterOperation::getReference() = (RegisterOperation::getReference() & ~m_mask) | m_value;
        RegisterOperation::getReference() = (RegisterOperation::getReference() & ~m_mask) | m_value;
    };

    /**
     * @brief Read the register value
     * @return TP_RegType 
     */
    inline __attribute__((always_inline))
    static constexpr TP_RegType read()
    {
        return RegisterOperation::getSnapshot().value;
    };


    /**
     * @brief Clear the mask bits in the register
     */
    inline __attribute__((always_inline))
    void clearMaskBits() const {
        RegisterOperation::getReference() &= ~m_mask;
    };

    /**
     * @brief Set the mask bits in the register
     */
    inline __attribute__((always_inline))    
    void setMaskBits() const {
        RegisterOperation::getReference() |= m_mask;
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
    class                   TP_FieldType = TP_RegType
>
class BitView
{
    private:
    static constexpr TP_RegType c_val_mask = ((1u << TP_Size) - 1); // mask for the field value
    

    template <typename... Args>
    BitView(Args...) = delete; // Deletes all constructors
    
    public:
    inline __attribute__((always_inline)) [[nodiscard]]
    static constexpr RegisterOperation<TP_RegType, TP_Addr>
    prepare(TP_RegType value=0) {
        return RegisterOperation<TP_RegType, TP_Addr>(
            (value<<TP_Offset),
            (c_val_mask<<TP_Offset)
            );
    };
    
    inline __attribute__((always_inline))
    static constexpr
    TP_FieldType read() {
        //return (prepare().read() >> TP_Offset ) & c_val_mask;
        return readFromSnapshot(prepare().getSnapshot());
    };

    inline __attribute__((always_inline))
    static constexpr
    TP_FieldType readFromSnapshot(Snapshot<TP_RegType, TP_Addr> snap) {
        return (snap.value >> TP_Offset) & c_val_mask;
    };

    //Snapshot<TP_RegType, TP_Addr>

    inline __attribute__((always_inline))
    static constexpr
    TP_RegType readSnapshot() {
        return (prepare().read() >> TP_Offset) & c_val_mask;        
    };


    inline __attribute__((always_inline))
    static constexpr
    void write(TP_RegType v)
    {
        prepare(v).apply();
    };

};


// Specialized aliases
export template<
    bare::uintptr_t         TP_Addr,
    bare::uint8_t           TP_Offset,
    bare::uint8_t           TP_Size,
    class                   TP_FieldType = bare::uint32_t
>
using BitView32 = BitView<bare::uint32_t, TP_Addr, TP_Offset, TP_Size, TP_FieldType>;

export template<
    bare::uintptr_t         TP_Addr,
    bare::uint8_t           TP_Offset,
    bare::uint8_t           TP_Size,
    class                   TP_FieldType = bare::uint16_t
>
using BitView16 = BitView<bare::uint16_t, TP_Addr, TP_Offset, TP_Size, TP_FieldType>;

export template<
    bare::uintptr_t         TP_Addr,
    bare::uint8_t           TP_Offset,
    bare::uint8_t           TP_Size,
    class                   TP_FieldType = bare::uint8_t
>
using BitView8 = BitView<bare::uint8_t, TP_Addr, TP_Offset, TP_Size, TP_FieldType>;