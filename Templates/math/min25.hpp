struct min25
{
    auto calc(i64 n)
    {
        int block = (int)sqrt(n);
        vector<int> prime(1);
        vector<i64> primef(1), primeg(1);
        vector<i64> f, g;
        vector<int> id1(block + 5), id2(block + 5);
        auto sieve = [&](int m)
        {
            vector<bool> vis(m + 5);
            for (int i = 2; i <= m; ++i)
            {
                if (!vis[i])
                {
                    prime.push_back(i);
                    primef.push_back((primef.back() + i) % mod);
                    primeg.push_back((primeg.back() + (i64)i * i) % mod);
                }
                for (int j = 1; j < (int)prime.size(); ++j)
                {
                    if (i * prime[j] > m)
                        break;
                    vis[i * prime[j]] = true;
                    if (i % prime[j] == 0)
                        break;
                }
            }
        };
        function<i64(i64, int)> solve = [&](i64 x, int y) -> i64
        {
            if (x <= prime[y])
                return 0;
            int k = (x <= block ? id1[x] : id2[n / x]);
            i64 ans = ((g[k] - f[k]) - (primeg[y] - primef[y])) % mod;
            for (int i = y + 1; i < (int)prime.size() && (i64)prime[i] * prime[i] <= x; ++i)
                for (i64 pe = prime[i]; pe <= x; pe *= prime[i])
                    (ans += (pe % mod) * ((pe - 1) % mod) % mod * (solve(x / pe, i) + (pe != prime[i]))) %= mod;
            return ans;
        };
        vector<i64> p;
        sieve(block);
        for (i64 i = 1, j; i <= n; i = j + 1)
        {
            j = n / (n / i);
            auto x = n / i % mod;
            p.push_back(n / i);
            f.push_back((x * (x + 1) / 2 % mod - 1) % mod);
            g.push_back((x * (x + 1) / 2 % mod * (2 * x + 1) % mod * inv3 % mod - 1) % mod);
            if (n / i <= block)
                id1[n / i] = (int)p.size() - 1;
            else
                id2[n / (n / i)] = (int)p.size() - 1;
        }
        for (int i = 1; i < (int)prime.size(); ++i)
            for (int j = 0; j < (int)p.size() && (i64)prime[i] * prime[i] <= p[j]; ++j)
            {
                int k = (p[j] / prime[i] <= block ? id1[p[j] / prime[i]] : id2[n / (p[j] / prime[i])]);
                (f[j] -= prime[i] * (f[k] - primef[i - 1])) %= mod;
                (g[j] -= (i64)prime[i] * prime[i] % mod * (g[k] - primeg[i - 1])) %= mod;
            }
        return (solve(n, 0) + 1 + mod) % mod;
    }
};