/*

Problem Description
省政府“畅通工程”的目标是使全省任何两个村庄间都可以实现公路交通（但不一定有直接的公路相连，只要能间接通过公路可达即可）。现得到城镇道路统计表，表中列出了任意两城镇间修建道路的费用，以及该道路是否已经修通的状态。现请你编写程序，计算出全省畅通需要的最低成本。
 

Input
测试输入包含若干测试用例。每个测试用例的第1行给出村庄数目N ( 1< N < 100 )；随后的 N(N-1)/2 行对应村庄间道路的成本及修建状态，每行给4个正整数，分别是两个村庄的编号（从1编号到N），此两村庄间道路的成本，以及修建状态：1表示已建，0表示未建。

当N为0时输入结束。
 

Output
每个测试用例的输出占一行，输出全省畅通需要的最低成本。
 

Sample Input
3
1 2 1 0
1 3 2 0
2 3 4 0
3
1 2 1 0
1 3 2 0
2 3 4 1
3
1 2 1 0
1 3 2 1
2 3 4 1
0
 

Sample Output
3
1
0

*/

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

