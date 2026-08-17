namespace stringAlgorithm
{
    struct manacher
    {
        vector<int> p;
        manacher() = default;
        manacher(const string &s)
        {
            string str = "!|";
            str.reserve(2 * s.size() + 3);
            for (auto c : s)
            {
                str.push_back(c);
                str.push_back('|');
            }
            str.push_back('@');
            p.resize(str.size());
            for (int i = 1, mid = 0, r = 0; i < (int)str.size() - 1; ++i)
            {
                if (i <= r)
                    p[i] = min(p[mid * 2 - i], r - i + 1);
                while (str[i - p[i]] == str[i + p[i]])
                    ++p[i];
                if (i + p[i] - 1 > r)
                    mid = i, r = i + p[i] - 1;
            }
        }
        auto split()
        {
            vector<int> p1(p.size() / 2 - 1), p2(p.size() / 2 - 2);
            for (int i = 0; i < (int)p1.size(); ++i)
                p1[i] = p[i * 2 + 2] - 1;
            for (int i = 0; i < (int)p2.size(); ++i)
                p2[i] = p[i * 2 + 3] - 1;
            return make_pair(p1, p2);
        }
    };
}