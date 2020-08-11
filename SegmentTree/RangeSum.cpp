#include<bits/stdc++.h>
using namespace std;

// range sum from L to R-1 (0≤l<r≤n)

struct segtree {
    int size;
    vector<long long>sums;
    void init(int n){
        size=1;
        while(size<n)size*=2;
        sums.assign(2*size,0LL);
    }

    void build(vector<long long>&a, int x,int lx,int rx){
        if(rx-lx==1)
        {
            if(lx<(int)a.size())
                sums[x]=a[lx];
            return;
        }
        int m=(lx+rx)/2;
        build(a,2*x+1,lx,m);
        build(a,2*x+2,m,rx);
        sums[x]=sums[2*x+1]+sums[2*x+2];
    }

    void build(vector<long long>&a) {
        build(a, 0, 0, size);
    }

    void set(int i,int v,int x,int lx,int rx){
        if(rx-lx==1){
            sums[x]=v;
            return;
        }
        int m=(lx+rx)/2;
        if(i<m) {
            set(i, v, 2 * x + 1, lx, m);
        }
        else {
            set(i, v, 2 * x + 2, m, rx);
        }
        sums[x]=sums[2*x+1]+sums[2*x+2];
    }

    void set(int i,int v)
    {
        set(i,v,0,0,size);
    }

    long long sum(int l,int r,int x,int lx,int rx)
    {
        if(lx>=r || rx<=l) return 0;
        if(lx>=l && rx<=r)
            return sums[x];
        else
        {
            int m=(lx+rx)/2;
            long long s1=sum(l,r,2*x+1,lx,m);
            long long s2=sum(l,r,2*x+2,m,rx);
            return s1+s2;
        }
    }

    long long sum(int l,int r)
    {
        return sum(l,r,0,0,size);
    }

};

int main()
{
    int n,m;
    cin>>n>>m;
    segtree st;
    st.init(n);
    vector<long long>a(n);
    for(int i=0;i<n;i++)
        cin>>a[i];
    st.build(a);

    while(m--)
    {
        int d,l,r;
        cin>>d>>l>>r;
        if(d==1)
        {
            st.set(l,r);
        }
        else
        {
            cout<<st.sum(l,r)<<endl;
        }
    }

}