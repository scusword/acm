#include <iostream>
#include <string.h>
#include <stdio.h>

char SODUKU_GRID[9][9];

bool MAP_X[9][9];
bool MAP_Y[9][9];
bool MAP_BLOCK[9][9];
bool found_solution = false;
bool first_solution = true;

inline bool can_place(int x, int y, char i) {
    char index = i - '1';
    if (MAP_X[x][index]) {
        return false;
    }
    if (MAP_Y[y][index]) {
        return false;
    }
    int block_index = (x / 3) * 3 + y / 3;
    if (MAP_BLOCK[block_index][index]) {
        return false;
    }
    return true;
}

inline void place_or_unplace(int x, int y, char i, bool place) {
    place ? SODUKU_GRID[x][y] = i : SODUKU_GRID[x][y] = '?';
    char index = i - '1';
    MAP_X[x][index] = place;
    MAP_Y[y][index] = place;
    MAP_BLOCK[(x / 3) * 3 + y / 3][index] = place;
}

void dump() {
    if (first_solution == false) {
        std::cout<<std::endl;
    } else {
        first_solution = false;
    }
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            j != 0 ? std::cout<<' '<<SODUKU_GRID[i][j] : std::cout<<SODUKU_GRID[i][j];
        }
        std::cout<<std::endl;
    }
}

void dfs_search(int n) {
    if (n == 81) {
        found_solution = true;
        dump();
        return;
    }
    int x = n / 9, y = n % 9;
    if (SODUKU_GRID[x][y] != '?') {
        dfs_search(n + 1);
    } else {
        for (char i = '1'; i <= '9'; i++) {
            if (can_place(x, y, i)) {
                place_or_unplace(x, y, i, true);
                dfs_search(n + 1);
                if (found_solution) {
                    break;
                }
                place_or_unplace(x, y, i, false);
            }
        }
    }
}

int main() {
    char c;
    do {
        memset(MAP_X, 0, sizeof(MAP_X));
        memset(MAP_Y, 0, sizeof(MAP_Y));
        memset(MAP_BLOCK, 0, sizeof(MAP_BLOCK));
        found_solution = false;
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                std::cin>>c;
                place_or_unplace(i, j, c, c != '?');
            }
        }
        dfs_search(0);
    } while (std::cin.get() != EOF);
}