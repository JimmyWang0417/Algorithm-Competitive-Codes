template <typename T, typename Cmp>
struct sparse
{
    Cmp cmp;
    vector<vector<T>> dp;
    sparse() = default;
    sparse(const vector<T> &a, const Cmp &_cmp = Cmp())
        : cmp(_cmp), dp(__lg(max((int)a.size(), 1)) + 1, a)
    {
        for (int j = 0; j + 1 < (int)dp.size(); ++j)
            for (int i = 0; i + (2 << j) - 1 < (int)a.size(); ++i)
                dp[j + 1][i] = min(dp[j][i], dp[j][i + (1 << j)], cmp);
    }
    auto query(int l, int r) const
    {
        int k = __lg(r - l + 1);
        return min(dp[k][l], dp[k][r - (1 << k) + 1], cmp);
    }
};
