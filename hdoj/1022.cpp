#include<iostream>
#include<stack>
#include<string>
#include<vector>
#include<algorithm>

void solve(const std::string& s1, const std::string& s2) {
    std::stack<char> sk;
    std::vector<char> ops;
    auto len = s1.length();
    decltype(len) s1_pos = 0;
    decltype(len) s2_pos = 0;
    bool succ = false;
    for (;;) {
        if (sk.empty() || sk.top() != s2[s2_pos]) {
            while (s1_pos < len && s2_pos < len && s1[s1_pos] != s2[s2_pos]) {
                sk.push(s1[s1_pos++]);
                ops.push_back('i');
            }
            if (s1_pos < len && s2_pos < len) {
                sk.push(s1[s1_pos++]);
                ops.push_back('i');
            } 
        }
        if (!sk.empty() && sk.top() == s2[s2_pos]) {
            ops.push_back('o');
            sk.pop();
            s2_pos++;
        } else if (sk.empty() && s1_pos == len && s2_pos == len) {
            succ = true;
            break; 
        } else {
            break;
        }
    }
    if (succ) {
        std::cout<<"Yes."<<std::endl;
        std::for_each(ops.begin(), ops.end(), [](char c) {
            c == 'i' ? std::cout<<"in" : std::cout<<"out";
            std::cout<<std::endl;
        });
        std::cout<<"FINISH"<<std::endl;
    } else {
        std::cout<<"No."<<std::endl;
        std::cout<<"FINISH"<<std::endl;
    }
}

int main() {
    int n;
    std::string s1, s2;
    while (std::cin>>n>>s1>>s2) {
        solve(s1, s2);
    }
    return 0;
}