#include <stdio.h>
char MAZE[8][8];

int DIRECTIONS_X[] = {-1, 1, 0, 0};
int DIRECTIONS_Y[] = {0, 0, -1, 1};

int N, M, T;
bool SUCC;
int start_x, start_y;
int exit_x, exit_y;

inline int my_abs(int v) {
    return v < 0 ? -v : v;
}

void DFS(int x, int y, int t) {
    if (MAZE[x][y] == 'D') {
        if (t == T) {
            SUCC = true;
        }
        return;
    }
    if (t >= T) {
        return;
    }
    int min_time = my_abs(x - exit_x) + my_abs(y - exit_y);
    if (min_time > T - t || (T - t - min_time) % 2) {
        return;
    }
    int next_x, next_y;
    for (int i = 0; i < 4; i++) {
        next_x = x + DIRECTIONS_X[i];
        next_y = y + DIRECTIONS_Y[i];
        if (next_x >= 0 && next_x < N &&
            next_y >= 0 && next_y < M &&
            MAZE[next_x][next_y] != 'X' &&
            MAZE[next_x][next_y] != 'H') {
            char c = MAZE[x][y];
            MAZE[x][y] = 'H';
            DFS(next_x, next_y, t + 1);
            MAZE[x][y] = c;
        }
    }
}

int main() {
    while (scanf("%d %d %d\n", &N, &M, &T) != EOF) {
        if (N + M + T == 0) {
            break;
        }
        for (int i = 0; i < N; i++) {
            scanf("%s\n", MAZE[i]);
        }
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                if (MAZE[i][j] == 'S') {
                    start_x = i;
                    start_y = j;
                } else if (MAZE[i][j] == 'D') {
                    exit_x = i;
                    exit_y = j;
                }
            }
        }
        SUCC = false;
        DFS(start_x, start_y, 0);
        if (SUCC) {
            printf("YES\n");
        } else {
            printf("NO\n");
        }
    }
}