#include<bits/stdc++.h>
using namespace std;
#define fast ios::sync_with_stdio(0), cout.tie(0), cin.tie(0);
typedef long long int ll;

ll N,Q;
vector<ll> adj[300005];
ll parent[300005][30];
ll depth[300005];
vector<ll> level[300005];
ll max_depth;
ll cnt[300005];
ll val_1x[300005];
ll val_11[300005];
ll max_level;
ll nodex,nodey;
        
void dfs(ll x, ll p)
{
    parent[x][0] = p;
    depth[x] = depth[p] + 1;
    
    level[depth[x]].push_back(x);
    if(depth[x] > max_depth)
        max_depth = depth[x];

    for(ll i = 0; i < adj[x].size(); i++)
    {
        if(adj[x][i] != p)
            dfs(adj[x][i], x);
    }
}

void calculate_no_of_nodes()
{
    for(ll i = max_depth; i >= 1; i--)
    {
        for(ll j = 0; j < level[i].size(); j++)
        {
            cnt[level[i][j]]++;
            cnt[ parent[ level[i][j] ][0] ] += cnt[ level[i][j] ];
        }
    }
    cnt[1] = N;
}

void cnt_1x(ll x, ll p)
{
    ll temp = val_1x[p];
    
    ll c = 0;
    ll cc = 0;
    
    for(ll i = 0; i < adj[x].size(); i++)
    {
        if(adj[x][i] != p)
        {
            ll t = cnt[adj[x][i]];
            c = c + t;
            t = (t*(t-1))/2;
            cc = cc + t;
        }
    }
    
    c++;
    c = (c * (c-1))/2;
    c = c - cc;
    temp = temp + c;
    
    if(x != 1)
    {
        c = cnt[p] - cnt[x] - 1;
        c = cnt[x] + (cnt[x]*c);
        temp = temp - c;
    }
    
    temp++;
    val_1x[x] = temp;
    
    for(ll i = 0; i < adj[x].size(); i++)
        if(adj[x][i] != p)  
            cnt_1x(adj[x][i] , x);
}

void cnt_11(int x, int p)
{
    ll temp = 0;
    ll c = 0;
    for(ll i = 0; i < adj[x].size(); i++)
    {
        ll t;
        if(adj[x][i] != p)
        {
            t = cnt[adj[x][i]];
            t =(t*(t-1))/2;
            c = c + t;
        }
        else
        {
            t = N-cnt[x];
            t = (t*(t-1))/2;
            c = c + t;
        }
    }
    
    temp = (N*(N-1))/2;
    temp = temp - c;
    temp++;
    val_11[x] = temp;
    
    for(ll i = 0; i < adj[x].size(); i++)
        if(adj[x][i] != p)
            cnt_11(adj[x][i], x);
}

ll LCA(ll u, ll v)
{
    if(u == v)
        return u;
        
    if(depth[u] > depth[v])
    {
        swap(u,v);
    }
        
    ll diff = depth[v] - depth[u];
    
    for(ll i = 0; i < max_level; i++)
    {
        if((diff >> i)&1)
        {
            v = parent[v][i];
        }
    }
    
    if(u == v)
        return u;
        
    for(ll i = max_level-1; i >= 0; i--)
    {
        if(parent[u][i] != parent[v][i])
        {
            u = parent[u][i];
            v = parent[v][i];
        }
    }
    return parent[u][0];
}

void sparse_matrix()
{
    for(ll i = 1; i < max_level; i++)
    {
        for(ll j = 1; j <= N; j++)
        {
            if(parent[j][i-1] != -1)
                parent[j][i] = parent[ parent[j][i-1] ][i-1];
        }
    }
}

ll find(ll x, ll y)
{
    ll diff = depth[x] - depth[y] - 1;
    for(ll i = 0; i < max_level; i++)
    {
        if((diff >> i)&1)
        {
            x = parent[x][i];
        }
    }
    return x;
}

void solve(ll u, ll v)
{
    ll lca = u;
    
    nodey = find(v, u);
    
    ll cnty = cnt[nodey];
    
    ll temp1 = val_11[lca];
    
    ll ans = 0;
    
    temp1 = temp1 - (cnty + cnty*(N-1-cnty));
    
    ans = ans + temp1;
    
    ll temp2 = val_1x[lca];
    
    temp2 = temp2 - (cnty + cnty * (cnt[lca]-1-cnty));
    
    ll temp3 = val_1x[v];
    
    temp3 = temp3 - temp2;
    
    ans = ans + temp3;
    
    cout << ans << "\n";
}

void solve1(ll u, ll v, ll lca)
{
    nodex = find(u, lca);
    nodey = find(v, lca);
    
    ll cntx = cnt[nodex];
    ll cnty = cnt[nodey];
    
    ll ans = 0;
    
    ll c = cntx + cnty;

    ll temp1 = val_11[lca];
    
    temp1 = temp1 - (c + (cntx*cnty) + c *(N - 1 - c));
    
    ans = ans + temp1;
    
    ll temp2 = val_1x[lca];
    
    temp2 = temp2 - (c + (cntx*cnty) + c * (cnt[lca] - 1 - c));
    
    ll temp3 = val_1x[u];
    
    temp3 = temp3 - temp2 - (cnty + cnty * (cnt[lca] - 1 - c));
    
    ll temp4 = val_1x[v];
    
    temp4 = temp4 - temp2 - (cntx + cntx * (cnt[lca] - 1 - c));
    
    ans = ans + temp3 + temp4;
    
    cout << ans << "\n";
}

void init()
{
    for(ll i = 0; i <= N; i++)
    {
        adj[i].clear();
        level[i].clear();
    }
    
    memset(depth,0,sizeof(depth));
    memset(parent,-1,sizeof(parent));
    memset(cnt,0,sizeof(cnt));
    memset(val_1x,0,sizeof(val_1x));
    memset(val_11,0,sizeof(val_11));
}

void input_tree()
{
    for(ll i = 0; i < N-1; i++)
    {
        ll u,v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
}

void query()
{
    while(Q--)
    {
        ll u,v;
        
        cin >> u >> v;
        
        if(u > v)
            swap(u,v);

        if(u == v)
            cout << val_11[u] << "\n";
        else if(u == 1)
            cout << val_1x[v] << "\n";
        else
        {
            ll lca = LCA(u,v);

            if(lca == u)
                solve(u,v);
            else if(lca == v)
                solve(v,u);
            else
                solve1(u,v,lca);
        }
    }
}

int main()
{
    fast
    
    int T;
    cin >> T;
    
    while(T--)
    {
        cin >> N >> Q;
        
        init();
        
        input_tree();
        
        max_depth = 0;
        depth[0] = depth[1] = -1;
        
        dfs(1,1);
    
        calculate_no_of_nodes();
        
        cnt_1x(1,1);
        
        cnt_11(1,1);
        
        max_level = log2(N)+1;
        sparse_matrix();
        
        query();
    }
}
