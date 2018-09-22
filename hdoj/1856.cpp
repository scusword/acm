#include <iostream>
#include <map>

int p[10000001];
int current_max;
/*cnt, depth*/
std::map<int, std::pair<int, int> > state;

int find(int x) {
    if (p[x] == x) {
        return x;
    }
    return p[x] = find(p[x]);
}

void merge(int x, int y) {
    int px = find(x);
    int py = find(y);
    if (px != py) {
        auto iter_x = state.find(px);
        auto iter_y = state.find(py);
        auto iter = state.end();
        if (iter_x == state.end() && iter_y == state.end()) {
            p[px] = py;
            state.insert(std::make_pair(py, std::make_pair(2, 2)));
            iter = state.find(py);
        } else if (iter_x != state.end() && iter_y == state.end()) {
            p[py] = px;
            iter_x->second.first++;
            iter = iter_x;
        } else if (iter_x == state.end() && iter_y != state.end()) {
            p[px] = py;
            iter_y->second.first++;
            iter = iter_y;
        } else {
            if (iter_x->second.second > iter_y->second.second) {
                p[py] = px;
                iter_x->second.first += iter_y->second.first;
                state.erase(iter_y);
                iter = iter_x;
            } else {
                p[px] = py;
                iter_y->second.first += iter_x->second.first;
                if (iter_x->second.second == iter_y->second.second) {
                    iter_y->second.second++;
                }
                state.erase(iter_x);
                iter = iter_y;
            }
        }
        if (iter->second.first > current_max) {
            current_max = iter->second.first;
        }
    }
}

void init() {
    for (int i = 0; i < 10000001; i++) {
        p[i] = i;
    }
    state.clear();
}
int main() {
    int n;
    int a, b;
    while (std::cin>>n) {
        if (n == 0) {
            std::cout<<1<<std::endl;
            continue;
        }
        current_max = 0;
        init();
        while (n--) {
            std::cin>>a>>b;
            merge(a, b);
        }
        std::cout<<current_max<<std::endl;
    }
    return 0;
}