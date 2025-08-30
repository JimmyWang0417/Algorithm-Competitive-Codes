namespace stringAlgorithm
{
    struct acam
    {
        struct node
        {
            int ch[26], fail;
            auto operator[](int x) const { return ch[x]; }
            auto &operator[](int x) { return ch[x]; }
        };
        vector<node> tree;
        vector<int> where;
        auto insert(const string &s)
        {
            auto newnode = [&]()
            {
                tree.emplace_back();
                return (int)tree.size() - 1;
            };
            int u = 0;
            for (int i = 0; i < (int)s.size(); ++i)
            {
                int c = s[i] - 'a';
                if (!tree[u][c])
                    tree[u][c] = newnode();
                u = tree[u][c];
            }
            return u;
        }
        auto build()
        {
            queue<int> q;
            for (int i = 0; i < 26; ++i)
                if (tree[0][i])
                    q.push(tree[0][i]);
            while (!q.empty())
            {
                int u = q.front();
                q.pop();
                for (int i = 0; i < 26; i++)
                {
                    if (tree[u][i])
                    {
                        tree[tree[u][i]].fail = tree[tree[u].fail][i];
                        q.push(tree[u][i]);
                    }
                    else
                        tree[u][i] = tree[tree[u].fail][i];
                }
            }
        }
        auto match(const string &s)
        {
            int u = 0;
            for (int i = 0; i < (int)s.size(); ++i)
            {
                int c = s[i] - 'a';
                if (!tree[u][c])
                    return -1;
                u = tree[u][c];
            }
            return u;
        }
        acam() = default;
        acam(const vector<string> &s) : tree(1), where(s.size())
        {
            for (int i = 0; i < (int)s.size(); ++i)
                where[i] = insert(s[i]);
            build();
        }
    };
}