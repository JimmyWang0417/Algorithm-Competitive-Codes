namespace stringAlgorithm
{
    struct pam
    {
        struct node
        {
            int ch[26];
            int fail, len;
            auto operator[](int x) const { return ch[x]; }
            auto &operator[](int x) { return ch[x]; }
        };
        vector<node> point;
        pam() = default;
        pam(const string &str) : point(2)
        {
            auto newnode = [&]()
            {
                point.emplace_back();
                return (int)point.size() - 1;
            };
            point[0].fail = 1;
            point[1].len = -1;
            for (int n = 0, las = 1; n < (int)str.size(); ++n)
            {
                int c = str[n] - 'a';
                auto find = [&](int now)
                {
                    while (str[n] != str[n - point[now].len - 1])
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
                }
                las = now;
            }
        }
    };
}