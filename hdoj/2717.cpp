#include <iostream>
#include <queue>
#include <cstring>

int N, K;
int actions[] = {-1, 1, 0};
bool table[100001];

inline bool is_valid_pos(int pos) {
    return pos >= 0 && pos <= 100000;
}

int bfs_search() {
    std::queue<std::pair<int, int> > q;
    q.push(std::make_pair(N, 0));
    table[N] = true;
    int r = -1;
    while (!q.empty()) {
        const std::pair<int, int>& pos = q.front();
        if (pos.first == K) {
            r = pos.second;
            break;
        }
        actions[2] = pos.first;
        int next_pos;
        for (int i = 0; i < 3; i++) {
            next_pos = pos.first + actions[i];
            if (is_valid_pos(next_pos) && table[next_pos] == false) {
                q.push(std::make_pair(next_pos, pos.second + 1));
                table[next_pos] = true;
            }
        }
        q.pop(); 
    }
    return r;
}

int main() {
    while (std::cin>>N>>K) {
        memset(table, 0, sizeof(table));
        std::cout<<bfs_search()<<std::endl;
    }
    return 0;
}
