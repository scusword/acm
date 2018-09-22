#include <iostream>
#include <map>

int p[1001];
int rank[1001];

int find(int x) {
    if (p[x] == x) {
        return x;
    }
    return p[x] = find(p[x]);
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
void init(int n) {
    for (int i = 0; i <= n; i++) {
        p[i] = i;
        rank[i] = 1;
    }
}

int main() {
    int t;
    std::cin>>t;
    int m, n, a, b;
    while (t--) {
        std::cin>>n>>m;
        init(n);
        while (m--) {
            std::cin>>a>>b;
            if (merge(a, b)) {
                n--;
            }
        }
        std::cout<<n<<std::endl;
    }
    return 0;
}