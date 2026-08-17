namespace stringAlgorithm
{
    struct MinRep
    {
        static auto solve(const string &s)
        {
            int n = (int)s.size();
            int i = 0, j = 1, k = 0;
            while (i < n && j < n && k < n)
            {
                if (s[(i + k) % n] == s[(j + k) % n])
                    ++k;
                else
                {
                    if (s[(i + k) % n] > s[(j + k) % n])
                        i += k + 1;
                    else
                        j += k + 1;
                    if (i == j)
                        ++j;
                    k = 0;
                }
            }
            return min(i, j);
        }
    };
}
