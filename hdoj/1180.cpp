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

inline 
bool can_standby(int x, int y) {
    return !(x < 0 || x >= M || y < 0 || y >= N || MAP[x][y] == '*');
}

inline 
bool is_stairs(int x, int y) {
    return MAP[x][y] == '|' || MAP[x][y] == '-';
}

inline 
bool can_cross_stairs(int x, int y, int s_x, int s_y, bool changed) {
    if (!changed) {
        if ((x == s_x && MAP[s_x][s_y] == '-') ||
            (y == s_y && MAP[s_x][s_y] == '|')) {
            return true;
        }
    } else {
        if ((x == s_x && MAP[s_x][s_y] == '|') ||
            (y == s_y && MAP[s_x][s_y] == '-')) {
            return true;
        }
    }
    return false;
}

int bfs(char start_x, char start_y, char end_x, char end_y) {
    static bool state_map[25][25][2];
    memset(state_map, 0, sizeof(state_map));
    std::priority_queue<state> q;
    state_map[start_x][start_y][0] = true;
    q.push(state(start_x, start_y, 0));
    char next_x, next_y;
    int next_time;
    auto is_visited = [](int x, int y, int t)->bool {
        return state_map[x][y][t & 1];
    };

    while (!q.empty()) {
        state s = q.top();
        if (s.x == end_x && s.y == end_y) {
            return s.t;
        }
        for (int i = 0; i < 4; i++) {
            next_x = s.x + dx[i];
            next_y = s.y + dy[i];
            if (!can_standby(next_x, next_y)) {
                continue;
            }
            if (is_stairs(next_x, next_y)) {
                if (can_standby(next_x + dx[i], next_y + dy[i])) {
                    if (!can_cross_stairs(s.x, s.y, next_x, next_y, s.t & 1)) {
                        next_time = s.t + 1;
                        if (!is_visited(s.x, s.y, next_time)) {
                            state_map[s.x][s.y][(s.t + 1) & 1] = true;
                            q.push(state(s.x, s.y, s.t + 1));
                        }
                    } else {
                        next_x += dx[i];
                        next_y += dy[i];
                    }
                }
            }
            next_time = s.t + 1;
            if (!is_visited(next_x, next_y, next_time)) {
                state_map[next_x][next_y][next_time & 1] = true;
                q.push(state(next_x, next_y, next_time));
            }
        }
        q.pop();
    }
    return -1;
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
