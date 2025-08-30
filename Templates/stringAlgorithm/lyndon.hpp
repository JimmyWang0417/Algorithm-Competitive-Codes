namespace stringAlgorithm
{
    struct lyndon
    {
        auto duval(string s)
        {
            vector<string> ans;
            for (int i = 0, j, k; i < (int)s.size();)
            {
                j = i, k = i + 1;
                while (k < (int)s.size() && s[j] <= s[k])
                {
                    if (s[j] < s[k])
                        j = i;
                    else
                        ++j;
                    ++k;
                }
                while (i <= j)
                {
                    ans.emplace_back(s.substr(i, k - j));
                    i += k - j;
                }
            }
            return ans;
        }
    };
}