#include <iostream>

bool FLAG[50][50] = {false};
int N;
int count;

int result[10] = {0};

inline bool can_place(int x, int y) {
    for (int i = 0; i < y; i++) {
        if (FLAG[x][i]) {
            return false;
        }
    }
    for (int i = x - 1, j = y - 1; i >= 0 && j >= 0; i--, j--) {
        if (FLAG[i][j]) {
            return false;
        }
    }
    for (int i = x + 1, j = y - 1; i < N && j >= 0; i++, j--) {
        if (FLAG[i][j]) {
            return false;
        }
    }
    return true;
}

void DFS(int n) {
    if (n >= N) {
        count++;
        return;
    }
    for (int i = 0; i < N; i++) {
        if (can_place(i, n)) {
            FLAG[i][n] = true;
            DFS(n + 1);
            FLAG[i][n] = false;
        }
    }
}

int main() {
    for (int i = 1; i <= 10; i++) {
        count = 0;
        N = i;
        DFS(0);
        result[i] = count;
    }
    while (std::cin>>N && N != 0) {
        std::cout<<result[N]<<std::endl;
    }
    return 0;
}