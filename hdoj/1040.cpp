#include <iostream>
#include <set>
#include <algorithm>

int main() {
    int t;
    std::set<int> num_set;
    int num;
    int cnt;
    std::cin>>t;
    while (t--) {
        std::cin>>cnt;
        while (cnt--) {
            std::cin>>num;
            num_set.insert(num);
        }
        bool add_space = false;
        std::for_each(num_set.begin(), num_set.end(), [&add_space](int n) {
            add_space ? std::cout<<' ', true : add_space = true;
            std::cout<<n;
        });
        std::cout<<std::endl;
        num_set.clear();
    }
    return 0;
}