template <typename T = i64>
struct DuSieve
{
    const sieve<T> &s;
    T invG;
    unordered_map<i64, T> mp;
    function<T(i64)> sumG, sumFG;
    template <typename F, typename G>
    DuSieve(const sieve<T> &_s, T _invG, F _sumG, G _sumFG)
        : s(_s), invG(_invG), sumG(_sumG), sumFG(_sumFG) {}
    auto solve(i64 n) -> T
    {
        if (n <= 0)
            return 0;
        if (n < (i64)s.pre.size())
            return s.pre[n];
        if (auto it = mp.find(n); it != mp.end())
            return it->second;
        T res = sumFG(n);
        for (i64 l = 2, r; l <= n; l = r + 1)
        {
            r = n / (n / l);
            res -= (sumG(r) - sumG(l - 1)) * solve(n / l);
        }
        return mp[n] = res * invG;
    }
};
