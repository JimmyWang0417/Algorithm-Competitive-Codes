template <typename T = i64>
struct sieve
{
    vector<int> prime, low;
    vector<T> f, pre;
    template <typename F>
    sieve(int n, F calc) : low(n + 1), f(n + 1)
    {
        if (n)
            f[1] = 1;
        for (int i = 2; i <= n; ++i)
        {
            if (!low[i])
            {
                prime.emplace_back(i);
                for (int j = 1, k = i; k <= n; ++j, k *= i)
                {
                    low[k] = k;
                    f[k] = calc(i, j, k);
                    if (k > n / i)
                        break;
                }
            }
            for (int j = 0; j < (int)prime.size(); ++j)
            {
                if (i * prime[j] > n)
                    break;
                int x = i * prime[j];
                if (i % prime[j] == 0)
                {
                    low[x] = low[i] * prime[j];
                    if (x != low[x])
                        f[x] = f[x / low[x]] * f[low[x]];
                    break;
                }
                low[x] = prime[j];
                f[x] = f[i] * f[prime[j]];
            }
        }
        pre.resize(f.size());
        partial_sum(f.begin(), f.end(), pre.begin());
    }
};
