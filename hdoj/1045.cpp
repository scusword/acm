#include <iostream>

char MAP[5][5];

int current_max;
int count;
int N;

bool can_place(int x, int y) {
    if (MAP[x][y] == 'X') {
        return false;
    }
    for (int i = x - 1; i >= 0 && MAP[i][y] != 'X'; i--) {
        if (MAP[i][y] == 'G') {
            return false;
        }
    }
    for (int i = x + 1; i < N && MAP[i][y] != 'X'; i++) {
        if (MAP[i][y] == 'G') {
            return false;
        }
    }
    for (int i = y - 1; i >= 0 && MAP[x][i] != 'X'; i--) {
        if (MAP[x][i] == 'G') {
            return false;
        } 
    }
    for (int i = y + 1; i < N && MAP[x][i] != 'X'; i++) {
        if (MAP[x][i] == 'G') {
            return false;
        }
    }
    return true;
}

void DFS(int n) {
    if (n == N * N) {
        if (count > current_max) {
            current_max = count;
        }
        return;
    }
    int x = n / N, y = n % N;
    if (can_place(x, y)) {
        MAP[x][y] = 'G';
        count++;
        DFS(n + 1);
        MAP[x][y] = '.';
        count--;
    }
    DFS(n + 1);
}

int main() {
    while (std::cin>>N && N != 0) {
        std::cin.get();
        for (int i = 0; i < N; i++) {
            std::cin.getline(MAP[i], 5);
        }
        current_max = 0;
        count = 0;
        DFS(0);
        std::cout<<current_max<<std::endl;
    }
    return 0;
}