template <typename T>
struct cdq
{
    vector<T> &a;
    template <typename Compare, typename Add, typename Query, typename Clear, typename Leaf>
    auto work(int l, int r, Compare &cmp, Add &add, Query &query, Clear &clear, Leaf &leaf) -> void
    {
        if (l == r)
        {
            leaf(l);
            return;
        }
        int mid = (l + r) >> 1;
        work(l, mid, cmp, add, query, clear, leaf);
        vector<T> A(a.begin() + l, a.begin() + mid + 1);
        vector<T> B(a.begin() + mid + 1, a.begin() + r + 1);
        sort(A.begin(), A.end(), cmp);
        sort(B.begin(), B.end(), cmp);
        int i = 0, j = 0;
        while (i < (int)A.size() && j < (int)B.size())
        {
            if (cmp(B[j], A[i]))
                query(B[j++]);
            else
                add(A[i++]);
        }
        while (j < (int)B.size())
            query(B[j++]);
        for (int p = 0; p < i; ++p)
            clear(A[p]);
        work(mid + 1, r, cmp, add, query, clear, leaf);
    }
    cdq(vector<T> &_a) : a(_a) {}
    template <typename Compare, typename Add, typename Query, typename Clear, typename Leaf>
    auto solve(Compare cmp, Add add, Query query, Clear clear, Leaf leaf)
    {
        if (!a.empty())
            work(0, (int)a.size() - 1, cmp, add, query, clear, leaf);
    }
    template <typename Compare, typename Add, typename Query, typename Clear>
    auto solve(Compare cmp, Add add, Query query, Clear clear)
    {
        auto leaf = [](int) {};
        solve(cmp, add, query, clear, leaf);
    }
};
