#include <cstdio>
#include <cstring>
#include <algorithm>

int cookies[100001][13];
int dp[100001][13];
int dp_max[100001];

int main() {
    int N;
    int x, T, maxT;
    while (scanf("%d", &N) && N != 0) {
        memset(cookies, 0, sizeof(cookies));
        memset(dp, 0, sizeof(dp));
        memset(dp_max, 0, sizeof(dp_max));
        maxT = 0;
        for (int i = 0; i < N; i++) {
            scanf("%d %d", &x, &T);
            if (T > maxT) {
                maxT = T;
            }
            cookies[T][x + 1]++;
        }
        dp[1][5] = cookies[1][5];
        dp[1][7] = cookies[1][7];
        dp[1][6] = cookies[1][6];
        dp_max[1] = std::max(std::max(dp[1][5], dp[1][6]), dp[1][7]);
        for (int i = 2; i <= maxT; i++) {
            for (int j = 1; j < 12; j++) {
                dp[i][j] = cookies[i][j] + std::max(std::max(dp[i - 1][j], dp[i - 1][j - 1]), dp[i - 1][j + 1]);
                if (dp[i][j] > dp_max[i]) {
                    dp_max[i] = dp[i][j];
                }
            }
        }
        printf("%d\n", dp_max[maxT]);
    }
    return 0;
}