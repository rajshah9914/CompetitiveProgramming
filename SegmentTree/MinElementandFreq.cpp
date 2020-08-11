// https://codeforces.com/edu/course/2/lesson/4/1/practice/contest/273169/problem/C

#include <bits/stdc++.h>
using namespace std;

// Print minimum element in range space separated with its count from L to R-1..(0≤l<r≤n)

struct segtree
{
    int size;
    vector<pair<int, int>> sums;
    void init(int n)
    {
        size = 1;
        while (size < n)
            size *= 2;
        sums.assign(2 * size, {INT_MAX, 0});
    }

    pair<int, int> merge(pair<int, int> p1, pair<int, int> p2)
    {
        if (p1.first < p2.first)
        {
            return p1;
        }
        else if (p2.first < p1.first)
        {
            return p2;
        }
        else
        {
            return {p1.first, p1.second + p2.second};
        }
    }

    void build(vector<long long> &a, int x, int lx, int rx)
    {
        if (rx - lx == 1)
        {
            if (lx < (int)a.size())
                sums[x] = {a[lx], 1};
            return;
        }
        int m = (lx + rx) / 2;
        build(a, 2 * x + 1, lx, m);
        build(a, 2 * x + 2, m, rx);
        sums[x] = merge(sums[2 * x + 1], sums[2 * x + 2]);
    }

    void build(vector<long long> &a)
    {
        build(a, 0, 0, size);
    }

    void set(int i, int v, int x, int lx, int rx)
    {
        if (rx - lx == 1)
        {
            sums[x] = {v, 1};
            return;
        }
        int m = (lx + rx) / 2;
        if (i < m)
        {
            set(i, v, 2 * x + 1, lx, m);
        }
        else
        {
            set(i, v, 2 * x + 2, m, rx);
        }
        sums[x] = merge(sums[2 * x + 1], sums[2 * x + 2]);
    }

    void set(int i, int v)
    {
        set(i, v, 0, 0, size);
    }

    pair<int, int> sum(int l, int r, int x, int lx, int rx)
    {
        if (lx >= r || rx <= l)
            return {INT_MAX, 0};
        if (lx >= l && rx <= r)
            return sums[x];
        else
        {
            int m = (lx + rx) / 2;
            pair<int, int> s1 = sum(l, r, 2 * x + 1, lx, m);
            pair<int, int> s2 = sum(l, r, 2 * x + 2, m, rx);
            return merge(s1, s2);
        }
    }

    pair<int, int> sum(int l, int r)
    {
        return sum(l, r, 0, 0, size);
    }
};

int main()
{
    int n, m;
    cin >> n >> m;
    segtree st;
    st.init(n);
    vector<long long> a(n);
    for (int i = 0; i < n; i++)
        cin >> a[i];
    st.build(a);

    while (m--)
    {
        int d, l, r;
        cin >> d >> l >> r;
        if (d == 1)
        {
            st.set(l, r);
        }
        else
        {
            pair<int, int> p = st.sum(l, r);
            cout << p.first << " " << p.second << endl;
        }
    }
}