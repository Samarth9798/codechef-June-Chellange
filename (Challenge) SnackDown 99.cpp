#include<bits/stdc++.h>
using namespace std;
#define fast ios::sync_with_stdio(0), cout.tie(0), cin.tie(0);
typedef long long int ll;

int N,M;
ll n[1000];
ll m[300000];
map<pair<int,int>, int> edge;

int main()
{
    fast
    
    cin >> N >> M;
    
    for(int i = 1; i <= N; i++)
        cin >> n[i];
        
    for(int i = 1; i <= M; i++)
        cin >> m[i];
        
    for(int i = 1; i <= M; i++)
    {
        int u,v;
        cin >> u >> v;
        
        edge[{u,v}] = i;
        edge[{v,u}] = i;
    }
    
    //dry run
    string ans = "";
    for(int i = 1; i <= N; i++)
    {
        if(i%2 == 1)
            ans = ans + "C";
        else
            ans = ans + "G";
    }
    
    vector<int> g,c;
    for(int i = 0; i < ans.size(); i++)
    {
        if(ans[i] == 'C')
            c.push_back(i+1);
        else
            g.push_back(i+1);
    }
    
    for(int i = 0; i < c.size(); i++)
    {
        for(int j = i+1; j < c.size(); j++)
        {
            int u = c[i];
            int v = c[j];
            
            if(edge.count({u,v}))
            {
                cout << edge[{u,v}] << endl << flush;
        
                int ty;
                cin >> ty;
                ll x,y;
                switch(ty)
                {
                    case 0: cin >> x >> y;
                            n[x] = y;
                            break;
                    case 1: cin >> x >> y;
                            m[x] = y;
                            break;
                    case 2: break;
                }
            }
        }
    }
    
    for(int i = 0; i < g.size(); i++)
    {
        for(int j = i+1; j < g.size(); j++)
        {
            int u = g[i];
            int v = g[j];
            
            if(edge.count({u,v}))
            {

                cout << edge[{u,v}] << endl << flush;
        
                int ty;
                cin >> ty;
                ll x,y;
                switch(ty)
                {
                    case 0: cin >> x >> y;
                            n[x] = y;
                            break;
                    case 1: cin >> x >> y;
                            m[x] = y;
                            break;
                    case 2: break;
                }
            }
        }
    }
    
    cout << "-1" << endl << flush;
    cout << ans << endl << flush;
}
