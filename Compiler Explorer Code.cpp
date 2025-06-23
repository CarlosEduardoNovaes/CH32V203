#include <cstdint>

template<
    class           TP_RegType,
    uintptr_t       TP_Addr
>
class Snapshot
{
    public:
    Snapshot(TP_RegType v) {value = v;};
    TP_RegType value;
};

template<
    class           TP_RegType,
    uintptr_t       TP_Addr
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

template<
    class           TP_RegType,
    uintptr_t       TP_Addr
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
        class           TPF_RegType,
        uintptr_t       TPF_Addr,
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
    // inline __attribute__((always_inline))
    // static constexpr TP_RegType read()
    // {
    //     return RegisterOperation::getSnapshot().value;
    // };


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


template<
    class               TP_RegType,
    uintptr_t           TP_Addr,
    int8_t              TP_Offset,
    int8_t              TP_Size,
    class               TP_FieldType = TP_RegType
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


template<
    class           TP_RegType,
    uintptr_t       TP_Addr
>
class MyRegTmpl : public RegisterAccessor<TP_RegType, TP_Addr>
{
    public:
    using field1 = BitView<uint32_t, TP_Addr, 0, 1, bool>;
    using field2 = BitView<uint32_t, TP_Addr, 1, 1, bool>;
    using field3 = BitView<uint32_t, TP_Addr, 2, 1, bool>;
};

template<
    class           TP_RegType,
    uintptr_t       TP_Addr
>
class MyRegTmplTwo : public RegisterAccessor<TP_RegType, TP_Addr>
{
    public:
    using field1 = BitView<uint32_t, TP_Addr, 0, 2, uint8_t>;
    using field2 = BitView<uint32_t, TP_Addr, 1, 2, uint8_t>;
};

using MyReg = MyRegTmpl<uint32_t, 40010020>;
using MyRegTwo = MyRegTmplTwo<uint32_t, 40010020>;

using myreg = BitView<uint32_t, 40010020, 0, 1, bool>;
using myreg1 = BitView<uint32_t, 40010020, 1, 1, bool>;
volatile bool b1 = true;
volatile bool b2 = true;
volatile bool b3 = true;
volatile uint8_t flag = 0;


int main()
{
    // 27 extra lines on -O0 x86-64, 36 on riscv
    // 17 extra line on -O1 x86-64, 17 on riscv
    // 15 extra line on -O2 x86-64, 17 on riscv
    // *( (volatile uint32_t*)(40010020) ) &= ~(0x1);
    // *( (volatile uint32_t*)(40010020) ) |= (b1 << 0);
    // *( (volatile uint32_t*)(40010020) ) &= ~(0x2);
    // *( (volatile uint32_t*)(40010020) ) |= (b1 << 1);

    // 53 extra lines on -O0 x86-64, 81 on riscv
    // 13 extra line on -O1 x86-64, 13 on riscv
    // 11 extra line on -O2 x86-64, 13 on riscv
    // myreg::write(b1);
    // myreg1::write(b1);




    // 17 extra lines on -O0 x86-64, 23 on riscv
    // 12 extra line on -O1 x86-64, 12 on riscv
    // 10 extra line on -O2 x86-64, 12 on riscv
    // *( (volatile uint32_t*)(40010020) ) &= ~(0x3);
    // *( (volatile uint32_t*)(40010020) ) |= ( (b1 << 0) | (b2 << 1) );



    // 52 extra lines on -O0 x86-64, 88 on riscv
    // 10 extra line on -O1 x86-64, 10 on riscv
    // 8 extra line on -O2 x86-64, 10 on riscv
    // (
    //     myreg::prepare(b1) | myreg1::prepare(b2)
    // ).apply();
    // (
    //     MyReg::field1::prepare(b1) | MyReg::field2::prepare(b2)
    // ).apply();

    // b1 = MyReg::field1::read();
    // b2 = MyReg::field2::read();
    //b3 = MyReg::field3::read();
    
    auto snap = MyReg::getSnapshot();
    b1 = MyReg::field1::readFromSnapshot(snap);
    b2 = MyReg::field2::readFromSnapshot(snap);
    // b3 = MyReg::field3::readFromSnapshot(snap);
    //MyReg::field1::write(b1);
    
    
    // 5 extra lines on -O0 x86-64, 7 on riscv
    // 1 extra line on -O1 x86-64, 3 on riscv
    //myreg r;
    //r.set(10);

    // static constexpr auto setup1 = myreg::prepare(true) | myreg1::prepare(true);
    // setup1.apply();

    return 0;

};