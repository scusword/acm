#include <stdio.h>

int M, N;
char LAND[100][100];
int DIRECTIONS_X[] = {-1, 1, 0, 0, -1, 1, -1, 1};
int DIRECTIONS_Y[] = {0, 0, -1, 1, -1, -1, 1, 1};

void DFS(int x, int y) {
    int next_x, next_y;
    LAND[x][y] = '*';
    for (int i = 0; i < 8; i++) {
        next_x = x + DIRECTIONS_X[i];
        next_y = y + DIRECTIONS_Y[i];
        if (next_x >= 0 && next_x < M &&
            next_y >= 0 && next_y < N &&
            LAND[next_x][next_y] == '@') {
                DFS(next_x, next_y);
            }
    }
}

int main() {
    int n;
    while (scanf("%d %d\n", &M, &N) != EOF) {
        if (M + N == 0) {
            break;
        }
        for (int i = 0; i < M; i++) {
            scanf("%s\n", LAND[i]);
        }
        n = 0;
        for (int i = 0; i < M; i++) {
            for (int j = 0; j < N; j++) {
                if (LAND[i][j] == '@') {
                    DFS(i, j);
                    n++;
                }
            }
        }
        printf("%d\n", n);
    }
}