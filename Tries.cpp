// https://codingcompetitions.withgoogle.com/kickstart/round/000000000019ffc7/00000000001d3ff3


#include <bits/stdc++.h>
using namespace std;
int node,c[2000000][26],cnt[2000000],ans,k;

void dfs(int u=0,int d=0)
{
    for(int i=0;i<26;i++)
    {
        if(c[u][i])
        {
            dfs(c[u][i],d+1);
            cnt[u]+=cnt[c[u][i]];
        }
    }
    while(cnt[u]>=k)
    {
        cnt[u]-=k;
        ans+=d;
    }
}

int main()
{
    int t;
    cin>>t;
    int tt=t;
    while(t--)
    {
        int n;
        node=1;
        cin>>n>>k;
        for(int i=0;i<n;i++)
        {
            string s;
            cin>>s;
            int u=0;
            for(char a:s)
            {
                if(!c[u][a-'A'])
                    c[u][a-'A']=node++;
                u=c[u][a-'A'];
            }
            ++cnt[u];
        }
        ans=0;
        dfs();
        cout<<"Case #"<<tt-t<<": "<<ans<<endl;
        memset(c,0,node* sizeof(c[0]));
        memset(cnt,0,node*4);
    }
}
