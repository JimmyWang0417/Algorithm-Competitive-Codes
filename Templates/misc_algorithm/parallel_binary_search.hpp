template <typename T>
struct ParallelBinarySearch
{
    vector<T> &answer;
    template <typename Calc, typename Compare>
    auto work(int l, int r, int L, int R, Calc &calc, Compare &cmp) -> void
    {
        if (l > r || L > R)
            return;
        int mid = (l + r) >> 1, p = L;
        answer[mid] = calc(L, mid);
        for (int i = L + 1; i <= R; ++i)
        {
            auto now = calc(i, mid);
            if (cmp(now, answer[mid]))
                answer[mid] = now, p = i;
        }
        work(l, mid - 1, L, p, calc, cmp);
        work(mid + 1, r, p, R, calc, cmp);
    }
    ParallelBinarySearch(vector<T> &_answer) : answer(_answer) {}
    template <typename Calc, typename Compare>
    auto solve(int l, int r, int L, int R, Calc calc, Compare cmp)
    {
        work(l, r, L, R, calc, cmp);
    }
};
