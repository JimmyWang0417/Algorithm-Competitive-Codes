template <bool minHeap = true>
struct cartesianTree
{
    int root;
    vector<int> lc, rc;
    cartesianTree() = default;
    cartesianTree(const vector<int> &p) : lc(p.size()), rc(p.size())
    {
        int n = (int)p.size() - 1;
        stack<int> st;
        for (int i = 1; i <= n; ++i)
        {
            if constexpr (minHeap)
                while (!st.empty() && p[st.top()] > p[i])
                {
                    lc[i] = st.top();
                    st.pop();
                }
            else
                while (!st.empty() && p[st.top()] < p[i])
                {
                    lc[i] = st.top();
                    st.pop();
                }
            if (!st.empty())
                rc[st.top()] = i;
            st.push(i);
        }
        while (st.size() > 1)
            st.pop();
        root = st.top();
    }
};