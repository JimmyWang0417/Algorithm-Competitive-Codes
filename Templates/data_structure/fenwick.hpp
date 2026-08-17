template <typename T, bool isPrefix = true>
struct fenwick
{
    vector<T> c;

    using functype = function<void(T &x, T y)>;
    functype func;
    constexpr static auto _func = [](T &x, T y)
    { x += y; };

    fenwick() = default;
    fenwick(int n, const functype &other = _func) : c(n + 1), func(other) {}
    constexpr static auto lowbit = [](int x)
    { return x & (-x); };
    auto update(int pos, int val)
    {
        if constexpr (isPrefix)
            for (int i = pos; i < (int)c.size(); i += lowbit(i))
                func(c[i], val);
        else
            for (int i = pos; i; i -= lowbit(i))
                func(c[i], val);
    }
    auto query(int pos)
    {
        T res = 0;
        if constexpr (isPrefix)
            for (int i = pos; i; i -= lowbit(i))
                func(res, c[i]);
        else
            for (int i = pos; i < (int)c.size(); i += lowbit(i))
                func(res, c[i]);
        return res;
    }
};