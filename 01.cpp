# Du-tuyen-06-02

#include <bits/stdc++.h>
using namespace std;

typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;

int main()
{
    int n, m, s, u, v, w;
    vector<vii> AdjList;

    cin >> n >> m; s=0;

    vector<int> trace(n,-1);
    AdjList.assign(n, vii());
    for (int i = 0; i < m; i++)
    {
        cin >> u >> v >> w;
        AdjList[u-1].push_back(ii(v-1, w));
        AdjList[v-1].push_back(ii(u-1, w));
        trace[u-1]=v-1;
        trace[v-1]=u-1;
    }
    trace[s]=s;

    // Dijkstra routine
    vi dist(n, 1e9); dist[s] = 0;
    priority_queue< ii, vector<ii>, greater<ii> > pq; pq.push(ii(0, s));
    while (!pq.empty())
    {
        ii front = pq.top(); pq.pop();
        int d = front.first, u = front.second;
        if (d == dist[u])
        for (int j = 0; j < (int)AdjList[u].size(); j++)
        {
            ii v = AdjList[u][j];
            if (dist[u] + v.second < dist[v.first])
            {
                dist[v.first] = dist[u] + v.second;
                pq.push(ii(dist[v.first], v.first));
                trace[v.first]=u;
            }
        }
    }
    int dt = dist[n-1];

    stack<int> road; road.push(n-1);
    int t = trace[n-1];
    while (t != s)
    {
        road.push(t);
        t = trace[t];
    }
    road.push(0);

    int mx = 0;
    while (road.size() > 1)
    {
        int u = road.top();
        road.pop();
        int v = road.top();
        int vv;
        for (int j = 0; j < (int)AdjList[u].size(); j++)
            if (AdjList[u][j].first==v)
            {
                AdjList[u][j].second*=2;
                vv=j;
            }

        // Dijkstra again
        vi dist(n, 1e9); dist[s] = 0;
        priority_queue< ii, vector<ii>, greater<ii> > pq; pq.push(ii(0, s));
        while (!pq.empty())
        {
            ii front = pq.top(); pq.pop();
            int d = front.first, u = front.second;
            if (d == dist[u])
            for (int j = 0; j < (int)AdjList[u].size(); j++)
            {
                ii v = AdjList[u][j];
                if (dist[u] + v.second < dist[v.first])
                {
                    dist[v.first] = dist[u] + v.second;
                    pq.push(ii(dist[v.first], v.first));
                }
            }
        }
        if (dist[n-1]-dt > mx) mx = dist[n-1]-dt;
        AdjList[u][vv].second/=2;
    }
    cout << mx;
    return 0;
}
