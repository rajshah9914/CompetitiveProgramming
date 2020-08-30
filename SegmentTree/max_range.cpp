
//  There is an array of n elements, initially filled with zeros. You need to write a data structure that processes two types of queries:
// for all i from l to r−1 do the operation ai=max(ai,v),
//find the current value of element i.


#include<bits/stdc++.h>
using namespace std;

struct segtree{
    vector<int>operations;
    int size;
    void init(int n)
    {
        size=1;
        while(size<2*n)size*=2;
        operations.assign(2*size,0);
    }

    void update_max(int l, int r,int v,int x,int lx,int rx){
        if(lx>=r || rx<=l)
            return;
        if(lx>=l && rx<=r) {
            operations[x] =max(v,operations[x]);
            return;
        }
        int m=(lx+rx)/2;
        update_max(l,r,v,2*x+1,lx,m);
        update_max(l,r,v,2*x+2,m,rx);
    }

    void update_max(int l,int r,int v){
        update_max(l,r,v,0,0,size);
    }

    int get(int i,int x,int lx, int rx){
        if(rx-lx==1){
            return operations[x];
        }
        int m=(lx+rx)/2;
        int res=0;
        if(i<m)
        res=get(i,2*x+1,lx,m);
        else
        res=get(i,2*x+2,m,rx);
        return max(res,operations[x]);
    }

    int get(int i){
        return get(i,0,0,size);
    }
};

int main()
{
    int n,q;
    cin>>n>>q;
    segtree st;
    st.init(n);
    while(q--){
        int ch;
        cin>>ch;
        if(ch==1){
            int l,r,v;
            cin>>l>>r>>v;
            st.update_max(l,r,v);
        }
        else
        {
            int i;
            cin>>i;
            cout<<st.get(i)<<endl;
        }
    }
}
