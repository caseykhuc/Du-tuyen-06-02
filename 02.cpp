# Du-tuyen-06-02

#include <bits/stdc++.h>
using namespace std;

typedef pair<int, int> ii;
typedef pair<int, ii> iii;
typedef vector<int> vi;
typedef vector<ii> vii;
typedef vector<iii> viii;

int main()
{
    int n, m, s, u, v, w,x;
    vector<viii> AdjList;

    cin >> n >> m >> x; s=0;

    vector<int> c(m);
    AdjList.assign(n, viii());
    for (int i = 0; i < m; i++)
    {
        cin >> u >> v >> w >> c[i];
        AdjList[u-1].push_back(iii(v-1, ii(w,c[i])));
        AdjList[v-1].push_back(iii(u-1, ii(w,c[i])));
    }
    long mn=1e9;

    for (int i = 0; i < m; ++i)
    {
        // Dijkstra
        vi dist(n, 1e9); dist[s] = 0;
        priority_queue< ii, vector<ii>, greater<ii> > pq; pq.push(ii(0, s));
        while (!pq.empty())
        {
            ii front = pq.top(); pq.pop();
            int d = front.first, u = front.second;
            if (d == dist[u])
            for (int j = 0; j < (int)AdjList[u].size(); j++)
            {
                iii v = AdjList[u][j];
                if (dist[u] + v.second.first < dist[v.first] && v.second.second >= c[i])
                {
                    dist[v.first] = dist[u] + v.second.first;
                    pq.push(ii(dist[v.first], v.first));
                }
            }
        }
        // --------------------------------------
        if (mn > dist[n-1] + x/c[i]) mn = dist[n-1] + x/c[i];
    }
    cout << mn;
    return 0;
}
