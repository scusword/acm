#include <iostream>
#include <map>
#include <string>
#include <queue>
#include <stack>

const int dx[] = {-1, 1, 0, 0};
const int dy[] = {0, 0, -1, 1};
const char dd[] = {'u', 'd', 'l', 'r'};

inline void swap(std::string& s, int p1, int p2) {
    char t = s[p1];
    s[p1] = s[p2];
    s[p2] = t;
}

bool BFS(const std::string& init_state) {
    std::map<std::string, std::pair<std::string, char>> states;
    std::queue<std::string> q;
    std::string final_state("12345678x");
    int next_x, next_y;
    int x, y;
    q.push(std::string(init_state));
    states.insert(std::make_pair(init_state, std::make_pair(init_state, 'x')));

    while (!q.empty()) {
        std::string& curr = q.front();
        if (final_state == curr) {
            std::stack<char> sk;
            auto iter = states.find(curr);
            for (;;) {
                if (iter->first == iter->second.first) {
                    break;
                }
                sk.push(iter->second.second);
                iter = states.find(iter->second.first);
            }
            while (!sk.empty()) {
                std::cout<<sk.top();
                sk.pop();
            }
            std::cout<<std::endl;
            return true;
        }
        int pos = 0;
        for (; pos < 9; pos++) {
            if (curr[pos] == 'x') {
                break;
            }
        }
        x = pos / 3;
        y = pos % 3;
        for (int i = 0; i < 4; i++) {
            next_x = x + dx[i];
            next_y = y + dy[i];
            if (next_x >= 0 && next_x < 3 &&
                next_y >= 0 && next_y < 3) {

                int new_pos = next_x * 3 + next_y;
                std::string new_state(curr);
                swap(new_state, pos, new_pos);
                if (states.find(new_state) == states.end()) {
                    q.push(new_state);
                    states.insert(std::make_pair(new_state, std::make_pair(curr, dd[i])));
                }
            }
        }
        q.pop();
    }
    return false;
}

int main() {
    std::string s("23415x768");
    std::cout<<BFS(s)<<std::endl;
    return 0;
}