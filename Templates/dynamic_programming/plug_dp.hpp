template <typename T = i64>
struct PlugDP
{
    int n, m, bits;
    unordered_map<u64, T> dp, nxt;
    function<void(T &, T)> merge;
    template <typename F>
    PlugDP(int _n, int _m, int _bits, T start, F _merge)
        : n(_n), m(_m), bits(_bits), merge(_merge)
    {
        dp[0] = start;
    }
    auto insert(u64 state, T value)
    {
        if (auto it = nxt.find(state); it != nxt.end())
            merge(it->second, value);
        else
            nxt[state] = value;
    }
    template <typename F>
    auto solve(F transfer)
    {
        for (int i = 1; i <= n; ++i)
        {
            nxt.clear();
            for (auto [state, value] : dp)
                insert(state << bits, value);
            dp.swap(nxt);
            for (int j = 1; j <= m; ++j)
            {
                nxt.clear();
                for (auto [state, value] : dp)
                    transfer(i, j, state, value, *this);
                dp.swap(nxt);
            }
        }
    }
};
