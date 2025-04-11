#include <iostream>
#include <string>
#include <vector>
#include <string_view>
#include <experimental/iterator>

static const long long int PRIME = 1'000'000'007;
static const long long int BASE = 2;

template<typename T>
T readT() {
    T val;
    std::cin >> val;
    return val;
}

std::vector<size_t> rabinKarpSearch(const std::string& text, const std::string& pattern) {
    std::vector<size_t> matches;
    const size_t n = text.length();
    const size_t m = pattern.length();

    if (m == 0 || n < m){
        return matches;
    }

    long long int pow = 1;
    for (size_t i = 0; i < m - 1; ++i) {
        pow = (pow * BASE) % PRIME;
    }

    long long int patternHash = 0, textHash = 0;
    for (size_t i = 0; i < m; ++i) {
        patternHash = (BASE * patternHash + pattern[i]) % PRIME;
        textHash = (BASE * textHash + text[i]) % PRIME;
    }

    for (size_t i = 0; i <= n - m; ++i) {
        if (patternHash == textHash) {
            bool match = true;
            for (size_t j = 0; j < m; ++j) {
                if (text[i + j] != pattern[j]) {
                    match = false;
                    break;
                }
            }
            
            if (match) {
                matches.push_back(i);
            }
        }
        
        if (i < n - m) {
            textHash = (BASE * (textHash - text[i] * pow) + text[i + m]) % PRIME;
            
            if (textHash < 0) {
                textHash += PRIME;
            }
        }
    }
    
    return matches;
}

int main() {
    const auto pattern = readT<std::string>();
    const auto text = readT<std::string>();

    std::vector<size_t> res = rabinKarpSearch(text,pattern);
    std::copy(res.begin(), res.end(),
        std::experimental::make_ostream_joiner(std::cout, " "));
    std::cout << "\n";

    return 0;
}
