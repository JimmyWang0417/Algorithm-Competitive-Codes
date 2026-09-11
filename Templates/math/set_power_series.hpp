template <int mod = 998244353>
struct SetPowerSeries
{
    static auto popcount(int x)
    {
        return __builtin_popcount(x);
    }
    static auto fwt(vector<int> &a)
    {
        for (int mid = 1; mid < (int)a.size(); mid <<= 1)
            for (int i = 0; i < (int)a.size(); i += mid << 1)
                for (int j = 0; j < mid; ++j)
                    a[i + j + mid] = (a[i + j + mid] + a[i + j]) % mod;
    }
    static auto ifwt(vector<int> &a)
    {
        for (int mid = 1; mid < (int)a.size(); mid <<= 1)
            for (int i = 0; i < (int)a.size(); i += mid << 1)
                for (int j = 0; j < mid; ++j)
                    a[i + j + mid] = (a[i + j + mid] - a[i + j]) % mod;
    }
    static auto subsetConv(int n, const vector<int> &a, const vector<int> &b)
    {
        int lim = 1 << n;
        vector<vector<int>> A(n + 1, vector<int>(lim));
        vector<vector<int>> B(n + 1, vector<int>(lim));
        vector<vector<int>> C(n + 1, vector<int>(lim));
        for (int S = 0; S < lim; ++S)
        {
            int cnt = popcount(S);
            A[cnt][S] = a[S] % mod;
            B[cnt][S] = b[S] % mod;
        }
        for (int i = 0; i <= n; ++i)
            fwt(A[i]), fwt(B[i]);
        for (int S = 0; S < lim; ++S)
            for (int i = 0; i <= n; ++i)
                for (int j = 0; i + j <= n; ++j)
                    C[i + j][S] = (int)((C[i + j][S] + (i64)A[i][S] * B[j][S]) % mod);
        for (int i = 0; i <= n; ++i)
            ifwt(C[i]);
        vector<int> res(lim);
        for (int S = 0; S < lim; ++S)
            res[S] = (C[popcount(S)][S] + mod) % mod;
        return res;
    }
    static auto comp(const vector<int> &F, const vector<int> &G)
    {
        if (F.empty())
            return vector<int>{};
        int n = (int)F.size() - 1, lim = 1 << n;
        vector<int> fac(n + 1, 1);
        for (int i = 1; i <= n; ++i)
            fac[i] = (int)((i64)fac[i - 1] * i % mod);
        vector<vector<int>> f(n + 1, vector<int>(lim));
        for (int i = 0; i <= n; ++i)
            f[i][0] = (int)((i64)fac[i] * (F[i] % mod) % mod);
        for (int i = 0; i < n; ++i)
        {
            int m = 1 << (i + 1), half = 1 << i;
            for (int j = n - i - 1; j >= 0; --j)
            {
                vector<vector<int>> A(i + 2, vector<int>(m));
                vector<vector<int>> B(i + 2, vector<int>(m));
                for (int S = 0; S < half; ++S)
                    A[popcount(S)][S] = f[j + 1][S];
                for (int S = half; S < m; ++S)
                    B[popcount(S)][S] = G[S] % mod;
                for (int k = 0; k <= i + 1; ++k)
                    fwt(A[k]), fwt(B[k]);
                for (int S = 0; S < m; ++S)
                {
                    vector<int> C(i + 2);
                    for (int k = 0; k <= i + 1; ++k)
                        for (int l = 0; k + l <= i + 1; ++l)
                            C[k + l] = (int)((C[k + l] + (i64)A[k][S] * B[l][S]) % mod);
                    for (int k = 0; k <= i + 1; ++k)
                        A[k][S] = C[k];
                }
                for (int k = 0; k <= i + 1; ++k)
                    ifwt(A[k]);
                for (int S = half; S < m; ++S)
                    f[j][S] = (f[j][S] + A[popcount(S)][S]) % mod;
            }
        }
        for (auto &x : f[0])
            x = (x + mod) % mod;
        return f[0];
    }
};
