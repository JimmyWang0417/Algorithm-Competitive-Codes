struct DancingLinks
{
    int n, m, tot;
    vector<int> l, r, u, d, row, col, size, head, answer;
    DancingLinks(int _n, int _m, const vector<pair<int, int>> &edges)
        : n(_n), m(_m), tot(m), l(m + edges.size() + 1), r(l.size()), u(l.size()), d(l.size()),
          row(l.size()), col(l.size()), size(m + 1), head(n + 1)
    {
        for (int i = 0; i <= m; ++i)
            l[i] = i - 1, r[i] = i + 1, u[i] = d[i] = i;
        l[0] = m, r[m] = 0;
        for (auto [x, y] : edges)
            insert(x, y);
    }
    auto insert(int x, int y) -> void
    {
        ++tot;
        row[tot] = x, col[tot] = y, ++size[y];
        u[tot] = u[y], d[tot] = y;
        d[u[y]] = tot, u[y] = tot;
        if (!head[x])
            head[x] = l[tot] = r[tot] = tot;
        else
        {
            l[tot] = l[head[x]], r[tot] = head[x];
            r[l[head[x]]] = tot, l[head[x]] = tot;
        }
    }
    auto remove(int x)
    {
        l[r[x]] = l[x], r[l[x]] = r[x];
        for (int i = d[x]; i != x; i = d[i])
            for (int j = r[i]; j != i; j = r[j])
            {
                u[d[j]] = u[j], d[u[j]] = d[j];
                --size[col[j]];
            }
    }
    auto restore(int x)
    {
        for (int i = u[x]; i != x; i = u[i])
            for (int j = l[i]; j != i; j = l[j])
            {
                ++size[col[j]];
                u[d[j]] = d[u[j]] = j;
            }
        l[r[x]] = r[l[x]] = x;
    }
    auto dance() -> bool
    {
        if (!r[0])
            return true;
        int x = r[0];
        for (int i = r[x]; i; i = r[i])
            if (size[i] < size[x])
                x = i;
        remove(x);
        for (int i = d[x]; i != x; i = d[i])
        {
            answer.push_back(row[i]);
            for (int j = r[i]; j != i; j = r[j])
                remove(col[j]);
            if (dance())
                return true;
            for (int j = l[i]; j != i; j = l[j])
                restore(col[j]);
            answer.pop_back();
        }
        restore(x);
        return false;
    }
    auto solve()
    {
        answer.clear();
        return dance();
    }
};
