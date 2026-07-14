#pragma once
#include <numeric>
#include <utility>
#include <vector>

template <typename T = long long>
struct sieve
{
    int n = 0;
    std::vector<int> prime, low, mu, mu2;
    std::vector<T> phi, preMu, preMu2, prePhi;

    sieve() = default;
    sieve(int _n) : n(_n),
                    low(n + 1), mu(n + 1), mu2(n + 1), phi(n + 1),
                    preMu(n + 1), preMu2(n + 1), prePhi(n + 1)
    {
        work();
    }

    auto init(int _n)
    {
        n = _n;
        low.resize(n + 1), mu.resize(n + 1), mu2.resize(n + 1), phi.resize(n + 1);
        preMu.resize(n + 1), preMu2.resize(n + 1), prePhi.resize(n + 1);
        work();
    }

    auto work()
    {
        if (!n)
            return;
        mu[1] = mu2[1] = 1;
        phi[1] = 1;
        for (int i = 2; i <= n; ++i)
        {
            if (!low[i])
            {
                low[i] = i;
                prime.push_back(i);
                mu[i] = -1;
                mu2[i] = 1;
                phi[i] = i - 1;
            }
            for (int p : prime)
            {
                if (1LL * i * p > n)
                    break;
                int x = i * p;
                low[x] = p;
                if (i % p == 0)
                {
                    mu[x] = 0;
                    mu2[x] = 0;
                    phi[x] = phi[i] * p;
                    break;
                }
                mu[x] = -mu[i];
                mu2[x] = mu2[i];
                phi[x] = phi[i] * (p - 1);
            }
        }
        for (int i = 1; i <= n; ++i)
        {
            preMu[i] = preMu[i - 1] + mu[i];
            preMu2[i] = preMu2[i - 1] + mu2[i];
            prePhi[i] = prePhi[i - 1] + phi[i];
        }
    }

    auto isPrime(int x) const
    {
        return x >= 2 && x <= n && low[x] == x;
    }

    auto factor(int x) const
    {
        std::vector<std::pair<int, int>> res;
        while (x > 1)
        {
            int p = low[x], cnt = 0;
            while (x % p == 0)
            {
                x /= p;
                ++cnt;
            }
            res.emplace_back(p, cnt);
        }
        return res;
    }
};
