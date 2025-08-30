namespace stringAlgorithm
{
    struct sam
    { // aabaa的子串数是11
        struct node
        {
            int ch[26];
            int len, fail;
            auto operator[](int x) const { return ch[x]; }
            auto &operator[](int x) { return ch[x]; }
        };
        vector<node> point;
        sam() = default;
        sam(const string &s) : point(2)
        {
            int las = 1;
            auto insert = [&](int c)
            {
                auto newnode = [&]()
                {
                    point.emplace_back();
                    return (int)point.size() - 1;
                };
                int p = las, np = las = newnode();
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
            for (int i = 0; i < (int)s.size(); ++i)
                insert(s[i] - 'a');
        }
    };
}