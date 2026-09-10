template <typename T>
struct cdq
{
    vector<T> &a, tmp;
    template <typename Compare, typename Add, typename Query, typename Clear>
    auto solve(int l, int r, Compare &cmp, Add &add, Query &query, Clear &clear) -> void
    {
        if (l >= r)
            return;
        int mid = (l + r) >> 1;
        solve(l, mid, cmp, add, query, clear);
        solve(mid + 1, r, cmp, add, query, clear);
        int i = l, j = mid + 1, k = l;
        while (i <= mid && j <= r)
        {
            if (cmp(a[i], a[j]))
                add(a[i]), tmp[k++] = a[i++];
            else
                query(a[j]), tmp[k++] = a[j++];
        }
        while (j <= r)
            query(a[j]), tmp[k++] = a[j++];
        for (int p = l; p < i; ++p)
            clear(a[p]);
        while (i <= mid)
            tmp[k++] = a[i++];
        for (int p = l; p <= r; ++p)
            a[p] = tmp[p];
    }
    cdq(vector<T> &_a) : a(_a), tmp(a) {}
    template <typename Compare, typename Add, typename Query, typename Clear>
    auto solve(Compare cmp, Add add, Query query, Clear clear)
    {
        if (!a.empty())
            solve(0, (int)a.size() - 1, cmp, add, query, clear);
    }
};
