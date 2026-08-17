template <typename T>
struct HashTableBase
{
    constexpr static u64 C = (u64)(2e18 * M_PI) | 71;
    auto operator()(T x) const
    {
        if constexpr (sizeof(T) <= sizeof(int))
            return __builtin_bswap32(x * C);
        else
            return __builtin_bswap64(x * C);
    }
};
template <typename T, typename G>
struct HashTable : public __gnu_pbds::gp_hash_table<T, G, HashTableBase<T>>
{
    using base = __gnu_pbds::gp_hash_table<T, G, HashTableBase<T>>;
    using base::base;
};