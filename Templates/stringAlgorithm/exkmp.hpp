namespace stringAlgorithm
{
    struct exkmp
    { // 后缀lcp
        string s;
        vector<int> z;
        exkmp() = default;
        exkmp(const string &_s) : z(_s.size())
        {
            s = _s;
            z[0] = (int)s.size();
            for (int i = 1, l = 0, r = -1; i < (int)s.size(); ++i)
            {
                if (i <= r)
                    z[i] = min(r - i + 1, z[i - l]);
                while (i + z[i] < (int)s.size() && s[z[i]] == s[i + z[i]])
                    ++z[i];
                if (i + z[i] - 1 > r)
                    l = i, r = i + z[i] - 1;
            }
        }
        auto match(const string &t)
        {
            vector<int> p(t.size());
            for (int i = 0, l = 0, r = -1; i < (int)t.size(); ++i)
            {
                if (i <= r)
                    p[i] = min(r - i + 1, z[i - l]);
                while (i + p[i] < (int)t.size() && s[p[i]] == t[i + p[i]])
                    ++p[i];
                if (i + p[i] - 1 > r)
                    l = i, r = i + p[i] - 1;
            }
            return p;
        }
    };
}