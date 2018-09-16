#include <stdio.h>
#include <string.h>

bool PRIME_TABLE[40] = {false};
bool FLAG[21] = {false};
int NUMS[21];
int N;

inline void swap(int& a, int& b) {
    int t = a;
    a = b;
    b = t;
}

inline bool is_prime(int x) {
    return PRIME_TABLE[x];
}

void DFS(int x) {
    if (x > N) {
        if (x == 1 || is_prime(NUMS[x - 1] + NUMS[1])) {
            printf("%d", 1);
            for (int i = 2; i <= N; i++) {
                printf(" %d", NUMS[i]);
            }
            printf("\n");
        }
        return;
    }
    for (int i = 2; i <= N; i++) {
        if (FLAG[i] == false && is_prime(i + NUMS[x - 1])) {
            FLAG[i] = true;
            NUMS[x] = i;
            DFS(x + 1);
            FLAG[i] = false;
        }
    }
}

int main() {
    PRIME_TABLE[2] = true;
    PRIME_TABLE[3] = true;
    PRIME_TABLE[5] = true;
    PRIME_TABLE[7] = true;
    PRIME_TABLE[11] = true;
    PRIME_TABLE[13] = true;
    PRIME_TABLE[17] = true;
    PRIME_TABLE[19] = true;
    PRIME_TABLE[23] = true;
    PRIME_TABLE[29] = true;
    PRIME_TABLE[31] = true;
    PRIME_TABLE[37] = true;
    FLAG[1] = true;
    int cnt = 1;
    NUMS[1] = 1;
    while (scanf("%d", &N) != EOF) {
        memset(FLAG, 0, sizeof(FLAG));
        printf("Case %d:\n", cnt++);
        DFS(2);
        printf("\n");
    }
    return 0;
}
