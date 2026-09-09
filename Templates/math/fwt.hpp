template <typename T, typename F>
auto FWT(vector<T> &dp, F calc)
{
    for (int mid = 1; mid < (int)dp.size(); mid <<= 1)
        for (int i = 0; i < (int)dp.size(); i += mid << 1)
            for (int j = 0; j < mid; ++j)
                calc(dp[i + j], dp[i + j + mid]);
}
