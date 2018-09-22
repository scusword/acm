#include <iostream>

int p[100001];
int rank[100001];
bool flag[100001];

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

int main() {
    int a, b;
    bool is_right = true;
    int v_cnt = 0;
    int merge_cnt = 0;
    for (int i = 0; i < 100001; i++) {
        p[i] = i;
        rank[i] = 1;
    }
    while (std::cin>>a>>b && a != -1 && b != -1) {
        if (a == 0 && b == 0) {
            v_cnt == 0 || (is_right && v_cnt - 1 == merge_cnt) ? std::cout<<"Yes\n" : std::cout<<"No\n";
            is_right = true;
            v_cnt = 0;
            merge_cnt = 0;
            for (int i = 0; i < 100001; i++) {
                p[i] = i;
                rank[i] = 1;
                flag[i] = false;
            }
            continue;
        }
        if (flag[a] == false) {
            flag[a] = true;
            v_cnt++;
        }
        if (flag[b] == false) {
            flag[b] = true;
            v_cnt++;
        }
        if (is_right) {
            if (merge(a, b)) {
                merge_cnt++;
            } else {
                is_right = false;
            }
        }
    }
    return 0;
}