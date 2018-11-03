#include <cstdio>

long long fib_table[1000000];

void init_table() {
    fib_table[0] = 7;
    fib_table[1] = 11;
    for (int i = 2; i < 1000000; i++) {
        fib_table[i] = fib_table[i - 1] + fib_table[i - 2];
    }
}

long long F(int x) {
    return fib_table[x];
}

int main() {
    int x;
    init_table();
    while (scanf("%d", &x) != EOF) {
        F(x) % 3 ? printf("no\n") : printf("yes\n");
    }
    return 0;
}