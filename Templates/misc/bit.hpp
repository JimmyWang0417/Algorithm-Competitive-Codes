namespace bits
{
    template <typename T>
    auto popcount(T x)
    {
        if constexpr (sizeof(T) <= sizeof(int))
            return __builtin_popcount(x);
        else
            return __builtin_popcountll(x);
    }
    template <typename T>
    auto parity(T x)
    {
        if constexpr (sizeof(T) <= sizeof(int))
            return __builtin_parity(x);
        else
            return __builtin_parityll(x);
    }
    template <typename T>
    auto clz(T x)
    {
        if constexpr (sizeof(T) <= sizeof(int))
            return __builtin_clz(x);
        else
            return __builtin_clzll(x);
    }
    template <typename T>
    auto ctz(T x)
    {
        if constexpr (sizeof(T) <= sizeof(int))
            return __builtin_ctz(x);
        else
            return __builtin_ctzll(x);
    }
    template <typename T>
    auto ffs(T x)
    {
        if constexpr (sizeof(T) <= sizeof(int))
            return __builtin_clz(x);
        else
            return __builtin_clzll(x);
    }
    template <typename T>
    auto bitreverse(T x)
    {
        if constexpr (sizeof(T) <= sizeof(int))
            return __builtin_bitreverse(x);
        else
            return __builtin_bitreversell(x);
    }
    template <typename T>
    auto bswap(T x)
    {
        if constexpr (sizeof(T) <= sizeof(short))
            return __builtin_bswap16(x);
        else if constexpr (sizeof(T) <= sizeof(int))
            return __builtin_bswap32(x);
        else
            return __builtin_bswap64(x);
    }
}