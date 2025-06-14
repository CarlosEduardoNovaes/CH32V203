module;

export module bare:traits;
export namespace bare
{
    // is_integral<T>
    export template<typename T> struct is_integral       { static constexpr bool value = false; };
    export template<> struct is_integral<bool>           { static constexpr bool value = true; };
    export template<> struct is_integral<char>           { static constexpr bool value = true; };
    export template<> struct is_integral<signed char>    { static constexpr bool value = true; };
    export template<> struct is_integral<unsigned char>  { static constexpr bool value = true; };
    export template<> struct is_integral<short>          { static constexpr bool value = true; };
    export template<> struct is_integral<unsigned short> { static constexpr bool value = true; };
    export template<> struct is_integral<int>            { static constexpr bool value = true; };
    export template<> struct is_integral<unsigned int>   { static constexpr bool value = true; };
    export template<> struct is_integral<long>           { static constexpr bool value = true; };
    export template<> struct is_integral<unsigned long>  { static constexpr bool value = true; };
    export template<> struct is_integral<long long>      { static constexpr bool value = true; };
    export template<> struct is_integral<unsigned long long> { static constexpr bool value = true; };

    export template<typename T>
    constexpr bool is_integral_v = is_integral<T>::value;

    // is_enum<T>
    export template<typename T>
    struct is_enum {
    private:
        template<typename U>
        static constexpr bool test(int) {
            return !is_integral_v<U> && !__is_class(U) && !__is_union(U);
        };

        template<typename>
        static constexpr bool test(...) { return false; }

    public:
        static constexpr bool value = test<T>(0);
    };

    export template<typename T>
    constexpr bool is_enum_v = is_enum<T>::value;

};





