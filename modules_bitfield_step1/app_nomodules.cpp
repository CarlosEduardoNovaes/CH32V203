
#include <cstdint>
#include <type_traits>
#include <iostream>


template<
    class           TP_RegType,
    TP_RegType*     TP_Addr // for testing fake registers
    //uintptr_t       TP_Addr, // for real use
>
class RegisterOperation
{
    private:
    template<
        class           TPF_RegType,
        TPF_RegType*     TPF_Addr, // for testing fake registers
        //uintptr_t       TPF_Addr, // for real use
        int8_t          TPF_Offset,
        int8_t          TPF_Size,
        class           TPF_FieldType
    >
    friend class BitView;
    
    TP_RegType          m_value;
    TP_RegType          m_mask;

    //public:
    RegisterOperation(TP_RegType value, TP_RegType mask):
    m_value(value),
    m_mask(mask)
    {};

    public:

    
    

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

template<
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


// Specialized aliases
template<
    uint32_t*     TP_Addr, // for testing fake registers
    //uintptr_t       TP_Addr, // for real use
    int8_t          TP_Offset,
    int8_t          TP_Size,
    class           TP_FieldType = uint32_t
>
using BitView32 = BitView<uint32_t, TP_Addr, TP_Offset, TP_Size, TP_FieldType>;

template<
    uint16_t*     TP_Addr, // for testing fake registers
    //uintptr_t       TP_Addr, // for real use
    int8_t          TP_Offset,
    int8_t          TP_Size,
    class           TP_FieldType = uint16_t
>
using BitView16 = BitView<uint16_t, TP_Addr, TP_Offset, TP_Size, TP_FieldType>;

template<
    uint8_t*     TP_Addr, // for testing fake registers
    //uintptr_t       TP_Addr, // for real use
    int8_t          TP_Offset,
    int8_t          TP_Size,
    class           TP_FieldType = uint8_t
>
using BitView8 = BitView<uint8_t, TP_Addr, TP_Offset, TP_Size, TP_FieldType>;





template<uint32_t* TP_Addr>
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





static uint32_t fake_reg = 1024;

Register<&fake_reg> myreg;

int main() 
{ 
    // calling the add function from the math module 
    //int result = add(3, 5); 
  
    // calling the multiply function from the math module 
    //result = multiply(2, 4);
    //result = scale<int, 4>(result);
    //myreg.field0 = 1;
    //myreg.field0.set(1);
    //myreg.field1.set(2);
    //myreg.status.set(false);
    (
        myreg.field0.prepare(1) | myreg.field1.prepare(2) | myreg.status.prepare(false)
    ).apply();



    std::cout << "result is :" << fake_reg << std::endl;
    std::cout << "field0 :" << myreg.field0.get() << std::endl;
    std::cout << "field1 :" << myreg.field1.get() << std::endl;
    std::cout << "field2 :" << myreg.field2.get() << std::endl;
    std::cout << "status :" << myreg.status.get() << std::endl;
    return 0; 
}