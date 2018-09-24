/*

Problem Description
省政府“畅通工程”的目标是使全省任何两个村庄间都可以实现公路交通（但不一定有直接的公路相连，只要能间接通过公路可达即可）。经过调查评估，得到的统计表中列出了有可能建设公路的若干条道路的成本。现请你编写程序，计算出全省畅通需要的最低成本。
 

Input
测试输入包含若干测试用例。每个测试用例的第1行给出评估的道路条数 N、村庄数目M ( < 100 )；随后的 N 
行对应村庄间道路的成本，每行给出一对正整数，分别是两个村庄的编号，以及此两村庄间道路的成本（也是正整数）。为简单起见，村庄从1到M编号。当N为0时，全部输入结束，相应的结果不要输出。
 

Output
对每个测试用例，在1行里输出全省畅通需要的最低成本。若统计数据不足以保证畅通，则输出“?”。
 

Sample Input
3 3
1 2 1
1 3 2
2 3 4
1 3
2 3 2
0 100
 

Sample Output
3
?

*/

#include <iostream>
#include <cstring>

int villages[100][100];
bool marked[100];
int marked_villages[100];
int M;
int prim() {
    int marked_cnt = 0;
    int total_min_cost = 0;
    marked[1] = true;
    marked_villages[marked_cnt++] = 1;

    for (;;) {
        int min_node = -1;
        int min_cost = 0x7FFFFFFF;
        for (int i = 0; i < marked_cnt; i++) {
            for (int j = 1; j <= M; j++) {
                if (marked[j] == false && 
                    villages[marked_villages[i]][j] != 0 && 
                    villages[marked_villages[i]][j] < min_cost) {
                        min_cost = villages[marked_villages[i]][j];
                        min_node = j;
                }
            }
        }
        if (min_node == -1) {
            break;
        }
        marked[min_node] = true;
        marked_villages[marked_cnt++] = min_node;
        total_min_cost += min_cost;
    }
    if (marked_cnt != M) {
        total_min_cost = -1;
    }
    return total_min_cost;
}

int main() {
    int N;
    while (std::cin>>N>>M) {
        if (N == 0) {
            break;
        }
        memset(villages, 0, sizeof(villages));
        memset(marked, 0, sizeof(marked));
        int a, b, c;
        while (N--) {
            std::cin>>a>>b>>c;
            villages[a][b] = c;
            villages[b][a] = c;
        }
        int min_cost = prim();
        min_cost < 0 ? std::cout<<'?' : std::cout<<min_cost;
        std::cout<<std::endl;
    }
    return 0;
}