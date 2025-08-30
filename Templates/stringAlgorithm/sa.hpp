namespace stringAlgorithm
{
    struct suffixArray
    { // ababa 对应 4 2 0 3 1; 1 3 0 2
        vector<int> height;
        vector<int> sa, rk;
        suffixArray() = default;
        suffixArray(const string &_str) : height(_str.size()), sa(_str.size()), rk(_str.size())
        {
            auto str = _str.c_str();
            int n = (int)_str.size(), m = 128;
            vector<int> x(2 * n, -1), y(2 * n, -1);
            vector<int> ws(max(m, n));
            for (int i = 0; i < n; ++i)
                ++ws[x[i] = str[i]];
            for (int i = 1; i < m; ++i)
                ws[i] += ws[i - 1];
            for (int i = n - 1; i >= 0; --i)
                sa[--ws[x[i]]] = i;
            for (int i = 0; i < m; ++i)
                ws[i] = 0;

            for (int j = 1, p = 0; p < n; m = p, j <<= 1)
            {
                p = 0;
                for (int i = n - j; i < n; ++i)
                    y[p++] = i;
                for (int i = 0; i < n; ++i)
                    if (sa[i] >= j)
                        y[p++] = sa[i] - j;

                for (int i = 0; i < n; ++i)
                    ++ws[x[i]];
                for (int i = 1; i < m; ++i)
                    ws[i] += ws[i - 1];
                for (int i = n - 1; i >= 0; --i)
                    sa[--ws[x[y[i]]]] = y[i];
                for (int i = 0; i < m; ++i)
                    ws[i] = 0;

                swap(x, y);
                p = 0;
                for (int i = 0; i < n; ++i)
                {
                    auto compare = [&](int l, int r)
                    { return y[l] == y[r] && y[l + j] == y[r + j]; };
                    x[sa[i]] = i + 1 < n && compare(sa[i], sa[i + 1]) ? p : p++;
                }
            }

            for (int i = 0; i < n; ++i)
                rk[sa[i]] = i;
            for (int i = 0, j = 0; i < n; ++i)
            {
                if (j)
                    --j;
                if (rk[i])
                {
                    while (str[i + j] == str[sa[rk[i] - 1] + j])
                        ++j;
                    height[rk[i]] = j;
                }
            }
        }
    };
}