struct pam
{
    struct node : array<int, 26>
    {
        int fail, len, link;
    };
    vector<int> where;
    vector<node> point;
    template <bool SaveLink, typename GetLen>
    auto build(const string &str, GetLen get_len)
    {
        auto newnode = [&]()
        {
            point.emplace_back();
            return (int)point.size() - 1;
        };
        point[0].fail = 1;
        point[1].len = -1;
        where.resize((int)str.size());
        for (int n = 0, las = 1; n < (int)str.size(); ++n)
        {
            int c = str[n] - 'a';
            auto find = [&](int now)
            {
                while (n - point[now].len - 1 < 0 || str[n] != str[n - point[now].len - 1])
                    now = point[now].fail;
                return now;
            };
            int cur = find(las), now = point[cur][c];
            if (!now)
            {
                now = newnode();
                point[now].len = point[cur].len + 2;
                point[now].fail = point[find(point[cur].fail)][c];
                point[cur][c] = now;
                if constexpr (SaveLink)
                {
                    int limit = get_len(point[now].len);
                    int link = point[find(point[las].link)][c];
                    while (point[link].len > limit)
                        link = point[link].fail;
                    point[now].link = link;
                }
            }
            where[n] = las = now;
        }
    }
    pam() = default;
    pam(const string &str) : point(2)
    {
        build<false>(str, [](int) { return 0; });
    }
    template <typename GetLen>
    pam(const string &str, GetLen get_len) : point(2)
    {
        build<true>(str, get_len);
    }
};
