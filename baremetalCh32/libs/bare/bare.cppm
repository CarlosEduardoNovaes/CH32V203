module;
#include <stdint.h>

export module bare;

export import :traits;

export namespace bare {
    using int8_t   = ::int8_t;
    using int16_t  = ::int16_t;
    using int32_t  = ::int32_t;
    using int64_t  = ::int64_t;

    using uint8_t  = ::uint8_t;
    using uint16_t = ::uint16_t;
    using uint32_t = ::uint32_t;
    using uint64_t = ::uint64_t;

    using intptr_t  = ::intptr_t;
    using uintptr_t = ::uintptr_t;
    int bare_init() noexcept
    {
        return 9;
    };
}