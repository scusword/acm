#include <iostream>
#include <cstring>

int villages[200][200];
bool flag[200];

int N, M;
int S, T;

int current_distance;
int current_min_distance;
bool no_path;
void dfs_search(int x) {
    if (x == T) {
        if (current_distance < current_min_distance) {
            current_min_distance = current_distance;
        }
        no_path = false;
        return;
    }
    if (current_distance >= current_min_distance) {
        return;
    }
    flag[x] = true;
    for (int i = 0; i < N; i++) {
        if (flag[i] == false && villages[x][i]) {
            current_distance += villages[x][i];
            dfs_search(i);
            current_distance -= villages[x][i];
        }
    }
    flag[x] = false;
}

int main() {
    while (std::cin>>N>>M) {
        int a, b, x;
        memset(villages, 0, sizeof(villages));
        memset(flag, 0, sizeof(flag));
        current_distance = 0;
        current_min_distance = 0x7fffffff;
        no_path = true;
        while (M--) {
            std::cin>>a>>b>>x;
            villages[a][b] = x;
            villages[b][a] = x;
        }
        std::cin>>S>>T;
        dfs_search(S);
        no_path ? std::cout<<-1 : std::cout<<current_min_distance;
        std::cout<<std::endl;
    }
    return 0;
}