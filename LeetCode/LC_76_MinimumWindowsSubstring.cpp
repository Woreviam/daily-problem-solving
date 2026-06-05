#include <iostream>
#include <string>

class MinimumWindowSubstring {
private:
    std::string m_text, m_pattern;
public:
    MinimumWindowSubstring() = delete;
    MinimumWindowSubstring(std::string text, std::string pattern)
        : m_text(std::move(text)),
          m_pattern(std::move(pattern))
    {}
    std::string findMinimumWindow() {
        std::unordered_map<char, int>pattern_freq, current_freq;
        int match_count = 52, start_pos = -1, current_size = m_text.size() + 1;

        for (auto& c: m_pattern) {
            pattern_freq[c]++;
            if (pattern_freq[c] == 1)match_count--;
        }

        for (int l = 0, r = 0; l < m_text.length(); l++) {

            if (l > 0) {
                current_freq[m_text[l - 1]]--;
                if (current_freq[m_text[l - 1]] == pattern_freq[m_text[l - 1]] - 1)match_count--;
            }

            while (r < m_text.size() && match_count != 52) {

                current_freq[m_text[r]]++;
                if (current_freq[m_text[r]] == pattern_freq[m_text[r]])match_count++;
                r++;
            }

            if (match_count == 52 && r - l < current_size) {
                current_size = r - l;
                start_pos = l;
            }
        }

        if (start_pos == -1)return "";
        return m_text.substr(start_pos, current_size);
    }
};

int main() {

    ///////////////// UNIT TEST /////////////////
    // GROUP 1: CORNER CASES
    // T1: Corner case - only one character
    {
        MinimumWindowSubstring test("a", "a");
        std::string expected = "a";
        if (expected == test.findMinimumWindow())std::cout << "T1 passed" << std::endl;
        else std::cout << "T1 failed" << std::endl;
    }
    // T2: Corner case - only one character
    {
        MinimumWindowSubstring test(std::string(100000, 'a'), std::string(100000, 'a'));
        std::string expected = std::string(100000, 'a');
        if (expected == test.findMinimumWindow())std::cout << "T2 passed" << std::endl;
        else std::cout << "T2 failed" << std::endl;
    }
    
    return 0;
}