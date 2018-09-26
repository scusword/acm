#include <cstdio>
#include <vector>
#include <queue>
#include <cstring>
#include <iostream>

struct road {
    int to, dist;
    road() : to(0), dist(0) {}
    road(int _to, int _dist) : to(_to), dist(_dist) {}

    bool operator<(const road& r) const {
        return dist > r.dist;
    }
};

std::priority_queue<road> villiages[26];
bool marked[26];

int prim(int n) {
    int min_cost, total_min_cost = 0;
    memset(marked, 0, sizeof(marked));
    marked[0] = true;
    for (int i = 1; i < n; i++) {
        int min_cost = 0x7FFFFFFF;
        int u = -1;
        for (int j = 0; j < n; j++) {
            if (marked[j] && !villiages[j].empty()) {
                while (!villiages[j].empty()) {
                    if (marked[villiages[j].top().to]) {
                        villiages[j].pop();
                        continue;
                    }
                    if (min_cost > villiages[j].top().dist) {
                        min_cost = villiages[j].top().dist;
                        u = j;
                    }
                    break;
                }
            }
        }
        if (u == -1) {
            break;
        }
        marked[villiages[u].top().to] = true;
        total_min_cost += min_cost;
        villiages[u].pop(); 
    }
    return total_min_cost;
}

int main() {
    int t;
    while (scanf("%d", &t) != EOF && t != 0) {
        int n = t--;
        while (t--) {
            char u, v;
            int c, d;
            //scanf("%c %d", &u, &c);
            std::cin>>u>>c;
            while (c--) {
                //scanf("%c %d", &v, &d);
                std::cin>>v>>d;
                villiages[u - 'A'].push(road(v - 'A', d));
                villiages[v - 'A'].push(road(u - 'A', d));
            }
        }
        printf("%d\n", prim(n));
        for (int i = 0; i < 26; i++) {
            while (!villiages[i].empty()) {
                villiages[i].pop();
            }
        }
    }
    return 0;
}