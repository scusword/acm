#include <stdio.h>

int BOARD[1000][1000];
int N, M;
int Q;
int x1, y1, x2, y2;

int DIRECTIONS_X[] = {-1, 1, 0, 0};
int DIRECTIONS_Y[] = {0, 0, -1, 1};

bool SUCC;
bool DFS(int x, int y, int d, int cnt) {
    if (cnt > 2) {
        return false;
    }

    if (x == x2 && y == y2) {
        return true;
    }
    int next_x, next_y;
    for (int i = 0; i < 4; i++) {
        next_x = x + DIRECTIONS_X[i];
        next_y = y + DIRECTIONS_Y[i];
        if (next_x >= 0 && next_x < N &&
            next_y >= 0 && next_y < M &&
            (BOARD[next_x][next_y] == 0 || (next_x == x2 && next_y == y2))) {
                char c = BOARD[next_x][next_y];
                BOARD[next_x][next_y] = -1;
                bool r = DFS(next_x, next_y, i, i != d ? cnt + 1 : cnt);
                BOARD[next_x][next_y] = c;
                if (r) {
                    return true;
                }
        }
    }
    return false;
}

int main() {
    while (scanf("%d %d\n", &N, &M) != EOF) {
        if (N + M == 0) {
            break;
        }
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                scanf("%d", &BOARD[i][j]);
            }
        }
        scanf("%d", &Q);
        while (Q--) {
            scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
            x1--;
            y1--;
            x2--;
            y2--;
            SUCC = false;
            if (BOARD[x1][y1] == BOARD[x2][y2] && BOARD[x1][y1] && BOARD[x2][y2]) {
                SUCC = DFS(x1, y1, -1, -1);
            }
            if (SUCC) {
                printf("YES\n");
            } else {
                printf("NO\n");
            }
        }
    }
    return 0;
}