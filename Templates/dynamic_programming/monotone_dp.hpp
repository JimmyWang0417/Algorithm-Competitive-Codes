template <typename T, typename F, typename Compare>
auto divideDP(int l, int r, int x, int y, vector<T> &dp, vector<int> &from, F &calc, Compare &cmp) -> void
{
    if (l > r || x > y)
        return;
    int mid = (l + r) >> 1, pos = x;
    dp[mid] = calc(x, mid);
    for (int i = x + 1; i <= y; ++i)
    {
        T now = calc(i, mid);
        if (cmp(now, dp[mid]))
            dp[mid] = now, pos = i;
    }
    from[mid] = pos;
    divideDP(l, mid - 1, x, pos, dp, from, calc, cmp);
    divideDP(mid + 1, r, pos, y, dp, from, calc, cmp);
}
template <typename T, typename F, typename Compare>
auto monotoneDP(int l, int r, int x, int y, vector<T> &dp, vector<int> &from, F calc, Compare cmp)
{
    divideDP(l, r, x, y, dp, from, calc, cmp);
}
template <typename T, typename F, typename Compare>
auto monotoneDP(vector<T> &dp, vector<int> &from, F calc, Compare cmp)
{
    int n = (int)dp.size() - 1, head = 0, tail = 0;
    vector<array<int, 3>> que(n + 1);
    que[0] = {0, 1, n};
    for (int i = 1; i <= n; ++i)
    {
        while (que[head][2] < i)
            ++head;
        int p = que[head][0];
        dp[i] = calc(p, i), from[i] = p;
        if (i == n)
            continue;
        while (head <= tail && cmp(calc(i, que[tail][1]), calc(que[tail][0], que[tail][1])))
            --tail;
        if (head > tail)
            que[++tail] = {i, i + 1, n};
        else if (cmp(calc(i, n), calc(que[tail][0], n)))
        {
            int l = max(i + 1, que[tail][1]), r = n;
            while (l < r)
            {
                int mid = (l + r) >> 1;
                if (cmp(calc(i, mid), calc(que[tail][0], mid)))
                    r = mid;
                else
                    l = mid + 1;
            }
            que[tail][2] = l - 1;
            que[++tail] = {i, l, n};
        }
    }
}
template <typename T, typename F, typename Compare>
auto quadrangleDP(int n, T zero, F cost, Compare cmp)
{
    vector dp(n + 1, vector<T>(n + 1, zero));
    vector from(n + 1, vector<int>(n + 1));
    for (int i = 1; i <= n; ++i)
        from[i][i] = i;
    for (int len = 2; len <= n; ++len)
        for (int l = 1, r = len; r <= n; ++l, ++r)
        {
            int x = max(l, from[l][r - 1]), y = min(r - 1, from[l + 1][r]);
            from[l][r] = x;
            dp[l][r] = dp[l][x] + dp[x + 1][r] + cost(l, r);
            for (int k = x + 1; k <= y; ++k)
            {
                T now = dp[l][k] + dp[k + 1][r] + cost(l, r);
                if (cmp(now, dp[l][r]))
                    dp[l][r] = now, from[l][r] = k;
            }
        }
    return pair(dp, from);
}
