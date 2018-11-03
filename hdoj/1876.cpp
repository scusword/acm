#include <cstdio>

int chess_board[101][101];

int current_energy;
int no_energy_cnt;
int path_cnt;
int max_no_energy_cnt;

int n, m;

void dfs(int x, int y) {
    if (x > n || y > m) {
        return;
    }
    bool get_energy = false;
    if (current_energy == 0) {
        if (chess_board[x][y] > 0) {
            no_energy_cnt++;
            get_energy = true;
            current_energy = chess_board[x][y];
        } else {
            return;
        }
    }
    if (x == n && y == m) {
        printf("%d %d %d\n", no_energy_cnt, max_no_energy_cnt, path_cnt);
        if (no_energy_cnt >= max_no_energy_cnt) {
            no_energy_cnt == max_no_energy_cnt ? path_cnt++ : (max_no_energy_cnt = no_energy_cnt, path_cnt = 1);
        }
    } else {
        current_energy--;
        dfs(x, y + 1);
        dfs(x + 1, y);
        current_energy++;
    }
    if (get_energy) {
        no_energy_cnt--;
        current_energy = 0;
    }
}

int main() {
    int t;
    scanf("%d", &t);
    while (t--) {
        scanf("%d %d", &n, &m);
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                scanf("%d", &chess_board[i][j]);
            }
        }
        current_energy = chess_board[1][1];
        path_cnt = 0;
        no_energy_cnt = 0;
        max_no_energy_cnt = -1;
        dfs(1, 1);
        printf("%d %d\n", max_no_energy_cnt, path_cnt);
    }
    return 0;
}