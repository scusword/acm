#include <stdio.h>

int n, m;

int Solve(int n, int m) {
    int a, b, c, answer_cnt = 0;
    for (a = 0; a <= n; a++) {
        for (b = 0; b <= n - a; b++) {
            for(c = 0; c <= n - b - a; c++) {
                if ((a + b + c) == n && (a + 2 * b + 5 * c) == m) {
                    answer_cnt++;
                }
            }
        }
    }
    return answer_cnt;
}

int main() {
    int cnt;
    scanf("%d", &cnt);
    while (cnt--) {
        scanf("%d %d", &n, &m);
        printf("%d\n", Solve(n, m));
    }
    return 0;
}