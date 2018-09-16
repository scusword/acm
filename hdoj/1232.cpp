#include <cstdio>
#include <cstring>

bool graph[1000][1000];
bool marked[1000];

int N, M;

void dfs_search(int n) {
    marked[n] = true;
    for (int i = 1; i <= N; i++) {
        if (marked[i] == false && graph[n][i] == true) {
            dfs_search(i);
        }
    }
}

int main() {
    int a, b;
    while (scanf("%d %d", &N, &M) != EOF && N != 0) {
        memset(graph, 0, sizeof(graph));
        memset(marked, 0, sizeof(marked));
        while (M--) {
            scanf("%d %d", &a, &b);
            graph[a][b] = true;
            graph[b][a] = true;
        }
        int cnt = 0;
        for (int i = 1; i <= N; i++) {
            if (marked[i] == false) {
                dfs_search(i);
                cnt++;
            }
        }
        printf("%d\n", cnt - 1);
    }
    return 0;
}