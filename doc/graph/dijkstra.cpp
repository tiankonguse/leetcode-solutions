#include "base.h"

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define trav(a, x) for(auto& a : x)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
#define subnb true
#define Lnb true
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef vector<int> vi;
const ll INF = (ll)1e18;

struct Edge {
    int to, cost;
};
vector<ll> Dijkstra(int s, int n, vector<vector<Edge>> &S) {
    vector<ll> dist(n, INF);
    dist[s] = 0;
    priority_queue<pll, vector<pll>, greater<pll> > pque;
    pque.push({0, s});
    while(!pque.empty()) {
        auto p = pque.top(); pque.pop();
        ll v = p.second, d = p.first;
        if(dist[v] < d) continue;
        for (auto &e : S[v]) {
            if(dist[e.to] > dist[v] + e.cost) {
                dist[e.to] = dist[v] + e.cost;
                pque.push({dist[e.to], e.to});
            }
        }
    }
    return dist;
}