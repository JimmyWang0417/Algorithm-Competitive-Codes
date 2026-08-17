auto berlekampMassey(const vector<int> &a)
{
    vector<i64> v, last;
    int k = -1;
    i64 delta = 0;

    for (int i = 0; i < (int)a.size(); i++)
    {
        i64 tmp = 0;
        for (int j = 0; j < (int)v.size(); j++)
            (tmp += a[i - j - 1] * v[j]) %= mod;

        if (a[i] == tmp)
            continue;

        if (k < 0)
        {
            k = i;
            delta = (a[i] - tmp) % mod;
            v = vector<i64>(i + 1);
            continue;
        }

        auto u = v;
        auto val = (a[i] - tmp) * quickpow(delta, mod - 2) % mod;

        if (v.size() < last.size() + i - k)
            v.resize(last.size() + i - k);

        (v[i - k - 1] += val) %= mod;

        for (int j = 0; j < (int)last.size(); j++)
        {
            v[i - k + j] = (v[i - k + j] - val * last[j]) % mod;
            if (v[i - k + j] < 0)
                v[i - k + j] += mod;
        }

        if ((int)u.size() - i < (int)last.size() - k)
        {
            last = u;
            k = i;
            delta = (a[i] - tmp) % mod;
        }
    }
    for (auto &x : v)
        x = (x + mod) % mod;
    return v;
}