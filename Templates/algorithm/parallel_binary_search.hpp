template <typename T>
struct ParallelBinarySearch
{
    vector<T> &a, tmp;
    vector<bool> left;
    template <typename Divide, typename Clear, typename Answer>
    auto work(int ql, int qr, int l, int r, Divide &divide, Clear &clear, Answer &answer) -> void
    {
        if (ql > qr)
            return;
        if (l == r)
        {
            for (int i = ql; i <= qr; ++i)
                answer(a[i], l);
            return;
        }
        int mid = (l + r) >> 1, cnt = 0;
        for (int i = ql; i <= qr; ++i)
            left[i] = divide(a[i], mid), cnt += left[i];
        for (int i = qr; i >= ql; --i)
            if (left[i])
                clear(a[i]);
        int x = ql, y = ql + cnt;
        for (int i = ql; i <= qr; ++i)
            tmp[left[i] ? x++ : y++] = a[i];
        for (int i = ql; i <= qr; ++i)
            a[i] = tmp[i];
        work(ql, ql + cnt - 1, l, mid, divide, clear, answer);
        work(ql + cnt, qr, mid + 1, r, divide, clear, answer);
    }
    ParallelBinarySearch(vector<T> &_a) : a(_a), tmp(a), left(a.size()) {}
    template <typename Divide, typename Clear, typename Answer>
    auto solve(int ql, int qr, int l, int r, Divide divide, Clear clear, Answer answer)
    {
        work(ql, qr, l, r, divide, clear, answer);
    }
};
