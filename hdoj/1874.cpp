#include <iostream>
#include <cstring>
#include <algorithm>

const int MAX_DISTANCE = 0x7FFFFFFF;

int villages[205][205];
bool flag[205];

int min_distances[205];
int N, M;
int S, T;

int current_distance;
int current_min_distance;
bool no_path;

int dijkstra(int s, int e, int n) {
    for (int i = 0; i < n; i++) {
        min_distances[i] = MAX_DISTANCE;
        flag[i] = false;
    }
    min_distances[s] = 0;
    int min_node;
    for (;;) {
        min_node = -1;
        for (int j = 0; j < n; j++) {
            if (!flag[j] && (min_node == -1 || min_distances[j] < min_distances[min_node])) {
                min_node = j;
            }
        }
        if (min_node == -1) {
            break;
        }
        flag[min_node] = true;
        for (int j = 0; j < n; j++) {
            if (villages[min_node][j] != MAX_DISTANCE) {
                min_distances[j] = std::min(min_distances[j], min_distances[min_node] + villages[min_node][j]);
            }
        }
    }
    return min_distances[e] == MAX_DISTANCE ? -1 : min_distances[e];
}
/*time out*/
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
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                villages[i][j] = i == j ? 0 : MAX_DISTANCE;
            }
        }
        //memset(flag, 0, sizeof(flag));
        //current_distance = 0;
        //current_min_distance = 0x7fffffff;
        //no_path = true;
        while (M--) {
            std::cin>>a>>b>>x;
            if (x < villages[a][b]) {
                villages[a][b] = x;
                villages[b][a] = x;
            }
        }
        std::cin>>S>>T;
        // dfs_search(S);
        // no_path ? std::cout<<-1 : std::cout<<current_min_distance;
        int d = dijkstra(S, T, N);
        std::cout<<d<<std::endl;
    }
    return 0;
}