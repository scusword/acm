#include <iostream>
#include <vector>
#include <algorithm>

char castle[101][101];
int N, M;

int dx[] = {-1, 1, 0, 0};
int dy[] = {0, 0, -1, 1};

int current_cost;
int current_min_cost;
int current_step;
int min_step;
bool succ;

std::vector<std::pair<int, int>> current_path;
std::vector<std::pair<int, int>> min_cost_path;

void dfs_search(int x, int y) {
    if (current_min_cost <= current_cost) {
        return;
    }
    current_path[current_step++] = std::make_pair(x, y);
    if (x == N - 1 && y == M - 1) {
        if (current_cost < current_min_cost) {
            current_min_cost = current_cost;
            std::copy(current_path.begin(), current_path.begin() + current_step, min_cost_path.begin());
            succ = true;
            min_step = current_step;
        }
        current_step--;
        return;
    }
    char c = castle[x][y];
    castle[x][y] = 'G';
    int next_x, next_y;
    for (int i = 0; i < 4; i++) {
        next_x = x + dx[i];
        next_y = y + dy[i];
        if (next_x >= 0 && next_x < N &&
            next_y >= 0 && next_y < M &&
            castle[next_x][next_y] != 'X' &&
            castle[next_x][next_y] != 'G') {
            current_cost += 1 + castle[next_x][next_y] - '0';
            dfs_search(next_x, next_y);
            current_cost -= 1 + castle[next_x][next_y] - '0';
        }
    }
    castle[x][y] = c;
    current_step--;
}

int main() {
    char c;
    current_path.resize(100);
    min_cost_path.resize(100);
    while (std::cin>>N>>M) {
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                std::cin>>c;
                if (c == '.') {
                    c = '0';
                }
                castle[i][j] = c;
            }
        }
        current_cost = 0;
        current_step = 0;
        current_min_cost = 0x7FFFFFFF;
        succ = false;
        min_step = 0;
        dfs_search(0, 0);
        if (!succ) {
            std::cout<<"God please help our poor hero.\nFINISH\n";
        } else {
            std::cout<<"It takes "<<current_min_cost<<" seconds to reach the target position, let me show you the way.\n";
            int t = 1;
            int x, y;
            for (int i = 0; i < min_step; i++) {
                x = min_cost_path[i].first;
                y = min_cost_path[i].second;
                if (castle[x][y] != '0') {
                    int t1 = castle[x][y] - '0';
                    while (t1--) {
                        std::cout<<t++<<"s:FIGHT AT ("<<x<<','<<y<<")\n";
                    }
                }
                if (i + 1 < min_step) {
                    std::cout<<t++<<"s:"<<'('<<x<<','<<y<<")->("<<min_cost_path[i + 1].first<<','<<min_cost_path[i + 1].second<<")\n";
                }
            }
            std::cout<<"FINISH\n";
        }
    }
    return 0;
}