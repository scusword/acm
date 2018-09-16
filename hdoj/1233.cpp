#include <cstdio>
#include <cstring>
#include <cstdlib>

unsigned int graph[100][100];
bool mst_node_flag[100];
int mst_node[100];
int N;

unsigned int prim() {
    int mst_node_cnt = 0;
    unsigned int total_min_cost = 0;
    memset(mst_node_flag, 0, sizeof(mst_node_flag));

    mst_node[mst_node_cnt++] = 1;
    mst_node_flag[1] = true;
    while (true) {
        int min_cost = 0xFFFFFFFF;
        int min_node = -1;
        for (int i = 0; i < mst_node_cnt; i++) {
            for (int j = 1; j <= N; j++) {
                if (mst_node_flag[j] == false && graph[mst_node[i]][j] != 0) {
                    if (graph[mst_node[i]][j] < min_cost) {
                        min_cost = graph[mst_node[i]][j];
                        min_node = j;
                    } 
                }
            }
        }
        if (min_node == -1) {
            break;
        }
        mst_node[mst_node_cnt++] = min_node;
        mst_node_flag[min_node] = true;
        total_min_cost += min_cost;
    }
    return total_min_cost;
}

int main() {
    while (scanf("%d", &N) != EOF && N != 0) {
        memset(graph, 0, sizeof(graph));
        int a, b;
        unsigned int c;
        int d = N * (N - 1) / 2;
        while (d--) {
           scanf("%d %d %u", &a, &b, &c);
           graph[a][b] = c;
           graph[b][a] = c;
        }
        printf("%u\n", prim());
    }
    return 0;
}