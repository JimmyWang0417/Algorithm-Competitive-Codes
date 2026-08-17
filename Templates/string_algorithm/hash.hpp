namespace stringAlgorithm
{
    constexpr int base = 13331;
    template <int mod>
    struct Hash : vector<i64>
    {
        using vector<i64>::vector;
        static inline std::vector<int> power{1};
        static void ensure(int n)
        {
            while ((int)power.size() <= n)
                power.push_back((int)((i64)power.back() * base % mod));
        }
        Hash(const string &s)
        {
            resize(s.size());
            for (int i = 0; i < (int)s.size(); ++i)
                at(i) = ((i ? at(i - 1) : 0) * base + s[i]) % mod;
        }
        auto calc(int l, int r)
        {
            ensure(r - l + 1);
            return (at(r) - (l > 0 ? at(l - 1) * power[r - l + 1] % mod : 0) + mod) % mod;
        }
    };
}
