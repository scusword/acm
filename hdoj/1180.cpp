#include <cstdio>
#include <iostream>
#include <cstring>
#include <queue>

char MAP[25][25];
int M, N;

struct state {
    char x, y;
    int t;
    state(char _x, char _y, int _t) : x(_x), y(_y), t(_t) {}
    bool operator<(const state& s) const {
        return t > s.t;
    }
};

int dx[] = {-1, 1, 0, 0};
int dy[] = {0, 0, -1, 1};
char ds[] = {'|', '|', '-', '-'};

int bfs(char start_x, char start_y, char end_x, char end_y) {
    static bool state_map[25][25][2];
    memset(state_map, 0, sizeof(state_map));
    std::priority_queue<state> q;
    q.push(state(start_x, start_y, 0));
    char next_x, next_y;
    char next_f = 0;
    int time = 0;
    while (!q.empty()) {
        const state& s = q.top();
        if (s.x == end_x && s.y == end_y) {
            time = s.t;
            break;
        }
        for (int i = 0; i < 4; i++) {
            next_x = s.x + dx[i];
            next_y = s.y + dy[i];
            if (next_x < 0 || next_x >= M ||
                next_y < 0 || next_y >= N ||
                MAP[next_x][next_y] == '*') {
                continue;
            }
            if (MAP[next_x][next_y] != '.') {
                if (s.t % 2 == 0) {
                    if (MAP[next_x][next_y] != ds[i]) {
                        continue;
                    }
                } else {
                    if (MAP[next_x][next_y] == ds[i]) {
                        continue;
                    }
                }
                next_x += dx[i];
                next_y += dy[i];
                if (next_x < 0 || next_x >= M ||
                    next_y < 0 || next_y >= N ||
                    MAP[next_x][next_y] == '*') {
                        continue;
                }   
            }
            next_f = (s.t + 1) % 2;
            if (state_map[next_x][next_y][next_f]) {
                continue;
            }
            state_map[next_x][next_y][next_f] = true;
            q.push(state(next_x, next_y, s.t + 1));
        }
        q.pop();
    }
    return time;
}

int main() {
    int start_x, start_y, end_x, end_y;
    while (std::cin>>M>>N) {
        for (int i = 0; i < M; i++) {
            for (int j = 0; j < N; j++) {
                char c;
                //scanf("%c", &c);
                std::cin>>c;
                if (c == 'S') {
                    start_x = i;
                    start_y = j;
                    c = '.';
                } else if (c == 'T') {
                    end_x = i;
                    end_y = j;
                    c = '.';
                }
                MAP[i][j] = c;
            }
        }
        printf("%d\n", bfs(start_x, start_y, end_x, end_y));
    }
    return 0;
}
