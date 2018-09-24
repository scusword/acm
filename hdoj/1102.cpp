/*
Problem Description
There are N villages, which are numbered from 1 to N, and you should build some roads such that every two villages can connect to each other. We say two village A and B are connected, if and only if there is a road between A and B, or there exists a village C such that there is a road between A and C, and C and B are connected. 

We know that there are already some roads between some villages and your job is the build some roads such that all the villages are connect and the length of all the roads built is minimum.
 

Input
The first line is an integer N (3 <= N <= 100), which is the number of villages. Then come N lines, the i-th of which contains N integers, and the j-th of these N integers is the distance (the distance should be an integer within [1, 1000]) between village i and village j.

Then there is an integer Q (0 <= Q <= N * (N + 1) / 2). Then come Q lines, each line contains two integers a and b (1 <= a < b <= N), which means the road between village a and village b has been built.
 

Output
You should output a line contains an integer, which is the length of all the roads to be built such that all the villages are connected, and this value is minimum. 
 

Sample Input
3
0 990 692
990 0 179
692 179 0
1
1 2
 

Sample Output
179
*/

#include <iostream>
#include <cstring>
#include <queue>

int villiages[101][101];

int p[101];
int rank[101];

int find(int x) {
    if (p[x] == x) {
        return x;
    }
    return p[x] = find(p[x]);
}

bool is_same_group(int x, int y) {
    return find(x) == find(y);
}

bool merge(int x, int y) {
    int px = find(x);
    int py = find(y);
    if (px == py) {
        return false;
    }
    if (rank[px] > rank[py]) {
        p[py] = px;
    } else {
        p[px] = py;
        if (rank[px] == rank[py]) {
            rank[py]++;
        }
    }
    return true;
}
struct edge {
    int u, v, cost;

    edge(int u, int v, int cost) {
        this->u = u;
        this->v = v;
        this->cost = cost;
    }

    bool operator<(const edge& e) const {
        return cost > e.cost;
    }
};

inline void init_union_set(int n) {
    for (int i = 1; i <= n; i++) {
        p[i] = i;
        rank[i] = 1;
    }
}

int kruskal(int n) {
    std::priority_queue<edge> queue;
    for (int i = 1; i <= n; i++) {
        for (int j = i + 1; j <= n; j++) {
            if (!is_same_group(i, j)) {
                queue.push(edge(i, j, villiages[i][j]));
            }
        }
    }
    int min_cost = 0;
    while (!queue.empty()) {
        const edge& e = queue.top();
        if (!is_same_group(e.u, e.v)) {
            merge(e.u, e.v);
            min_cost += e.cost;
        }
        queue.pop();
    }
    return min_cost;
}

int main() {
    int N;
    while (std::cin>>N) {
        init_union_set(N);
        for (int i = 1; i <= N; i++) {
            for (int j = 1; j <= N; j++) {
                int c;
                std::cin>>c;
                villiages[i][j] = c;
                villiages[j][i] = c;
            }
        }
        int a, b, Q;
        std::cin>>Q;
        while (Q--) {
            std::cin>>a>>b;
            merge(a, b);
        }
        std::cout<<kruskal(N)<<std::endl;
    }
    return 0;
}