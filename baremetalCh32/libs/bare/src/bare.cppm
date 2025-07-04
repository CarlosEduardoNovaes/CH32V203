module;
#include <stdint.h>

export module bare;

export import :traits;

export namespace bare {
    using int8_t                = ::int8_t;
    using int16_t               = ::int16_t;
    using int32_t               = ::int32_t;
    using int64_t               = ::int64_t;

    using int_fast8_t           = ::int_fast8_t;
    using int_fast16_t          = ::int_fast16_t;
    using int_fast32_t          = ::int_fast32_t;
    using int_fast64_t          = ::int_fast64_t;

    using int_least8_t          = ::int_least8_t;
    using int_least16_t         = ::int_least16_t;
    using int_least32_t         = ::int_least32_t;
    using int_least64_t         = ::int_least64_t;

    using intmax_t              = ::intmax_t;
    using intptr_t              = ::intptr_t;

    using uint8_t               = ::uint8_t;
    using uint16_t              = ::uint16_t;
    using uint32_t              = ::uint32_t;
    using uint64_t              = ::uint64_t;

    using uint_fast8_t          = ::uint_fast8_t;
    using uint_fast16_t         = ::uint_fast16_t;
    using uint_fast32_t         = ::uint_fast32_t;
    using uint_fast64_t         = ::uint_fast64_t;

    using uint_least8_t         = ::uint_least8_t;
    using uint_least16_t        = ::uint_least16_t;
    using uint_least32_t        = ::uint_least32_t;
    using uint_least64_t        = ::uint_least64_t;

    using uintmax_t             = ::uintmax_t;
    using uintptr_t             = ::uintptr_t;
};