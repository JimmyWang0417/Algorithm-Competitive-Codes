struct min25
{
    static constexpr int inv3 = quickpow(3);
    i64 n, answer;
    int block;
    vector<int> prime, id1, id2;
    vector<i64> primef, primeg;
    vector<i64> p, f, g;
    auto sieve() -> void
    {
        vector<bool> vis(block + 1);
        prime.emplace_back();
        primef.emplace_back();
        primeg.emplace_back();
        for (int i = 2; i <= block; ++i)
        {
            if (!vis[i])
            {
                prime.emplace_back(i);
                primef.emplace_back((primef.back() + i) % mod);
                primeg.emplace_back((primeg.back() + (i64)i * i) % mod);
            }
            for (int j = 1; j < (int)prime.size(); ++j)
            {
                if (i * prime[j] > block)
                    break;
                vis[i * prime[j]] = true;
                if (i % prime[j] == 0)
                    break;
            }
        }
    }
    auto getid(i64 x) const
    {
        return x <= block ? id1[x] : id2[n / x];
    }
    auto solve(i64 x, int y) -> i64
    {
        if (x <= prime[y])
            return 0;
        int k = getid(x);
        i64 res = ((g[k] - f[k]) - (primeg[y] - primef[y])) % mod;
        for (int i = y + 1; i < (int)prime.size() && (i64)prime[i] * prime[i] <= x; ++i)
            for (i64 pe = prime[i]; pe <= x; pe *= prime[i])
                (res += pe % mod * ((pe - 1) % mod) % mod * (solve(x / pe, i) + (pe != prime[i]))) %= mod;
        return res;
    }
    min25(i64 _n) : n(_n), block((int)sqrt(n)), id1(block + 1), id2(block + 1)
    {
        sieve();
        for (i64 i = 1, j; i <= n; i = j + 1)
        {
            j = n / (n / i);
            i64 x = n / i % mod;
            p.emplace_back(n / i);
            f.emplace_back((x * (x + 1) / 2 % mod - 1) % mod);
            g.emplace_back((x * (x + 1) / 2 % mod * (2 * x + 1) % mod * inv3 % mod - 1) % mod);
            if (n / i <= block)
                id1[n / i] = (int)p.size() - 1;
            else
                id2[n / (n / i)] = (int)p.size() - 1;
        }
        for (int i = 1; i < (int)prime.size(); ++i)
            for (int j = 0; j < (int)p.size() && (i64)prime[i] * prime[i] <= p[j]; ++j)
            {
                int k = getid(p[j] / prime[i]);
                (f[j] -= prime[i] * (f[k] - primef[i - 1])) %= mod;
                (g[j] -= (i64)prime[i] * prime[i] % mod * (g[k] - primeg[i - 1])) %= mod;
            }
        answer = (solve(n, 0) + 1 + mod) % mod;
    }
};
