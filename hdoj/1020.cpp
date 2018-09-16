#include <iostream>
#include <string>

int main() {
    std::string s;
    int prefix = 0;
    char curr;
    bool stop;
    int t;
    std::cin>>t;
    while (t--) {
        std::cin>>s;
        if (s.empty()) {
            continue;
        }
        stop = false;
        std::string::size_type start_pos = 0;
        curr = s[0];
        for (;;) {
            std::string::size_type end_pos = s.find_first_not_of(curr, start_pos + 1);
            if (end_pos == std::string::npos) {
                end_pos = s.length();
                stop = true; 
            }
            prefix = end_pos - start_pos;
            if (prefix == 1) {
                std::cout<<curr;
            } else {
                std::cout<<prefix<<curr;
            }
            if (stop) {
                std::cout<<std::endl;
                break;
            } 
            curr = s[end_pos];
            start_pos = end_pos;
        }
    }
    return 0;
}