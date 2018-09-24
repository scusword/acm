#include <iostream>
#include <cstring>
#include <queue>
#include <algorithm>
#include <cstdio>

int p[100];
int rank[100];
int villages[100][100];

struct road {
    int v, u, cost;
};

bool road_comp(const road& r1, const road& r2) {
    return r1.cost < r2.cost;
}

road roads[5005];

inline void init_union_set(int n) {
    for (int i = 0; i < n; i++) {
        p[i] = i;
        rank[i] = 1;
    }
}

int find(int x) {
    if (p[x] == x) {
        return x;
    }
    return p[x] = find(p[x]);
}

bool is_same_group(int x, int y) {
    return find(x) == find(y);
}

void merge(int x, int y) {
    int px = find(x);
    int py = find(y);
    if (px == py) {
        return;
    }
    if (rank[px] > rank[py]) {
        p[py] = px;
    } else {
        p[px] = py;
        if (rank[px] == rank[py]) {
            rank[py]++;
        }
    }
}

int kruskal2(int roads_cnt) {
    int min_cost = 0;
    std::sort(roads, roads + roads_cnt, road_comp);

    for (int i = 0; i < roads_cnt; i++) {
        if (!is_same_group(roads[i].v, roads[i].u)) {
            merge(roads[i].v, roads[i].u);
            min_cost += roads[i].cost;
        }
    }
    return min_cost;
}

/*
int kruskal(int n) {
    int min_cost = 0;
    std::priority_queue<road> q;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (villages[i][j] != 0 && !is_same_group(i, j)) {
                q.push(road(i, j, villages[i][j]));
            }
        }
    }

    while (!q.empty()) {
        const road& r = q.top();
        if (!is_same_group(r.v, r.u)) {
            min_cost += r.cost;
            merge(r.v, r.u);
        }
        q.pop();
    }
    return min_cost;
}
*/

int main() {
    int N, a, b, c, d;
    while (scanf("%d", &N) && N) {
        int t = N * (N - 1) / 2;
        int road_cnt = 0;
        //memset(villages, 0, sizeof(villages));
        init_union_set(N);
        while (t--) {
            scanf("%d %d %d %d", &a, &b, &c, &d);
            a--;
            b--;
            if (d == 1) {
                merge(a, b);
            } else {
                roads[road_cnt].v = a;
                roads[road_cnt].u = b;
                roads[road_cnt++].cost  = c;
            }
        }
        std::cout<<kruskal2(road_cnt)<<std::endl;
    }
    return 0;
}

