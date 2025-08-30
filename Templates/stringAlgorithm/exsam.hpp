namespace stringAlgorithm
{
    struct exsam
    {
        struct node
        {
            int ch[26];
            int len, fail;
            auto operator[](int x) const { return ch[x]; }
            auto &operator[](int x) { return ch[x]; }
        };
        vector<node> point;
        exsam() = default;
        exsam(const vector<string> &str) : point(2)
        {
            int las = 1;
            auto insert = [&](int c)
            {
                auto newnode = [&]()
                {
                    point.emplace_back();
                    return (int)point.size() - 1;
                };
                int p = las;
                if (point[p][c])
                {
                    int q = point[p][c];
                    if (point[q].len == point[p].len + 1)
                        return las = q;
                    else
                    {
                        int nq = newnode();
                        point[nq] = point[q];
                        point[nq].len = point[p].len + 1;
                        point[q].fail = nq;
                        for (; p && point[p][c] == q; p = point[p].fail)
                            point[p][c] = nq;
                        return las = nq;
                    }
                }
                int np = las = newnode();
                point[np].len = point[p].len + 1;
                for (; p && !point[p][c]; p = point[p].fail)
                    point[p][c] = np;
                if (!p)
                    point[np].fail = 1;
                else
                {
                    int q = point[p][c];
                    if (point[q].len == point[p].len + 1)
                        point[np].fail = q;
                    else
                    {
                        int nq = newnode();
                        point[nq] = point[q];
                        point[nq].len = point[p].len + 1;
                        point[np].fail = point[q].fail = nq;
                        for (; p && point[p][c] == q; p = point[p].fail)
                            point[p][c] = nq;
                    }
                }
                return np;
            };
            for (const auto &s : str)
            {
                las = 1;
                for (auto c : s)
                    insert(c - 'a');
            }
        }
    };
}