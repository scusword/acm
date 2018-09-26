/*

Problem Description
In 2100, since the sea level rise, most of the cities disappear. Though some survived cities are still connected with others, but most of them become disconnected. The government wants to build some roads to connect all of these cities again, but they don’t want to take too much money.  
 

Input
The first line contains the number of test cases.
Each test case starts with three integers: n, m and k. n (3 <= n <=500) stands for the number of survived cities, m (0 <= m <= 25000) stands for the number of roads you can choose to connect the cities and k (0 <= k <= 100) stands for the number of still connected cities.
To make it easy, the cities are signed from 1 to n.
Then follow m lines, each contains three integers p, q and c (0 <= c <= 1000), means it takes c to connect p and q.
Then follow k lines, each line starts with an integer t (2 <= t <= n) stands for the number of this connected cities. Then t integers follow stands for the id of these cities.
 

Output
For each case, output the least money you need to take, if it’s impossible, just output -1.
 

Sample Input
1
6 4 3
1 4 2
2 6 1
2 3 5
3 4 33
2 1 2
2 1 3
3 4 5 6
 

Sample Output
1

*/

#include <cstdio>
#include <queue>
#include <cstring>

int p[501];
int rank[501];
int cities[501][501];
int disconnected_city_cnt;

#define MAX 0x7FFFFFFF

struct road {
    int u, v, cost;
    road() : u(0), v(0), cost(0) {}
    road(int _u, int _v, int _cost) : u(_u), v(_v), cost(_cost) {}

    bool operator<(const road& r) const {
        return cost > r.cost;
    }
};

void init_union_set(int n) {
    for (int i = 0; i <= n; i++) {
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
    disconnected_city_cnt--;
    if (rank[px] > rank[py]) {
        p[py] = px;
    } else {
        p[px] = py;
        if (rank[px] == rank[py]) {
            rank[py]++;
        }
    }
}

int kruskal(int n) {
    std::priority_queue<road> q;
    for (int i = 1; i <=n; i++) {
        for (int j = i + 1; j <= n; j++) {
            if (cities[i][j] != MAX && !is_same_group(i, j)) {
                q.push(road(i, j, cities[i][j]));
            }
        }
    }
    int min_cost = 0;
    while (!q.empty()) {
        const road& r = q.top();
        if (!is_same_group(r.u, r.v)) {
            merge(r.u, r.v);
            min_cost += r.cost;
        }
        q.pop();
    }
    return disconnected_city_cnt == 1 ? min_cost : -1;
}

int main() {
    int t, n, m, k;
    scanf("%d", &t);
    while (t--) {
        scanf("%d %d %d", &n, &m, &k);
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                cities[i][j] = MAX;
            }
        }
        init_union_set(n);
        disconnected_city_cnt = n;
        while (m--) {
            int p, q, c;
            scanf("%d %d %d", &p, &q, &c);
            if (cities[p][q] > c) {
                cities[p][q] = cities[q][p] = c; 
            }
        }
        while (k--) {
            int x, first;
            scanf("%d %d", &x, &first);
            x--;
            while (x--) {
                int y;
                scanf("%d", &y);
                merge(first, y);
            } 
        }
        printf("%d\n", kruskal(n));
    }
    return 0;
}