namespace fft
{
    // FFT/IFFT 前先 init(n)，并将序列扩至 limit。
    // 整数卷积：令 N=bit_ceil(n+m-1)，E=sum(a[i]^2)+sum(b[i]^2)。
    // E*log2(N)<9e14 时可安全取整；否则改用拆系数 FFT 或多模 NTT+CRT。
    // 还需保证结果不溢出 i64；非负序列可用 sum(x[i]^2)<=max(x)*sum(x) 估计 E。
    inline vector<int> rk;
    inline int len, limit;
    auto init(int n)
    {
        len = 0, limit = 1;
        while (limit < n)
        {
            ++len;
            limit <<= 1;
        }
        rk.resize(limit);
        rk[0] = 0;
        for (int i = 1; i < limit; ++i)
            rk[i] = (rk[i >> 1] >> 1) | ((i & 1) << (len - 1));
    }
    auto FFT(vector<complex<double>> &dp)
    {
        for (int i = 0; i < limit; ++i)
            if (i < rk[i])
                swap(dp[i], dp[rk[i]]);
        for (int mid = 1; mid < limit; mid <<= 1)
        {
            const auto gn = polar(1.0, numbers::pi / mid);
            for (int i = 0; i < limit; i += mid << 1)
            {
                complex<double> g(1, 0);
                for (int j = 0; j < mid; ++j, g *= gn)
                {
                    auto x = dp[i + j], y = dp[i + j + mid] * g;
                    dp[i + j] = x + y;
                    dp[i + j + mid] = x - y;
                }
            }
        }
    }
    auto IFFT(vector<complex<double>> &dp)
    {
        for (int i = 0; i < limit; ++i)
            if (i < rk[i])
                swap(dp[i], dp[rk[i]]);
        for (int mid = 1; mid < limit; mid <<= 1)
        {
            const auto gn = polar(1.0, -numbers::pi / mid);
            for (int i = 0; i < limit; i += mid << 1)
            {
                complex<double> g(1, 0);
                for (int j = 0; j < mid; ++j, g *= gn)
                {
                    auto x = dp[i + j], y = dp[i + j + mid] * g;
                    dp[i + j] = (x + y) / 2.0;
                    dp[i + j + mid] = (x - y) / 2.0;
                }
            }
        }
    }
    auto multiply(const vector<i64> &lhs, const vector<i64> &rhs)
    {
        if (lhs.empty() || rhs.empty())
            return vector<i64>{};
        auto up = lhs.size() + rhs.size() - 1;
        init(up);
        vector<complex<double>> x(lhs.begin(), lhs.end()), y(rhs.begin(), rhs.end());
        x.resize(limit), y.resize(limit);
        FFT(x), FFT(y);
        for (int i = 0; i < limit; ++i)
            x[i] *= y[i];
        IFFT(x);
        vector<i64> res(up);
        for (int i = 0; i < up; ++i)
            res[i] = (i64)round(x[i].real());
        return res;
    }
}
