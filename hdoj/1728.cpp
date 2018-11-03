#include <iostream>
#include <queue>
#include <cstring>

char map[100][100];
int m, n;
bool yes;

int dx[] = {-1, 1, 0, 0};
int dy[] = {0, 0, -1, 1};

int start_x, start_y, finish_x, finish_y, max_turn_cnt;

struct bfs_state {
    char x;
    char y;
    char d;
    char turn_cnt;

    bfs_state(char _x, char _y, char _d, char _turn_cnt) :
        x(_x), y(_y), d(_d), turn_cnt(_turn_cnt) {}
};

bool bfs_search() {
    static bool bfs_state_map[100][100][4][10];
    memset(bfs_state_map, 0, sizeof(bfs_state_map));
    std::queue<bfs_state> q;
    q.push(bfs_state(start_x, start_y, 0, 0));
    q.push(bfs_state(start_x, start_y, 1, 0));
    q.push(bfs_state(start_x, start_y, 2, 0));
    q.push(bfs_state(start_x, start_y, 3, 0));
    int next_x, next_y, next_turn_cnt;
    bool bfs_yes = false; 
    while (!q.empty()) {
        const bfs_state& state = q.front();
        if (state.x == finish_x && state.y == finish_y) {
            bfs_yes = true;
            break;
        }
        for (int i = 0; i < 4; i++) {
            next_x = state.x + dx[i];
            next_y = state.y + dy[i];
            if (next_x >= 0 && next_x < m && 
                next_y >= 0 && next_y < n &&
                map[next_x][next_y] == '.') {
                if (i == state.d && !bfs_state_map[next_x][next_y][i][state.turn_cnt]) {
                    bfs_state_map[next_x][next_y][i][state.turn_cnt] = true;
                    q.push(bfs_state(next_x, next_y, i, state.turn_cnt));
                } else {
                    if (state.turn_cnt < max_turn_cnt && !bfs_state_map[next_x][next_y][i][state.turn_cnt + 1]) {
                        bfs_state_map[next_x][next_y][i][state.turn_cnt + 1] = true;
                        q.push(bfs_state(next_x, next_y, i, state.turn_cnt + 1));
                    }
                }
            }
        } 
        q.pop();
    }
    return bfs_yes;
}

void dfs_search(int x, int y, int d, int turn_cnt) {
    if (turn_cnt > max_turn_cnt) {
        return;
    }
    if (x == finish_x && y == finish_y) {
        yes = true;
        return;
    }
    if (turn_cnt == max_turn_cnt) {
        if (x != finish_x || y != finish_y) {
            return;
        }
    }
    int next_x, next_y;
    for (int i = 0; i < 4; i++) {
        next_x = x + dx[i];
        next_y = y + dy[i];
        if (next_x >= 0 && next_x < m && next_y >= 0 && next_y < n &&
            map[next_x][next_y] == '.') {
            map[next_x][next_y] = 'G';
            dfs_search(next_x, next_y, i, i == d ? turn_cnt : turn_cnt + 1);
            map[next_x][next_y] = '.';
            if (yes) {
                break;
            }
        }
    }
}

int main() {
    int t;
    std::cin>>t;
    while (t--) {
        std::cin>>m>>n;
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                std::cin>>map[i][j];
            }
        }
        std::cin>>max_turn_cnt>>start_y>>start_x>>finish_y>>finish_x;
        start_x--;
        start_y--;
        finish_x--;
        finish_y--;
        yes = false;
        //dfs_search(start_x, start_y, -1, -1);
        bfs_search() ? std::cout<<"yes\n" : std::cout<<"no\n";
    }
    return 0;
}
