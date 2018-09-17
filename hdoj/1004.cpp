#include <iostream>
#include <string>
#include <map>

int main() {
    int n;
    std::map<std::string, int> table;
    std::string s;
    std::string current_most_popular;
    int current_max;
    while (std::cin>>n && n != 0) {
        current_max = 0;
        table.clear();
        while (n--) {
            std::cin>>s;
            auto iter = table.find(s);
            if (iter == table.end()) {
                table.insert(std::make_pair(s, 0));
                iter = table.find(s);
            }
            iter->second++;
            if (iter->second > current_max) {
                current_max = iter->second;
                current_most_popular = s;
            }
        }
        std::cout<<current_most_popular<<std::endl;
    }
    return 0;
}