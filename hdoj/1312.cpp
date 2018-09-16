#include <stdio.h>

char ROOM[20][20];

int DIRECTIONS_X[] = {-1, 1, 0, 0};
int DIRECTIONS_Y[] = {0, 0, -1, 1};

int W, H;
int COUNT = 0;
void DFS(int x, int y) {
    int next_x, next_y;
    COUNT++;
    ROOM[x][y] = '#';
    for (int i = 0; i < 4; i++) {
        next_x = x + DIRECTIONS_X[i];
        next_y = y + DIRECTIONS_Y[i];
        if (next_x >= 0 && next_x < W &&
            next_y >= 0 && next_y < H &&
            ROOM[next_x][next_y] == '.') {
                DFS(next_x, next_y);
        }
    }
}

int main() {
    int start_x, start_y;
    while (scanf("%d %d\n", &H, &W) != EOF) {
        if (W + H == 0) {
            break;
        }
        for (int i= 0; i < W; i++) {
            scanf("%s\n", ROOM[i]);
        }
        for (int i = 0; i < W; i++) {
            for (int j = 0; j < H; j++) {
                if (ROOM[i][j] == '@') {
                    start_x = i;
                    start_y = j;
                }
            }
        }
        COUNT = 0;
        DFS(start_x, start_y);
        printf("%d\n", COUNT);
    }
    return 0;
}